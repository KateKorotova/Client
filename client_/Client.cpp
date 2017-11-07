#include <iostream>
#include "Winsock2.h"
#include <ws2tcpip.h>
#include <string> 

#pragma comment(lib, "Ws2_32.lib")

using namespace std;

int main() {
	string ipAddress = "127.0.0.1";  // Ip Adress of the server
	int port = 54000;

	// Initialize WinSock
	WSADATA data;
	WORD ver = MAKEWORD(2, 2);
	int wsResult = WSAStartup(ver, &data);
	if (wsResult != 0) {
		cerr << "Can't start winsock" << endl;
		return 1;
	}

	// Create socket
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET) {
		cerr << "Can't create socket" << endl;
		return 2;
	}
	// Full in a hint structure 
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(port);
	inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);

	// Connect to server
	int connResult = connect(sock, (sockaddr*)&hint, sizeof(hint));
	if (connResult == SOCKET_ERROR) {
		cerr << "Can't connect to server" << endl;
		WSACleanup();
		return 3;
	}

	// Do while loop to send and receive data 
	char buf[4096];
	string userInput;
	do {


	} while (userInput.size() > 0);

	// Close
	closesocket(sock);
	WSACleanup();
}