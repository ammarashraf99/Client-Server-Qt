#pragma once
#include "qtcpserver.h"
#include <QObject>
#include <QTcpServer>


class ServerApplication : public QTcpServer {
        Q_OBJECT
 public:
        explicit ServerApplication(QObject *parent = nullptr);

protected:
        void incomingConnection(qintptr socketDescriptor) override;

// private slots:
//         void onNewConnection();

private:
        QTcpServer m_server;
};

