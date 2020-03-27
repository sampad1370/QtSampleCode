#include <QtCore/QCoreApplication>
#include "Client.h"


int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	Client client;

	return a.exec();
}
