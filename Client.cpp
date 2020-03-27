#include "Client.h"
#include <iostream>
using namespace std;

Client::Client(QObject* parent):QObject(parent)
{
	m_tcpServer = new QTcpServer(this);
	connect(m_tcpServer, &QTcpServer::newConnection, this, &Client::onNewConnection);

	using std::placeholders::_1;
	m_functions.insert(MessageIdType::PowerOff, std::bind(&Client::powerOff, this, _1));
	m_functions.insert(MessageIdType::PowerOn, std::bind(&Client::powerOn, this, _1));
	m_functions.insert(MessageIdType::Restart, std::bind(&Client::restart, this, _1));
	m_functions.insert(MessageIdType::Update, std::bind(&Client::update, this, _1));

	// do blew lines in process data function
	QByteArray data;
	Message message= deserialize(data);
	m_functions[message.id](message);
}

bool Client::isConnected()
{
	return m_isConnected;
}

void Client::doConnect()
{

}

void Client::write(QByteArray data)
{

}

Message Client::deserialize(QByteArray rawaData)
{
	//in example for test I make a PowerOn Message Id type and return always.
	Message message;
	message.address = 0;
	message.id = MessageIdType::Update;
	message.number = 0;
	message.size = 0;
	return message;
}

bool Client::powerOn(Message)
{
	cout << "Power On System." << endl;
	return true;
}

bool Client::powerOff(Message)
{
	cout << "Power Off System." << endl;
	return true;
}

bool Client::restart(Message)
{
	cout << "Restart System." << endl;
	return true;
}

bool Client::update(Message)
{
	cout << "Updating System." << endl;
	return true;
}

void Client::handleData()
{

}

void Client::onNewConnection()
{

}

void Client::onDisconnected()
{

}

void Client::onByteWritten(qint64 bytes)
{

}

