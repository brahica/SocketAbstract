#include <iostream>

#if defined(WIN32) && !defined(UNIX)
# include "SocketWin.h"
#elif defined(UNIX) && !defined(WIN32)
# include "SocketUnix.h"
#else
/* Error, both can't be defined or undefined same time */
#endif

int	main()
{
	ISocketAbstract		*absSocket = NULL;
	ISocketAbstract		*absSocketClient = NULL;


#if defined(WIN32) && !defined(UNIX)
	absSocket = new SocketWin("", 4242);
	std::cout << "* Running in Windows env *" << std::endl;
#elif defined(UNIX) && !defined(WIN32)
	absSocket = new SocketUnix(NULL, 4242);
	std::cout << "* Running in UNIX env *" << std::endl;
#else
	/* Error, both can't be defined or undefined same time */
#endif


	absSocket->Init();
	absSocket->Socket(AF_INET, SOCK_STREAM, 0);
	absSocket->Bind();
	absSocket->Listen(5);
	while (1)
	{
		absSocketClient = absSocket->Accept();
		if (absSocketClient->getSocket() == INVALID_SOCKET)
		{
			absSocket->Send(absSocketClient, "Hello world!\n");
			absSocketClient->Close();
		}
	}
	return (0);
}