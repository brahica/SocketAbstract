#pragma once
#ifndef		__ISOCKETSABSTRACT_H__
# define	__ISOCKETSABSTRACT_H__

# include <string>


class ISocketAbstract
{
public:
	virtual void	Init() = 0;
	virtual void	End() = 0;
	virtual bool	Socket(int af, int type, int protocole) = 0;
	virtual bool	Listen(int max) = 0;
	virtual bool	Bind() = 0;
	virtual bool	Send(ISocketAbstract *clientSocket, const std::string &msg) = 0;
	virtual bool	Close() = 0;
	virtual SOCKET	getSocket() const = 0;
	virtual ISocketAbstract	*Accept() = 0;
};


#endif // __ISOCKETSABSTRACT_H__
