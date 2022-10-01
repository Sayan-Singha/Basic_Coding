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

int server_fd, PEER_SOCKET[5], valread, clientCount=-1; 
struct sockaddr_in address; 
struct sockaddr_in CLIENTS[5];
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
	close(PEER_SOCKET[0]);
	exit(signum);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Forward()
{
	//cout<<"Forward called...\n";
	char message[2048],port_char[5];
	while(1)
	{	
		//cout<<PEER_SOCKET[0];
		memset(buffer,0,sizeof(buffer));

		for (int i=0; i<=clientCount; i++)
		{
			if (!(valread = recv(PEER_SOCKET[i], buffer, 1024,0) < 0))			
			{
				cout<<inet_ntoa(CLIENTS[i].sin_addr)<<":"<<ntohs(CLIENTS[i].sin_port)<<">>> "<<buffer<<endl;
				sprintf(port_char,"%u",ntohs(CLIENTS[i].sin_port));

				memset(message,0,sizeof(message));

				strcat(message,port_char);
				strcat(message," : ");
				strcat(message,inet_ntoa(CLIENTS[i].sin_addr));
				strcat(message,">>> ");
				strcat(message,buffer);
				for (int c=0; c<=clientCount; c++)
				{
					//cout<<"i = "<<i<<"\tc = "<<c<<endl;
					if (PEER_SOCKET[c]!=PEER_SOCKET[i])
						send(PEER_SOCKET[c],message,1024,0);
				}
				memset(buffer,0,sizeof(buffer));
			}			
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void ClientManager()
{
	while(1)
	{	
		#ifdef _WIN32
			if ((PEER_SOCKET[++clientCount] = accept(server_fd, (struct sockaddr *)&address, (int *)&addrlen))<0) 
		#elif __linux__
			if ((PEER_SOCKET[++clientCount] = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) 
		#endif

		{ 
			perror("accept"); 
			exit(EXIT_FAILURE); 
		} 
		cout<<"[+] Connected with "<<inet_ntoa(address.sin_addr)<<" with port #"<<(int)ntohs(address.sin_port)<<endl;
		CLIENTS[clientCount] = address;
			
		cout<<"clientCount = "<<clientCount<<endl;
		cout<<"PEER_SOCKET[clientCount] = "<<PEER_SOCKET[clientCount]<<endl;
			
		thread Fwd(Forward);
		Fwd.detach();
	}
}


void Connect()
{

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
	

	thread CM(ClientManager);
	CM.join();
	
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

	thread Listener(Connect);
	Listener.join();
	//thread Rcv(Recv);
	
	signal(SIGINT, intHandler);
	signal(SIGTERM, termHandler);
	signal(SIGILL, Closer);

	
	return 0; 
} 

