#include<winsock.h>
#include "passTCP.h"
#include "passivesocket.h"

SOCKET passiveTCP(const char* service,int qlen)
{
	return passivesock(service, "tcp", qlen);
}