#include <QCoreApplication>
#include <QTcpSocket>
#include <QSocketNotifier>
#include <QTextStream>
#include <QObject>


class ClientApplication : public QObject
{
        Q_OBJECT

 public:
        ClientApplication(QObject *parent = nullptr);

        void connectToServer(const QString &host, quint16 port);

private slots:
        void onStdinReady();
        void onReadyRead();

 private:
                QTcpSocket *m_socket;
                QSocketNotifier *m_stdinNotifier;
                QTextStream m_in;
                QTextStream m_out;
};

