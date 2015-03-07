#include "wsserver.h"
#include "QtWebSockets/qwebsocketserver.h"
#include "QtWebSockets/qwebsocket.h"
#include <QDebug>


QT_USE_NAMESPACE


WsServer::WsServer(quint16 port, QObject *parent) :
    QObject(parent),
	m_pWebSocketServer(new QWebSocketServer(QStringLiteral("PatternServer"),
                                            QWebSocketServer::NonSecureMode, this)),
    m_clients()
{
    if (m_pWebSocketServer->listen(QHostAddress::Any, port)) {
        qDebug() << "WsServer listening on port" << port;
        connect(m_pWebSocketServer, &QWebSocketServer::newConnection,
                this, &WsServer::onNewConnection);
        connect(m_pWebSocketServer, &QWebSocketServer::closed, this, &WsServer::closed);
    }
    cs = new CsEngine("../braingame.csd"); cs->start();


}


WsServer::~WsServer()
{
    m_pWebSocketServer->close();
    qDeleteAll(m_clients.begin(), m_clients.end());
}


void WsServer::onNewConnection()
{
    QWebSocket *pSocket = m_pWebSocketServer->nextPendingConnection();

    connect(pSocket, &QWebSocket::textMessageReceived, this, &WsServer::processTextMessage);
    //connect(pSocket, &QWebSocket::binaryMessageReceived, this, &WsServer::processBinaryMessage);
    connect(pSocket, &QWebSocket::disconnected, this, &WsServer::socketDisconnected);

    m_clients << pSocket;
    emit newConnection(m_clients.count());
	//pSocket->sendTextMessage("Hi");
}


void WsServer::processTextMessage(QString message)
{
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
    if (!pClient) {
        return;
    }
	qDebug()<<message;

	// messages that come in: csound,name,code2compile; comment,display,comment_text (- display, don't compile; message, name,

    QStringList messageParts = message.split("*");
	QString name = messageParts[1];
	if (message.startsWith("csound")) { // send code to compile and return result to caller
		QString code = messageParts[2];
		emit newMessage(name,code);
        int result = cs->compileOrc(code);
		// if (!result)
		QString returnMessage = (result) ? "Error" : "OK";
		emit newMessage("Csound",returnMessage);
		pClient->sendTextMessage("result,"+returnMessage);
	} else if (message.startsWith("comment")) { // send code to be displayed but not compiled
		QString comment = messageParts[2];
		emit newMessage(name,comment);
        //sendToAll(name+":"+comment, pClient);
    } else if (message.startsWith("message")) {  // don't display, only to peers
        sendToAll(name+":"+messageParts[2], pClient);
    }






}

//void WsServer::processBinaryMessage(QByteArray message)
//{
//    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
//    if (pClient) {
//        pClient->sendBinaryMessage(message);
//    }
//}

void WsServer::socketDisconnected()
{
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
    if (pClient) {
        m_clients.removeAll(pClient);
        emit newConnection(m_clients.count());
        pClient->deleteLater();
	}
}

void WsServer::sendToAll(QString message, QWebSocket *sender)
{
	foreach (QWebSocket *socket, m_clients) {
		if ( sender != NULL && socket != sender) // if sender is set, don't send back to itself
			socket->sendTextMessage(message);
	}
}


void WsServer::sendMessage(QWebSocket *socket, QString message )
{
    if (socket == 0)
    {
        return;
    }
    socket->sendTextMessage(message);

}


