#include "network.h"

static SOCKET g_serverSocket = INVALID_SOCKET;
static BOOL g_winsockStarted = FALSE;


BOOL ConnectToServer(const char *serverIP){

	WSADATA wsaData;
	if(WSAStartup(MAKEWORD(2, 2), &wsaData) != 0){
		return FALSE;
	};



	g_winsockStarted = TRUE;
	g_serverSocket = socket(AF_INET,
				SOCK_STREAM,
				IPPROTO_TCP
				);
	if (g_serverSocket == INVALID_SOCKET){
		WSACleanup();
		g_winsockStarted = FALSE;
		return FALSE;
	}




	struct sockaddr_in serverAddress;
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(SERVER_PORT);
	if (inet_pton(AF_INET, serverIP, &serverAddress.sin_addr) != 1){
		closesocket(g_serverSocket);
		g_serverSocket = INVALID_SOCKET;
		WSACleanup();
		g_winsockStarted = FALSE;
		return FALSE;
	}




	if (connect(g_serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR){
		closesocket(g_serverSocket);
		g_serverSocket = INVALID_SOCKET;
		WSACleanup();
		g_winsockStarted = FALSE;
		return FALSE;
	}
	return TRUE;
}

void DisconnectFromServer(void){
	if (g_serverSocket != INVALID_SOCKET){
		closesocket(g_serverSocket);
		g_serverSocket = INVALID_SOCKET;

	}
	if (g_winsockStarted){
		WSACleanup();
		g_winsockStarted = FALSE;
	}
}







