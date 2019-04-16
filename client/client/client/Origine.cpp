#include <iostream>
#include <winsock.h>
#include <process.h>

#pragma comment (lib, "Ws2_32.lib")
#define STR_BUF 256

using namespace std;

int main()
{
	SOCKET clientSocket;
	SOCKADDR_IN addr;

	char ip[STR_BUF];

	printf("IP Server: ");
	fgets(ip, sizeof(ip), stdin);

	WORD wVersionRequested = MAKEWORD(2, 2);
	WSADATA wsaData;
	WSAStartup(wVersionRequested, &wsaData);

	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(ip);
	addr.sin_port = htons(2700);
	clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	connect(clientSocket, (LPSOCKADDR)&addr, sizeof(addr));

	while (true) {
		char sendBuf[STR_BUF];
		char recvBuf[STR_BUF];

		printf("> ");
		fgets(sendBuf, sizeof(sendBuf), stdin);

		send(clientSocket, sendBuf, sizeof(sendBuf), 0);

		recv(clientSocket, recvBuf, sizeof(recvBuf), 0);

		printf("%s", recvBuf);
	}

	WSACleanup();
}