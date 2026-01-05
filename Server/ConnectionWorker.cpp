#include "ConnectionWorker.h"
#include "MessageParser.h"


ConnectionWorker::ConnectionWorker(qintptr sd)
        :m_sockDescriptor(sd)
{
        m_socket = new QTcpSocket(this);
}

void ConnectionWorker::start()
{
        qDebug() << "Begin start()";

        m_socket->setSocketDescriptor(m_sockDescriptor);

        connect(m_socket, &QTcpSocket::readyRead, this, &ConnectionWorker::onReadyRead);

        connect(m_socket, &QTcpSocket::disconnected, m_socket, &QObject::deleteLater);
        qDebug() << "End start()";
}

void ConnectionWorker::onReadyRead()
{
        while( m_socket->canReadLine() ) {
                qDebug() << "onReadyRead";
                QString line = m_socket->readAll();
                m_socket->write("Waaer");
                handleLine(line);
        }
}

void ConnectionWorker::handleLine(const QString& line)
{
        qDebug() << "Started handling line";
        std::optional<Request> req = MessageParser::parse(line);

        if (!req)
                return;

        qDebug() << "Command is " << req.value().command;

        qDebug() << "Args are:";
        for(auto arg : req.value().arguments)
        {
                qDebug() << arg;
        }


        // validate

        // commands factory...

        // dispatch

        // result socket write... success of fail
}


