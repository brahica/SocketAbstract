#include "SocketWin.h"

SocketWin::SocketWin(const std::string &ip, int port)
{
	this->_csin.sin_family = AF_INET;
	std::cout << "[WIN] Create Socket ";
	if (ip == "") // Serveur
	{
		std::cout << "Serveur ";
		this->_csin.sin_addr.s_addr = INADDR_ANY;
	}
	else // Client
	{
		this->_csin.sin_addr.s_addr = inet_addr(ip.c_str());
		std::cout << "Client IP : " << ip;
	}
	this->_csin.sin_port = htons(port);
	std::cout << " Port : " << port << std::endl;
	this->_csinsize = sizeof(_csin);
}

SocketWin::SocketWin(SOCKET sock)
{
	this->_sock = sock;
	this->_csinsize = sizeof(_csin);
}

SocketWin::~SocketWin()
{
}

void	SocketWin::Init()
{
	int		iResult;
	iResult = WSAStartup(MAKEWORD(2, 2), &_WSAData);
	if (iResult != 0)
		std::cerr << "[WIN] WSAStartup failed: " << iResult << std::endl;
}

void	SocketWin::End()
{
	WSACleanup();
}

bool	SocketWin::Socket(int af, int type, int protocole)
{
	_sock = socket(af, type, protocole);
	if (_sock == INVALID_SOCKET)
	{
		std::cerr << "[WIN] Socket function failed with error = " << WSAGetLastError() << std::endl;
		return (false);
	}
	std::cout << "[WIN] Socket function succeeded" << std::endl;
	return (true);
}

bool	SocketWin::Bind()
{
	if (bind(this->_sock, (SOCKADDR *) &_csin, sizeof(_csin)) == SOCKET_ERROR)
	{
		std::cerr << "[WIN] bind failed with error " << WSAGetLastError() << std::endl;
		return (false);
	}
	return (true);
}

bool	SocketWin::Listen(int max)
{
	if (listen(this->_sock, max) == SOCKET_ERROR) {
		std::cerr << "[WIN] Listen failed with error: " << WSAGetLastError() << std::endl;
		return (false);
	}
	return (true);
}

ISocketAbstract	*SocketWin::Accept()
{
	SOCKET	csock;
	csock = accept(this->_sock, (SOCKADDR *)(&this->_csin), &this->_csinsize);
	return (new SocketWin(csock));
}

bool	SocketWin::Send(ISocketAbstract *clientSocket, const std::string &msg)
{
	if (send(clientSocket->getSocket(), msg.c_str(), msg.length(), 0) == SOCKET_ERROR)
	{
		std::cerr << "[WIN] Send failed: " << WSAGetLastError() << std::endl;
		return (false);
	}
	return (true);
}

bool	SocketWin::Close()
{
	if (closesocket(this->_sock) == 0)
		return (true);	
	return (false);
}

SOCKET	SocketWin::getSocket()	const
{
	return (this->_sock);
}
