#include<stdarg.h>
#include<stdio.h>
#include<stdlib.h>
#include<winsock.h>
#include "errexit.h"

void errexit(const char* format, ...)
{
	va_list args;
	va_start(args, format);
	vfprintf(stderr, format, args);
	va_end(args);
	WSACleanup();	//�쳣�˳�ҲҪ�����̬���ӿ���Դռ��
	exit(1);
}