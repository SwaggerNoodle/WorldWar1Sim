#ifndef NETWORK_H
#define NETWORK_H


#define WIN32_LEAN_AND_MEAN

#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>

#define SERVER_PORT 27015



BOOL ConnectToServer(const char *serverIP);

void DisconnectFromServer(void);



#endif
