#pragma once
#ifndef __SOCKETWIN_H__
# define __SOCKETWIN_H__

#define _WINSOCK_DEPRECATED_NO_WARNINGS
# include <WinSock2.h>
# include <WS2tcpip.h>
# include <Windows.h>		//Include des socket Windows

#pragma comment(lib, "Ws2_32.lib")

# include <string>
# include <iostream>

# include "ISocketAbstract.h"

std::wstring	StringToWString(const std::string& s);

class SocketWin : public ISocketAbstract
{
private:
	WSADATA			_WSAData;		// Variable Initialisation des Socket Windows
private:
	SOCKET			_sock;
	SOCKADDR_IN		_csin;	// Info sur le socket
							// _cin.sin_addr.s_addr = inet_addr("127.0.0.1"); Client...
							// _cin.sin_addr.s_addr = htonl(INADDR_ANY); Serveur...
							// _cin.sin_family = AF_INET // Famille du Socket.
							// _cin.sin_port = htons(4148) // Le port d'écoute du Socket.
	int				_csinsize;
public:
	SocketWin(const std::string &ip, int port);
	SocketWin(SOCKET sock);
	~SocketWin();
public:
	virtual void	Init();
	virtual void	End();
	virtual bool	Socket(int af, int type, int protocole);
	virtual bool	Bind();
	virtual bool	Listen(int max);
	virtual bool	Send(ISocketAbstract *clientSocket, const std::string &msg);
	virtual bool	Close();
	virtual ISocketAbstract	*Accept();
public:
	SOCKET	getSocket() const;
};


#endif //__SOCKETWIN_H__
