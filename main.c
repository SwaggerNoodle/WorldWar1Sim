#define WIN32_LEAN_AND_MEAN

#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <windowsx.h>
#include <stdio.h>
#include <stdlib.h>

#include "network.h"



static HINSTANCE g_hInstance = NULL;
static const wchar_t *g_mainClassName = L"WorldWar1Sim";

static LRESULT CALLBACK MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);




static BOOL RegisterMainWindowClass(HINSTANCE hInstance){

	WNDCLASSEXW wc;
	ZeroMemory(&wc, sizeof(wc));

	wc.cbSize        = sizeof(wc);
        wc.lpfnWndProc   = MainWndProc;
        wc.hInstance     = hInstance;
        wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
        wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
        wc.lpszClassName = g_mainClassName;

        if (RegisterClassExW(&wc) == 0){
                return FALSE;
        }
        return TRUE;
}
static HWND CreateMainWindow(HINSTANCE hInstance){
	return CreateWindowExW(0,
			       g_mainClassName,
			       L"Supremacy1914 Clone",
			       WS_OVERLAPPEDWINDOW,
			       CW_USEDEFAULT,
			       CW_USEDEFAULT,

			       800,
			       600,

			       NULL,
			       NULL,
			       hInstance,
			       NULL
	);

}



static LRESULT CALLBACK MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam){

	switch(msg){

		case WM_DESTROY:
			DisconnectFromServer();
			PostQuitMessage(0);
			return 0;
	}
	return DefWindowProcW(hwnd, msg, wParam, lParam);
}




int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){

	g_hInstance = hInstance;

	if (!ConnectToServer("127.0.0.1")){
		MessageBoxW(NULL,
			    L"Could not connect to the server.",
			    L"Connection Failed",
			    MB_OK | MB_ICONERROR
		);
		return 1;
	}
	if (!RegisterMainWindowClass(hInstance)){
		DisconnectFromServer();
		return 1;
	}

	HWND hwnd = CreateMainWindow(hInstance);
	if (hwnd == NULL){
		DisconnectFromServer();
		return 1;
	}

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
	
	MSG msg;
	while (1){
		int ret = GetMessageW(&msg, NULL, 0, 0);

		if (ret > 0){
			TranslateMessage(&msg);
			DispatchMessageW(&msg);
		}
		else {
			break;
		}
	}
	return (int)msg.wParam;
}






