#include "ConnectionWorker.h"
#include "MessageParser.h"


ConnectionWorker::ConnectionWorker(QTcpSocket* socket)
        :m_socket(socket)
{
}

void ConnectionWorker::start()
{
        connect(m_socket, &QTcpSocket::readyRead,
                this, &ConnectionWorker::onReadyRead);

        connect(m_socket, &QTcpSocket::disconnected,
                m_socket, &QObject::deleteLater);
}

void ConnectionWorker::onReadyRead()
{
        qDebug() << "onReadyRead";
        QString line = m_socket->readAll();
        handleLine(line);
}

void ConnectionWorker::handleLine(const QString& line)
{
        qDebug() << "Started handling line";
        std::optional<Request> req = MessageParser::parse(line);

        if (!req)
                return;

        qDebug() << "Command is [ " << req.value().command << " ]";

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


