#include<winsock.h>
#include "passivesocket.h"
#include "passUDP.h"

SOCKET passiveUDP(const char* service)
{
	return passivesock(service, "udp", 0);
}