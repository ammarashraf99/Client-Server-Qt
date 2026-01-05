#pragma once
#include <QObject>
#include <QTcpServer>


class ServerApplication : public QObject {
        Q_OBJECT
 public:
        explicit ServerApplication(QObject *parent = nullptr);


private slots:
        void onNewConnection();

private:
        QTcpServer m_server;
};

