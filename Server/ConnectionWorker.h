#pragma once
#include <QObject>
#include <QTcpSocket>

class ConnectionWorker : public QObject {
        Q_OBJECT
 public:
        explicit ConnectionWorker(qintptr sd);

public slots:
        void start();
        void onReadyRead();
private:
        QTcpSocket *m_socket;
        qintptr m_sockDescriptor;

        // command dispatcher

        void handleLine(const QString& line);
};

