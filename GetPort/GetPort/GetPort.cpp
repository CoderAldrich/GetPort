// GetPort.cpp : �������̨Ӧ�ó������ڵ㡣
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

	// ��ʼ��socket
	wVersionRequested = MAKEWORD(2, 2);
	if (0 != WSAStartup(wVersionRequested, &wsaData))
	{
		return false;
	}

	// 1. ����һ��socket
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);

	// 2. ����һ��sockaddr���������Ķ˿ں���Ϊ0
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(ADDR_ANY);
	addr.sin_port = 0;        // ��portָ��Ϊ0,�����bindʱ��ϵͳ��Ϊ��ָ��һ�����õĶ˿ں�

							  // 3. ��
	int ret = bind(sock, (SOCKADDR*)&addr, sizeof addr);

	if (0 != ret) {
		result = false;
		goto END;
	}

	// 4. ����getsockname��ȡ
	struct sockaddr_in connAddr;
	int len = sizeof connAddr;
	ret = getsockname(sock, (SOCKADDR*)&connAddr, &len);

	if (0 != ret) {
		result = false;
		goto END;
	}

	port = ntohs(connAddr.sin_port); // ��ȡ�˿ں�

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

