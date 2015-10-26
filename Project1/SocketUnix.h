#pragma once
#ifndef		__SOCKETUNIX_H__
# define	__SOCKETUNIX_H__


#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h> /* close */
#include <netdb.h> /* gethostbyname */

#include "ISocketAbstract.h"

typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef struct in_addr IN_ADDR;

class SocketUnix : ISocketAbstract
{
private:
	SOCKET			_sock;
	SOCKADDR_IN		_csin;	// Info sur le socket
							// _cin.sin_addr.s_addr = inet_addr("127.0.0.1"); Client...
							// _cin.sin_addr.s_addr = htonl(INADDR_ANY); Serveur...
							// _cin.sin_family = AF_INET // Famille du Socket.
							// _cin.sin_port = htons(4148) // Le port d'écoute du Socket.
public:
	SocketUnix(const std::string &ip, int port);
	~SocketUnix();
public:
	virtual void	Init();
	virtual void	End();
	virtual bool	Socket(int af, int type, int protocole);
	virtual bool	Bind();

	//virtual Accept() = 0;
	//virtual Listen() const = 0;
	//virtual Close() const = 0;
};

#endif		//__SOCKETUNIX_H__