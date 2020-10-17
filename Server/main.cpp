#include <iostream>
#include <winsock2.h>
//�����
#pragma comment(lib,"ws2_32.lib")
using namespace std;

#define	SERVER_PORT						1314
#define	SERVER_ADDR						192
#define	SERVER_CLIEN_MAXSIZE		10

#define	BUFFER_SEND						1024
#define	BUFFER_RECV						1024

char			g_buffer_send[BUFFER_SEND];
char			g_buffer_recv[BUFFER_RECV];

typedef struct {
	char	name[32] = { 0 };
	int lv = 0;
}CLIENT_MSG,*PCLIENT_MSG;


int main(int argc, char* argv[]) {

	WSADATA	wsData;
	if (WSAStartup(MAKEWORD(2, 2), &wsData) != 0){
		cout << "Failed to load Winsock" << endl;
		return	0;
	}

	memset(g_buffer_send, 0, sizeof(g_buffer_send));
	memset(g_buffer_recv, 0, sizeof(g_buffer_recv));
	
	SOCKET sockServer = socket(AF_INET, SOCK_STREAM, 0);//����һ���׽���

	if (sockServer == SOCKET_ERROR){
		cout << "�׽��ִ���ʧ��!" << endl;
		getchar();
		return	0;
	}

	SOCKADDR_IN	serverAddr;//��������������Ϣ	
	serverAddr.sin_family = AF_INET;					//���÷�������ַ��
	serverAddr.sin_port = htons(SERVER_PORT);//���÷������˿ں�
	serverAddr.sin_addr.S_un.S_addr = inet_addr("10.5.33.169");
		
	//htonl(INADDR_ANY);//���÷�������ַΪ������ַ
	printf("����������ַ:%s\n", inet_ntoa(serverAddr.sin_addr));
	

	int bindMsg = bind(sockServer, (LPSOCKADDR)&serverAddr, sizeof(SOCKADDR_IN));//���׽������������Ϣ��
	if (bindMsg == SOCKET_ERROR) {
		cout << "���׽���ʧ��!" << endl;
		getchar();
		return 0;
	}

	int listenMsg = listen(sockServer, SERVER_CLIEN_MAXSIZE);
	if (listenMsg == SOCKET_ERROR) {
		cout << "�����׽���ʧ��!" << endl;
		getchar();
		return	0;
	}

	SOCKET	clien_request;
	SOCKADDR_IN	clienMsg;
	memset(&clienMsg, 0, sizeof(clienMsg));

	int addrlen;
	addrlen = sizeof(SOCKADDR_IN);
	clien_request = accept(sockServer, (LPSOCKADDR)&clienMsg, &addrlen);

	if (clien_request == SOCKET_ERROR) {
		cout << "�û�����ʧ��,��ȡʧ��!" << endl;
	}
	printf("[%s]���ӳɹ�\n", inet_ntoa(clienMsg.sin_addr));

	cout << "���뷢�͸��ͻ�����Ϣ:";
	cin >> g_buffer_send;
	int sendMsg = send(clien_request, g_buffer_send, sizeof(g_buffer_send), 0);//������Ϣ���ͻ���;
	if (sendMsg == SOCKET_ERROR) {
		cout << "������Ϣʧ��!" << endl;
	}


	recv(clien_request, g_buffer_recv, sizeof(g_buffer_recv), 0);
	if (strlen(g_buffer_recv) != 0) {
		printf("[%s]:[%s]", inet_ntoa(clienMsg.sin_addr), g_buffer_recv);
		memset(g_buffer_recv, 0, sizeof(g_buffer_recv));
	}

	closesocket(clien_request);
	closesocket(sockServer);
	WSACleanup();
	system("pause");
	return	0;
}