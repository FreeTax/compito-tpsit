#include "pch.h"
#include <iostream>
#include <winsock.h>
#include <process.h>

#pragma comment (lib, "Ws2_32.lib")
#define STR_BUF 256

using namespace std;

unsigned int __stdcall clientHandler(void*);

int main()
{
	SOCKET serverSocket;
	SOCKADDR_IN serverAddr;

	WORD wVersionRequested = MAKEWORD(2, 2);
	WSADATA wsaData;
	WSAStartup(wVersionRequested, &wsaData);

	serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = inet_addr("0.0.0.0");
	serverAddr.sin_port = htons(2700);

	bind(serverSocket, (LPSOCKADDR)&serverAddr, sizeof(struct sockaddr));
	listen(serverSocket, SOMAXCONN);

	printf("Server in ascolto su %s:%d\n", inet_ntoa(serverAddr.sin_addr), ntohs(serverAddr.sin_port));

	while (true) {
		SOCKET clientSocket = SOCKET_ERROR;
		SOCKADDR_IN clientAddr;

		while (clientSocket == SOCKET_ERROR)
			clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddr, &sizeof(struct sockaddr_in));

		printf("Connessione stabilita con client %s:%d\n", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));

		_beginthreadex(0, 0, &clientHandler, (void*)clientSocket, 0, 0);
	}

	WSACleanup();
}

unsigned int __stdcall clientHandler(void* data) {
	SOCKET clientSocket = (SOCKET)data;

	char buffer[STR_BUF];

	for (;;) {

		int res = recv(clientSocket, buffer, sizeof(buffer), 0);

		if (res > 0) {
			printf("Messaggio ricevuto: %s", buffer);

			// just sends back what was received

			send(clientSocket, buffer, sizeof(buffer), 0);
		}
		else {
			break;
		}

	}

	closesocket(clientSocket);
	return 0;
}