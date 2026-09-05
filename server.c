#define WIN32_LEAN_AND_MEAN

#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>

#define SERVER_PORT 27015

int main(void){

	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);



	SOCKET listenSocket = socket(AF_INET, 
				     SOCK_STREAM, 
				     IPPROTO_TCP
				     );
	struct sockaddr_in serverAddress;
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(SERVER_PORT);
	serverAddress.sin_addr.s_addr = INADDR_ANY;
	
	bind(listenSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress));
	listen(listenSocket, 1);

	printf("Server running on port %d. \n", SERVER_PORT);
	printf("Waiting for a client...\n");

	

	struct sockaddr_in clientAddress;
	int clientAddressSize = sizeof(clientAddress);

	SOCKET clientSocket = accept(listenSocket, 
				     (struct sockaddr*)&clientAddress, 
				     &clientAddressSize
	           	             );
	if (clientSocket == INVALID_SOCKET){
		printf("accept() failed.\n");
		closesocket(listenSocket);
		WSACleanup();
		return 1;
	}



	char clientIP[INET_ADDRSTRLEN];

	inet_ntop(AF_INET, 
		  &clientAddress.sin_addr, 
		  clientIP, 
		  sizeof(clientIP)
	);
	printf("Client connected from %s. \n", clientIP);



	char dummyBuffer[1];

	int result = recv(clientSocket,
			  dummyBuffer,
			  sizeof(dummyBuffer),
			  0
			  );
	if (result == 0){
		printf("Client disconnected.\n");
	}
	else if (result == SOCKET_ERROR){
		printf("Connection lost.\n");
	}

	closesocket(clientSocket);
	closesocket(listenSocket);

	WSACleanup();

	return 0;
}









