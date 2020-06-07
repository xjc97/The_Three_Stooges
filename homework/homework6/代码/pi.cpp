#include <iostream>
#include <unistd.h>
#include <cstring>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
using namespace std; 
#define USEPORT 1234

int main()
{
//****创建套接字
	int serverSock = socket(AF_INET, SOCK_STREAM, 0); 
	//Windows中，AF_INET==PF_INET
	//Linux中，不同的版本这两者有微小差别.对于BSD是AF,对于POSIX是PF
	if (serverSock < 0)
	{
		cout << "socket creation failed" << endl; 
		exit(-1); 
	}
	cout << "socket creation successfully" << endl; 
//****绑定ip和端口
	struct sockaddr_in serverAddr; 
	memset(&serverAddr, 0, sizeof(serverAddr)); 
	serverAddr.sin_family = AF_INET; 
	serverAddr.sin_port = htons(USEPORT); 
	//INADDR_ANY绑定所有IP
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY); 
//****绑定套接字
	if (bind(serverSock, 
		(struct sockaddr*)&serverAddr, 
		sizeof(struct sockaddr)) == -1)
	{
		cout << "Bind error, Port["<< USEPORT << "]" << endl; 
	       exit(-1); 
    }
	cout << "Bind successfully" << endl; 
	
//****监听
	if (listen(serverSock, 10) == -1)
	{
		cout << "Listen error!" << endl; 
	}
	cout << "Listening on port[" << USEPORT << "]" << endl; 

//****开始接收accept()
	struct sockaddr clientAddr; 
	int size = sizeof(struct sockaddr); 

	int clientSock = accept(serverSock, (struct sockaddr*)&clientAddr, (socklen_t*)&size); 

	cout << "****NEW client touched****" << endl; 

//****通信
	while (1)
	{
		string input; 
		cout << "input something ('quit' to shutdown)" << endl; 
		cin >> input; 
		send(clientSock, input.c_str(), input.length(), 0); 
		if (input == "quit")
		{
			cout << "shutdown"<<endl;
			break; 
		}
	}
	
	close(serverSock); 
	return 0; 
}
