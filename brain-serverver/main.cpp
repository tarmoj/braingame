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


	QObject *mainQml = engine.rootObjects().first(); // to access qml-s properties
	wsServer->setQmlObject(mainQml);
	/*mainQml->setProperty("clientsCount",8);
	mainQml->setProperty("attention1",0.25);*/



    return app.exec();
}
