#define connect_debug

#ifndef connect_debug
#include<stdlib.h>
#include<winsock.h>
#include<time.h>
#include "errexit.h"
#include "passivesocket.h"
#include "passUDP.h"
#pragma comment(lib,"ws2_32.lib")

#define WSVERS MAKEWORD(2,0)

int main(int argc, char* argv[])
{
	struct sockaddr_in fsin;
	char* service = (char*)"daytime";
	SOCKET sock;
	int alen;
	char* pts;
	char* buf;
	time_t now;
	WSADATA wsadata;

	switch (argc)
	{
	case 1:
		break;
	case 2:
		service - argv[1];
		break;
	default:
		errexit("usage:UDPdaytime [port]\n");
	}
	if (WSAStartup(WSVERS, &wsadata) != 0)
		errexit("WSAStartup failed\n");

	sock = passiveUDP(service);

	while (1)
	{
		alen = sizeof(struct sockaddr);
		if (recvfrom(sock, buf, sizeof(buf), 0, (struct sockaddr*)&fsin, &alen) == SOCKET_ERROR)
			errexit("recvfrom:error %d\n", GetLastError();
		(void)time(&now);
		pts = ctime(&now);
		(void)sendto(sock, pts, strlen(pts), 0, (struct sockaddr*)&fsin, sizeof(fsin));
	}
	return 1;
}
#endif // !connect_debug



#ifdef connect_debug
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<winsock.h>
#include<process.h>
#include<time.h>
#include "errexit.h"
#include "passivesocket.h"
#include "passTCP.h"
#pragma comment(lib,"ws2_32.lib")

#define QLEN 5
#define WSVERS MAKEWORD(2,0)
void TCPdaytimed(SOCKET);

int main(int argc, char* argv[])
{
	struct sockaddr_in fsin;
	char* service = (char*)"daytime";
	SOCKET msock,ssock;
	int alen;
	WSADATA wsadata;

	switch (argc)
	{
	case 1:
		break;
	case 2:
		service - argv[1];
		break;
	default:
		errexit("usage:TCPdaytimed [port]\n");
	}
	if (WSAStartup(WSVERS, &wsadata) != 0)
		errexit("WSAStartup failed\n");

	msock = passiveTCP(service,QLEN);

	printf("面向连接并发daytime服务器\n");

	while (1)
	{
		alen = sizeof(struct sockaddr);
		ssock = accept(msock, (struct sockaddr*)&fsin, &alen);

		if (ssock== INVALID_SOCKET)
			errexit("accept failed:error number %d\n", GetLastError());
		
		//通过beginthread来创建一个新的线程
		//方法不唯一
		if (_beginthread((void(*)(void*))TCPdaytimed,0, (void*)ssock )< 0)
		{
			errexit("_beginthread:%s\n", strerror(errno));
		}
	}
	return 1;
}
#endif // DEBUG

void TCPdaytimed(SOCKET fd)
{
	char* pts;
	time_t now;
	(void)time(&now);
	pts = ctime(&now);
	(void)send(fd, pts, strlen(pts), 0);
	(void)closesocket(fd);
}