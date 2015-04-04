#ifndef LIBNETWORK_H
#define LIBNETWORK_H

#include <deque>
#include <string>
#include <vector>

#ifdef WINSTORE
typedef int SOCKET;
#elif WIN32
#include <WinSock.h>
#else
typedef int SOCKET;
#endif

enum EventCode
{
	eNone,

	eFirstError,
	eCreateSocketError,
	eSetReuseAddrError,
	eBindError,
	eListenError,
	eAcceptError,
	eOtherSideClosedConnection,
	eConnectError,
	eLastError,

	eOtherSideConnected,
	eDataReceived,
	eDataSent,
};

const char* eventCodeString(EventCode eventCode);

struct NetworkEvent
{
	EventCode eventCode;
	std::vector<char> data;
	unsigned int id;
};

class QueueElement;

class NetworkBase
{
public:
	int sendData(const void* data, unsigned int size);
	void cancelSend();

	SOCKET clientSock() const
	{
		return clientSock_;
	}

	bool isConnected() const;

	int dataSent() const
	{
		return dataSent_;
	}
	
	int dataReceived() const
	{
		return dataReceived_;
	}
	
/*
  public:
	virtual void dataReceived(int id, const char* data, unsigned int size) {}
	//virtual void dataSent(int id) {}
	virtual void connected() {}
	virtual void disconnected() {}
*/

	
protected:
	NetworkBase();
	~NetworkBase();

	void tickSend(NetworkEvent* event);
	void tickRecv(NetworkEvent* event);

	void sendAck(unsigned int id);

	SOCKET clientSock_;
	unsigned short port_;

	std::deque<QueueElement*> sendQueue_;

	int dataSent_;
	int dataReceived_;

	void cleanup(void);

	char* receiveData_;
	unsigned int receiveId_;
	unsigned int receiveSize_;
	unsigned int receiveCurrent_;
	unsigned int receiveType_;
};

class Server : public NetworkBase
{
public:
	Server(unsigned short port);
	~Server();

	void tick(NetworkEvent* event);

	SOCKET serverSock() const
	{
		return serverSock_;
	}

private:
	SOCKET serverSock_;

	void cleanup(void);
};

class Client : public NetworkBase
{
public:
	Client(const char* ip, unsigned short port);
	~Client();

	void tick(NetworkEvent* event);

private:
	std::string ip_;
	bool connecting_;

	void cleanup(void);
};

#endif
