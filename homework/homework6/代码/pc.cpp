#include <iostream>
#include <string>
#include <WinSock2.h> //包含WinSock2.h头文件
using namespace std;
#pragma comment(lib, "ws2_32.lib") //加载 ws2_32.dll 
#pragma warning(disable:4996)

int main()
{
//****初始化
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);		
	
//****创建套接字
	SOCKET sock = socket(PF_INET, SOCK_STREAM, 0);

//****创建sockAddr结构体
	sockaddr_in sockAddr;						
	memset(&sockAddr, 0, sizeof(sockAddr));	
	sockAddr.sin_family = PF_INET;
	sockAddr.sin_port = htons(1234);
	sockAddr.sin_addr.s_addr = inet_addr(RASPI_IP); //树莓派的局域网IP

//****建立连接
	connect(sock, (SOCKADDR*)& sockAddr, sizeof(SOCKADDR));		
	cout << "客户端发送链接请求" << endl;

//****接收服务器传回的数据	
	while (1)
	{
		cout << "等待服务端发送信息.." << endl;
		
		char tack[MAXBYTE] = { 0 };
		recv(sock, tack, MAXBYTE, NULL); 
		
		//输出接收到的数据
		cout << "服务器: " << tack << endl;
		
		if (strcmp(tack, "quit") == 0)
		{
			cout << "shutdown" << endl; 
			break;
		}
	}

	//关闭套接字、终止使用 DLL
	closesocket(sock);
	WSACleanup();

	return 0;
}
