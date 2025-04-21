
#include <iostream>
#include "Includes.h"
#include "CPackets.h"
int main()
{
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	int server = socket(AF_INET, SOCK_STREAM, 0);
	sockaddr_in addr = {};
	addr.sin_family = AF_INET;
	addr.sin_port = htons(13381);
	addr.sin_addr.S_un.S_addr = INADDR_ANY;

	bind(server, (SOCKADDR*)&addr, sizeof(addr));
	listen(server, SOMAXCONN);
	while (true) {
		int client = accept(server, nullptr, nullptr);
		auto user = CBanchoHelper::parseLoginLines(client);
		std::cout << "[DEBUG] User " << user.username << " Logged in from build " << user.build << std::endl;
		CLoginReply loginreply = CLoginReply(user);
		loginreply.WriteToStream(client);
	}
	closesocket(server);
	WSACleanup();
	return 0;
}	
