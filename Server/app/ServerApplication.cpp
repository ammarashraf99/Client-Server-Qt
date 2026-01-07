#include "app/ServerApplication.h"
#include "net/ConnectionWorker.h"
#include <QDebug>
#include <QThread>

ServerApplication::ServerApplication(QObject *parent)
        :QTcpServer(parent)
{
        this->listen(QHostAddress::Any, 12345);
        qInfo() << "[INFO] Started listening on port 12345";
}

void ServerApplication::incomingConnection(qintptr socketDescriptor)
{
        qInfo() << "[INFO] New Connection";
        QThread *thread = new QThread;
        ConnectionWorker *worker = new ConnectionWorker(socketDescriptor);

        worker->moveToThread(thread);

        connect(thread, &QThread::started,
                worker, &ConnectionWorker::start);

        connect(worker, &ConnectionWorker::finished,
                thread, &QThread::quit);

        connect(worker, &ConnectionWorker::finished,
                worker, &QObject::deleteLater);

        connect(thread, &QThread::finished,
                thread, &QObject::deleteLater);

        thread->start();
}

