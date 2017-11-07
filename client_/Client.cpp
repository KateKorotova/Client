#include <iostream>
#include "Winsock2.h"
#include <ws2tcpip.h>
#include <string> 
#include <vector>
#include <fstream>
#include <algorithm>

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
	vector <string>origtxt;
	ifstream file("text.txt");
	while (!(file.eof())) {
		int i = 0;
		string tmp;
		getline(file, tmp);
		origtxt.push_back(tmp);
		i++;
	}
	file.close();

	char buf[4096];
	string userInput;
	do {
		getline(cin, userInput);
		if (userInput == "correct") {
			int sendResult = send(sock, userInput.c_str(), userInput.size() + 1, 0);
			if (sendResult != SOCKET_ERROR) {
				ZeroMemory(buf, 4096);
				int bytesReceived = recv(sock, buf, 4096, 0);
				string mess = string(buf);
				if (mess != "No changes") {
					int num = stoi(mess.substr(0, mess.find(",")));
					mess.erase(mess.begin(), mess.begin() + mess.find(",") + 1);
					string chs = mess;
					if (num < origtxt.size())
						origtxt[num] = chs;
					else
						origtxt.push_back(chs);

					ofstream nfile("text.txt");
					for (int i = 0; i < origtxt.size(); i++)
						nfile << origtxt[i] >> endl; 
					nfile.close();
				}
				cout << string(buf) << endl;

			}
		}
			else
				cout << "You can correct file" << endl;

	} while (userInput.size() > 0);

	// Close
	closesocket(sock);
	WSACleanup();
}