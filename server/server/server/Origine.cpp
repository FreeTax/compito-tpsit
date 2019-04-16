#include <stdio.h>
#include <winsock.h>
#include <string.h>
#include <iostream>
#include <process.h>
#include <fstream>
#include <string>
#pragma comment (lib,"Ws2_32.lib")
using namespace std;

SOCKADDR_IN Client_addr;
int ls_result;
int sin_size;

unsigned int __stdcall clientHandler(void* re){
		SOCKET &remoteSocket = *(SOCKET*)re;
		ifstream inFile;
		inFile.open("data.txt");
		char buffer[3];
		recv(remoteSocket, buffer, sizeof(buffer), 0);
		cout << "riga richiesta : " << buffer << endl;
		int n = stoi(buffer);
		char ok[1024] = "errore";
		if (!inFile) {
			cout << "Errore nell'apertura del file ";
		}
		else {
			
			for (int i = 0; i <= n; i++) {
					inFile.getline(ok, 1024);
				}
			}
		send(remoteSocket, ok, strlen(ok), 0);
		inFile.close();
		return 0;
}

int main()
{
	SOCKET	remoteSocket;
	SOCKET	listenSocket;
	SOCKADDR_IN Server_addr;
	short port;
	int wsastartup;

	WORD wVersionRequested = MAKEWORD(2, 2);
	WSADATA wsaData;
	wsastartup = WSAStartup(wVersionRequested, &wsaData);
	if (wsastartup != NO_ERROR) cout << "Errore WSAStartup()\n" << endl;

	listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (listenSocket < 0) cout << "Server: errore nella creazione della socket.\n" << endl;
	else cout << "La Listening Socket è partita\n" << endl;

	port = 27000;

	Server_addr.sin_family = AF_INET;
	Server_addr.sin_addr.s_addr = 0;
	Server_addr.sin_port = htons(port);

	if (bind(listenSocket, (LPSOCKADDR)&Server_addr, sizeof(struct sockaddr)) < 0)
		cout << "Server: errore durante la bind." << endl;

	ls_result = listen(listenSocket, SOMAXCONN);
	if (ls_result < 0) printf("Server: errore durante la listen.");
	else cout << "La Socket è in Ascolto" << endl;
	while (true) {
		sin_size = sizeof(struct sockaddr_in);
		remoteSocket = accept(listenSocket, (struct sockaddr *)&Client_addr, &sin_size);
		cout << "client " << inet_ntoa(Client_addr.sin_addr) << "  " << ntohs(Client_addr.sin_port) << endl;
		_beginthreadex(0, 0, &clientHandler, (void*) &remoteSocket, 0, 0);
	}

	cout << "Chiudo il Server" << endl;
	closesocket(remoteSocket);
	WSACleanup();
	return 0;
}
