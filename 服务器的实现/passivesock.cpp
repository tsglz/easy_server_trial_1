#include<stdlib.h>
#include<string.h>
#include<winsock.h>
#include "passivesocket.h"
#include "errexit.h"


SOCKET passivesock(const char* service, const char* transport, int qlen)
{
	struct servent* pse;
	struct protoent* ppe;
	struct sockaddr_in sin;
	SOCKET s;
	int type;

	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = INADDR_ANY;

	if (pse = getservbyname(service, transport))
		sin.sin_port = (u_short)pse->s_port;
	else if ((sin.sin_port = htons((u_short)atoi(service))) == 0)
		errexit("can't get \"%s\" service entry\n", service);
	if ((ppe = getprotobyname(transport)) == 0)
		errexit("can't get \"%s\" protocol entry\n", transport);
	if (strcmp(transport, "udp") == 0)
		type = SOCK_DGRAM;
	else
		type = SOCK_STREAM;

	s = socket(PF_INET, type, ppe->p_proto);
	if (s == INVALID_SOCKET)
		errexit("can't create socket:%d\n", GetLastError());
	if (bind(s, (struct sockaddr*)&sin, sizeof(sin)) == SOCKET_ERROR)
		errexit("can't bind to %s port:%d\n", service, GetLastError());
	if (type == SOCK_STREAM && listen(s, qlen) == SOCKET_ERROR)
		errexit("can't listen on %s port:%d\n", service, GetLastError());
	return s;
}