#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WinSock2.h>
#include <iostream>

//�ͻ���

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
		cout << "�׽��ִ���ʧ��" << endl;
		getchar();
		return 0;
	}

	SOCKADDR_IN	serverAddr;//��������������Ϣ	
	serverAddr.sin_family = AF_INET;					//���÷�������ַ��
	serverAddr.sin_port = htons(SERVER_PORT);//���÷������˿ں�
	serverAddr.sin_addr.S_un.S_addr = inet_addr("10.5.33.169");
	
	int connectMsg = connect(sockClient, (LPSOCKADDR)&serverAddr, sizeof(serverAddr));

	if (connectMsg == INVALID_SOCKET) {
		cout << "����������ʧ��!" << endl;
		closesocket(sockClient);
		getchar();
		return 0;
	}

	recv(sockClient, g_buffer_recv, sizeof(g_buffer_recv), 0);
	printf("������:%s\n", g_buffer_recv);


	closesocket(sockClient);
	WSACleanup();
	system("pause");
	return 0;
}