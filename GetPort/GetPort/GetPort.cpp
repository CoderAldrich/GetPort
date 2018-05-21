// GetPort.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdio.h>
#include <Winsock2.h>

#pragma comment (lib, "Ws2_32.lib")

bool getAvaliablePort(unsigned short &port)
{
	bool result = true;
	WORD			wVersionRequested;
	WSADATA			wsaData;

	// 初始化socket
	wVersionRequested = MAKEWORD(2, 2);
	if (0 != WSAStartup(wVersionRequested, &wsaData))
	{
		return false;
	}

	// 1. 创建一个socket
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);

	// 2. 创建一个sockaddr，并将它的端口号设为0
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(ADDR_ANY);
	addr.sin_port = 0;        // 若port指定为0,则调用bind时，系统会为其指定一个可用的端口号

							  // 3. 绑定
	int ret = bind(sock, (SOCKADDR*)&addr, sizeof addr);

	if (0 != ret) {
		result = false;
		goto END;
	}

	// 4. 利用getsockname获取
	struct sockaddr_in connAddr;
	int len = sizeof connAddr;
	ret = getsockname(sock, (SOCKADDR*)&connAddr, &len);

	if (0 != ret) {
		result = false;
		goto END;
	}

	port = ntohs(connAddr.sin_port); // 获取端口号

END:
	if (0 != closesocket(sock))
		result = false;
	return result;
}

int main()
{
	unsigned short i_random_port;
	while (true)
	{
		getAvaliablePort(i_random_port);
		printf("port=%d\n", i_random_port);
		Sleep(200);
	}

	getchar();
    return 0;
}

