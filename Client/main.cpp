#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WinSock2.h>
#include <iostream>

//客户端

#pragma comment(lib,"ws2_32.lib")
using namespace std;

#define	SERVER_PORT						1314
#define	SERVER_ADDR						192
#define	SERVER_CLIEN_MAXSIZE		10

#define		BUFFER_SEND		1024
#define		BUFFER_RECV		1024

char				g_buffer_send[BUFFER_SEND];
char				g_buffer_recv[BUFFER_RECV];


int main(int argc, char* argv[]) {

	WSADATA wsData;
	if (WSAStartup(MAKEWORD(2, 2), &wsData) != 0) {
		cout << "Failed to load Winsock" << endl;
		return	0;
	}

	SOCKET	sockClient = socket(AF_INET, SOCK_STREAM, 0);
	if (sockClient == SOCKET_ERROR) {
		cout << "套接字创建失败" << endl;
		getchar();
		return 0;
	}

	SOCKADDR_IN	serverAddr;//创建服务器的信息	
	serverAddr.sin_family = AF_INET;					//设置服务器地址族
	serverAddr.sin_port = htons(SERVER_PORT);//设置服务器端口号
	serverAddr.sin_addr.S_un.S_addr = inet_addr("10.5.33.169");
	
	int connectMsg = connect(sockClient, (LPSOCKADDR)&serverAddr, sizeof(serverAddr));

	if (connectMsg == INVALID_SOCKET) {
		cout << "服务器连接失败!" << endl;
		closesocket(sockClient);
		getchar();
		return 0;
	}

	recv(sockClient, g_buffer_recv, sizeof(g_buffer_recv), 0);
	printf("服务器:%s\n", g_buffer_recv);


	closesocket(sockClient);
	WSACleanup();
	system("pause");
	return 0;
}