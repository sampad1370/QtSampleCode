#pragma once
#include <QTcpSocket>
#include <QTcpServer>
#include <QHostAddress>
#include <QMap>

enum class MessageIdType:uint16_t
{
	PowerOn,PowerOff,Restart,Update
};
struct Message
{
	uint8_t address;
	MessageIdType id;
	uint32_t number;
	uint32_t size;
	//and so on...I Use this to fix size of Message structure.
};

class Client : public QObject
{
	Q_OBJECT
public:
	Client(QObject* parent = nullptr);
	bool isConnected();
private:
	void doConnect();
	void write(QByteArray data);
	Message deserialize(QByteArray rawaData);

	//get same signature for all function to use in map/function
	bool powerOn(Message);
	bool powerOff(Message);
	bool restart(Message);
	bool update(Message);

private slots:
	void handleData();
	void onNewConnection();
	void onDisconnected();
	void onByteWritten(qint64 bytes);

private:
	QTcpServer*														m_tcpServer = nullptr;
	QTcpSocket*														m_tcpSocket = nullptr;
	bool															m_isConnected = false;
	QMap<MessageIdType,std::function<bool(Message)>> m_functions;

};