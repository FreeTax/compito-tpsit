#include <iostream>
#include <stdio.h>
#include <winsock.h>
#include <string.h>
#include <process.h>
#pragma comment (lib,"Ws2_32.lib")

using namespace std;
SOCKET	ServerSock;
SOCKADDR_IN addr;
bool isWorking;

unsigned int __stdcall recive(void*);

void chatting() {
	char messaggio[80];
	

	cout << "dammi la lineaa da fornire al server" << endl;
	cin >> messaggio;
	send(ServerSock, messaggio, sizeof(messaggio), 0);
	_beginthreadex(0, 0, &recive, 0, 0, 0);
	return;
	

}

unsigned int __stdcall recive(void* ) {
	char buffer[1024] = { 0 };
	recv(ServerSock, buffer, 1024, 0);
	cout << buffer << endl;
	isWorking = false;
	return 0;
}

int main()
{
	isWorking = true;
	int valread;
	short port;
	char ip[15];
	WORD wVersionRequested = MAKEWORD(2, 2);
	WSADATA wsaData;
	WSAStartup(wVersionRequested, &wsaData);
	port = 27000;
	addr.sin_family = AF_INET;
	cout << "dammi l'ip" << endl;
	gets_s(ip);
	addr.sin_addr.s_addr = inet_addr(ip);
	addr.sin_port = htons(port);
	ServerSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (connect(ServerSock, (LPSOCKADDR)&addr, sizeof(addr)) < 0) {
		cout << "errore!" << endl;
		exit(1);
	}
	chatting();
	while (isWorking != false) {
		cout << "sto lavorando!!!" << endl;
		Sleep(1000);
	}
	closesocket(ServerSock);
	WSACleanup();
	system("PAUSE");


}