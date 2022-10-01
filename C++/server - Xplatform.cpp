// Server side C/C++ program to demonstrate Socket programming 
#include <unistd.h> 
#include <iostream> 
#include <iomanip>
#include <pthread.h> 
#include <thread> 
#include <stdlib.h> 
#include <string.h> 
#include <csignal>

#ifdef _WIN32
	#include <winsock2.h>
#elif __linux__
	#include <sys/socket.h>
	#include <netinet/in.h> 
	#include <arpa/inet.h> 
#endif

using namespace std;

int server_fd, PEER_SOCKET, valread; 
struct sockaddr_in address; 
int opt = 1, PORT = 54321, i, flag=1; 
int addrlen = sizeof(address); 
static char buffer[1024] = {0}; 
static char message[1024];

char terms[][10] = {"bye","goodbye","tata"};

void termHandler(int signum)
{
	cout<<"[!] "<<inet_ntoa(address.sin_addr)<<": "<<(int)ntohs(address.sin_port)<<" Unexpectedly closed the connection!\n";
	exit(signum);
}

void intHandler(int signum)
{
	cout<<"[!] You Unexpectedly closed the connection!\n";
	exit(signum);
}

void Closer(int signum)
{
	cout<<"[!] Connection closed successfully!\n";
	close(PEER_SOCKET);
	exit(signum);
}

void Recv()
{
	while(1)
	{	
		memset(buffer,0,sizeof(buffer));
		valread = recv( PEER_SOCKET , buffer, 1024,0); 			
		cout<<endl<<setw(50)<<right<<buffer;
		cout<<" <["<<inet_ntoa(address.sin_addr)<<": "<<(int)ntohs(address.sin_port)<<"]\n";

		
		if (valread == 0)
			raise(SIGTERM);
						
		for (i=0; i<sizeof(terms)/10; i++)
		{
			if (strstr(buffer,terms[i]) != NULL)
			{
				#ifdef __linux__
					shutdown(PEER_SOCKET,SHUT_RD);
				#endif
				flag--;
				if(flag<0)
					raise(SIGILL);
				return;
			}
		}
	}
}

int main(int argc, char const *argv[]) 
{ 
	#ifdef _WIN32
		WSADATA wsaData;
		int iRes = WSAStartup(MAKEWORD(2,2), &wsaData);
		if(iRes)
		{
			cout<<"WSAStartup Failed!"<<endl<<iRes;
			return 0;
		}
	#endif
	
	if (argc == 2)
		PORT = atoi(argv[1]);
	else if (argc > 2)
	{
		cout<<"[!] Usage: <script> (optional)<LISTENING_PORT>\n";
		return 0;
	}

	// Creating socket file descriptor 
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
	{ 
		perror("socket failed"); 
		exit(EXIT_FAILURE); 
	} 
	
	#ifdef _WIN32
		if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, (const char *)&opt, sizeof(opt))) 
	#elif __linux__
		if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) 
	#endif
	{ 				
		perror("setsockopt"); 
		exit(EXIT_FAILURE); 
	}

	address.sin_family = AF_INET; 
	address.sin_addr.s_addr = INADDR_ANY; 
	address.sin_port = htons( PORT ); 

	// Forcefully attaching socket to the port 8080 
	
	if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0) 
	{ 
		perror("bind failed"); 
		exit(EXIT_FAILURE); 
	}
	
	if (listen(server_fd, 3) < 0) 
	{ 
		perror("listen"); 
		exit(EXIT_FAILURE); 
	} 
	cout<<"[!] Listening for incoming connections on port #"<<PORT<<endl;

	#ifdef _WIN32
		if ((PEER_SOCKET = accept(server_fd, (struct sockaddr *)&address, (int *)&addrlen))<0) 
	#elif __linux__
		if ((PEER_SOCKET = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) 
	#endif
	{ 
		perror("accept"); 
		exit(EXIT_FAILURE); 
	} 
	cout<<"[+] Connected with "<<inet_ntoa(address.sin_addr)<<" with port #"<<(int)ntohs(address.sin_port)<<endl;
	//cout<<inet_ntoa(address.sin_addr)<<endl;		// prints peer's IP
	//cout<<(int)ntohs(address.sin_port)<<endl;		// prints peer's PORT
	
	thread Rcv(Recv);
	
	signal(SIGINT, intHandler);
	signal(SIGTERM, termHandler);
	signal(SIGILL, Closer);

	while(1)
	{			
		memset(message,0,sizeof(message));
		strcpy(message,"\0");
		message[0] = 0;
		fflush(stdin);
		cout<<"\nYou: ";
		cin.getline(message,1024);
		send(PEER_SOCKET , message , strlen(message) , 0 ); 
		
		for (i=0; i<sizeof(terms)/10; i++)
		{
			if (strstr(buffer,terms[i]) != NULL)
			{
				#ifdef __linux__
					shutdown(PEER_SOCKET,SHUT_WR);
				#endif
				flag--;
				if(flag<0)
					raise(SIGILL);
			}
		}
	}
	return 0; 
} 

