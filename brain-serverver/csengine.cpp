#include "csengine.h"
#include <QDebug>

#define PORT 7077

CsEngine::CsEngine(char *csd)
{
    mStop=false;
    m_csd = csd;
    errorValue=0;
    // UDP server to receive messages from other computer
    socket = new QUdpSocket(this); // The most common way to use QUdpSocket class is // to bind to an address and port using bind() // bool QAbstractSocket::bind(const QHostAddress & address, // quint16 port = 0, BindMode mode = DefaultForPlatform)
    socket->bind(QHostAddress::Any, 7077);
    qDebug()<<"Listening for UDP messages on port 7077";
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));


}


CsEngine::~CsEngine()
{
	stop();
	//free cs;

}


void CsEngine::readyRead()
{
     QByteArray buffer; buffer.resize(socket->pendingDatagramSize());
     QHostAddress sender;
     quint16 senderPort;

     socket->readDatagram(buffer.data(), buffer.size(), &sender, &senderPort);

	 //qDebug() << "UDP Message: " << buffer;
     QString message = QString(buffer);
     QStringList messageParts = message.split(","); // constructed: "sensor",channel, value, ie. "sensor,attention1,0.5"
    if (message.startsWith("sensor")) {
		QString sensor = messageParts[1];
		double value =  messageParts[2].toDouble();
		setChannel(sensor,value);
		emit newSensorValue(sensor,value);
    }

}


//Csound *CsEngine::getCsound() {return &cs;}

void CsEngine::run()
{

    //if ( open(m_csd)) {
    if ( cs.Compile(m_csd)) {
		qDebug()<<"Could not open csound file "<<m_csd;
        return;
    }
    CsoundPerformanceThread perfThread(&cs);
    perfThread.Play();

    // kas siin üldse performance threadi vaja? vt. soundcarpet v CsdPlayerQt

	QList <MYFLT> oldActive, active;
	oldActive <<  0 << 0 <<0; // perhaps there is better way to define an empty list;
	active <<  0 << 0 <<0;

	while (!mStop  && perfThread.GetStatus() == 0 ) {
		usleep(10000);  // ? et ei teeks tööd kogu aeg
		// do we need anything here?
	}
    qDebug()<<"Stopping thread";
    perfThread.Stop();
    perfThread.Join();
    mStop=false; // luba uuesti käivitamine
}

void CsEngine::stop()
{
    // cs.Reset();  // ?kills Csound at all
    mStop = true;

}

QString CsEngine::getErrorString()  // probably not necessry
{
    return errorString;
}

int CsEngine::getErrorValue()
{
    return errorValue;
}


MYFLT CsEngine::getChannel(QString channel)
{
    //qDebug()<<"setChannel "<<channel<<" value: "<<value;
	return cs.GetChannel(channel.toLocal8Bit());
}

void CsEngine::handleMessage(QString message)
{
	// message format: 'pattern' name voice repeatNtimes afterNsquares steps: pitch_index11 pitch_index2
	qDebug()<<"Message in csound: "<<message;
	//vaja midagi nagu: 1) compileOrc( giMatrix[voice][0] = step1 etc fillarray )  2) ;schedule "playPattern",0,0,nTimes, afterNsquares

	if (message.startsWith("clear") || message.startsWith("mode")) {
		return;
	}
	QStringList messageParts = message.split(",");
	QString voice = messageParts[2];
	QString repeatNtimes = messageParts[3];
	QString afterNSquares = messageParts[4];
	QString panOrSpeaker = messageParts[5];
	// prepare steps for compileOrc:
	QString code = "";
	for (int j=0, i=messageParts.indexOf("steps:")+1 ; i<messageParts.length(); i++, j++ ) { // statements to store steps into 2d array giMartix[voice][step]
		code += "giMatrix["+voice+"]["+QString::number(j) + "] = " + messageParts[i] +  "\n";
	}

	code += "\nschedule \"playPattern\",0,0," + repeatNtimes + "," + afterNSquares + "," + voice + "," + panOrSpeaker;
	qDebug()<<"Message to compile: "<<code;
	compileOrc(code);

}

int CsEngine::compileOrc(QString code)
{

	//qDebug()<<"Code to compile: "<<code;
	return  cs.CompileOrc(code.toLocal8Bit());

}

void CsEngine::restart()
{
    stop(); // sets mStop true
    while (mStop) // run sets mStop false again when perftrhead has joined
        usleep(100000);
	start();
}

void CsEngine::handleChannelChange(QString channel, double value)
{
	setChannel(channel, (MYFLT) value);
}

void CsEngine::setChannel(QString channel, MYFLT value)
{
    //qDebug()<<"setChannel "<<channel<<" value: "<<value;
    cs.SetChannel(channel.toLocal8Bit(), value);
}

void CsEngine::csEvent(QString event_string)
{
    cs.InputMessage(event_string.toLocal8Bit());
}
