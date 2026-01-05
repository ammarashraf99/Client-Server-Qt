#include "ServerApplication.h"
#include "ConnectionWorker.h"
#include <QDebug>
#include <QThread>

ServerApplication::ServerApplication(QObject *parent)
        :QObject(parent)
{
        connect(&m_server, &QTcpServer::newConnection,
                this, &ServerApplication::onNewConnection);

        m_server.listen(QHostAddress::Any, 12345);
        qInfo() << "Started listening on port 12345";
}

void ServerApplication::onNewConnection()
{
        qDebug() << "New Connection";

        QTcpSocket* socket = m_server.nextPendingConnection();

        auto* thread = new QThread;
        auto* worker = new ConnectionWorker(socket);

        worker->moveToThread(thread);

        connect(thread, &QThread::started, worker, &ConnectionWorker::start);
        connect(worker, &QObject::destroyed, thread, &QThread::quit);
        connect(thread, &QThread::finished, thread, &QObject::deleteLater);

        thread->start();
}

