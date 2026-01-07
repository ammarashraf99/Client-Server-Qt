#pragma once
#include <QObject>
#include <QTcpSocket>

class ConnectionWorker : public QObject {
        Q_OBJECT
 public:
        explicit ConnectionWorker(qintptr socketDescriptor, QObject *parent = nullptr);

signals:
        void finished();

public slots:
        void start();
private slots:
        void onReadyRead();
        void onDisconnected();

private:
        QTcpSocket *m_socket;
        qintptr m_sockDescriptor;
        bool m_isAuth;
        void handleLine(const QString& line);
};
