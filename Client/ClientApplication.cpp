#include "ClientApplication.h"

ClientApplication::ClientApplication(QObject *parent)
        : QObject(parent),
          m_socket(new QTcpSocket(this)),
          m_stdinNotifier(new QSocketNotifier(fileno(stdin),
          QSocketNotifier::Read, this)),
          m_in(stdin),
          m_out(stdout)
{
        connect(m_socket, &QTcpSocket::connected,
                this, [] { qInfo() << "[INFO] Connected to server"; });

        connect(m_socket, &QTcpSocket::readyRead,
                this, &ClientApplication::onReadyRead);

        connect(m_socket, &QTcpSocket::disconnected,
                this, [] { qInfo() << "[INFO] Disconnected"; });

        connect(m_stdinNotifier, &QSocketNotifier::activated,
                this, &ClientApplication::onStdinReady);

        connectToServer("127.0.0.1" ,12345);
}

void ClientApplication::connectToServer(const QString &host, quint16 port)
{
        m_socket->connectToHost(host, port);
}

void ClientApplication::onStdinReady()
{
        QString line = m_in.readLine();
        if (line.isNull())
                return;

        m_socket->write(line.toUtf8());
        m_socket->write("\n");
}

void ClientApplication::onReadyRead()
{
        QByteArray data = m_socket->readAll();
        m_out << data;
        m_out.flush();
}
