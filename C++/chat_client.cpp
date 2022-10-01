// Client side C/C++ program to demonstrate Socket programming 

#include <iostream> 
#include <iomanip>
#include <unistd.h> 
#include <string.h> 
#include <thread>
#include <pthread.h>
#include <csignal>

#ifdef _WIN32
	#include <winsock2.h>
#elif __linux__
	#include <sys/socket.h> 
	#include <arpa/inet.h> 
#endif

using namespace std;

int PORT,i=0,flag=1;
int sock = 0, valread; 
struct sockaddr_in serv_addr; 
static char message[1024]; 
static char buffer[1024] = {0}; 

char terms[][10] = {"bye","goodbye","tata"};

void termHandler(int signum)
{
	cout<<"[!] "<<inet_ntoa(serv_addr.sin_addr)<<": "<<(int)ntohs(serv_addr.sin_port)<<" Unexpectedly closed the connection!\n";
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
	close(sock);
	exit(signum);
}

void Recv()
{
	while(1)
	{
		memset(buffer,0,sizeof(buffer));
		valread = recv( sock , buffer, 1024,0);
		cout<<endl<<setw(50)<<right<<buffer<<endl;
		
		if (valread == 0)
			raise(SIGTERM);		
		
		for (i=0; i<sizeof(terms)/10; i++)
		{
			if (strstr(buffer,terms[i]) != NULL)
			{
				#ifndef _WIN32
					shutdown(sock,SHUT_RD);
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

	if (argc != 3)
	{
		cout<<"[!] Connect IP/ Port not provided!\nUsage: <script> CONNECT_IP CONNECT_PORT\n";
		return 0;
	}	
	PORT = atoi(argv[2]);

	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
	{ 
		cout<<"\n Socket creation error \n"; 
		return -1; 
	} 

	serv_addr.sin_family = AF_INET; 
	serv_addr.sin_port = htons(PORT); 
	
	// Convert IPv4 and IPv6 addresses from text to binary form 
	
	#ifdef _WIN32
		serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
		if(!inet_addr(argv[1]))
	#elif __linux__
		if(inet_pton(AF_INET, argv[1], &serv_addr.sin_addr)<=0)  
	#endif
	{ 
		cout<<"\nInvalid address/ Address not supported \n"; 
		return -1; 
	} 

	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
	{ 
		cout<<"\nConnection Failed \n"; 
		return -1; 
	} 
	cout<<"[+] Connected with "<<inet_ntoa(serv_addr.sin_addr)<<" with port #"<<(int)ntohs(serv_addr.sin_port)<<endl;
	
	//cout<<inet_ntoa(serv_addr.sin_addr)<<endl;		// prints peer's IP
	//cout<<(int)ntohs(serv_addr.sin_port)<<endl;		// prints peer's PORT
	
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
		cin.getline(message, 1024);
		send(sock , message , strlen(message) , 0 ); 		
		
		for (i=0; i<sizeof(terms)/10; i++)
		{
			if (strstr(buffer,terms[i]) != NULL)
			{
				#ifndef _WIN32
					shutdown(sock,SHUT_WR);
				#endif
				flag--;
				if(flag<0)
					raise(SIGILL);
			}
		}
	}
	return 0; 
} 

