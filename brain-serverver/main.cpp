#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "wsserver.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;

	WsServer *wsServer;
	wsServer = new WsServer(8080); // was 10010

	//bind object before load
	engine.rootContext()->setContextProperty("wsServer", wsServer); // forward c++ object that can be reached form qml by object name

	engine.load(QUrl(QStringLiteral("qrc:/main.qml")));


	//QObject *mainQml = engine.rootObjects().first(); // to access qml-s properties

	//mainQml->setProperty("clientsCount",0);




//	QObject::connect(wsServer,SIGNAL(newMessage(QString)),&cs,SLOT(handleMessage(QString)) );
//	QObject::connect(&cs, SIGNAL(sendNewPattern(int)), wsServer, SLOT(setFreeToPlay(int)));
//	QObject::connect(wsServer, SIGNAL(newPropertyValue(QString,double)), &cs, SLOT(handleChannelChange(QString,double)));
//	QObject::connect(wsServer, SIGNAL(newCodeToComplie(QString)) , &cs, SLOT(compileOrc(QString)));

    return app.exec();
}
