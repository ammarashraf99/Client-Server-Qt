#include "ConnectionWorker.h"
#include "Command.h"
#include "MessageParser.h"
#include "CommandFactory.h"
#include "Result.h"
#include <memory>


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

        Result result;

        // 127 command not found (exit code shell/processes)
        std::optional<Request> req = MessageParser::parse(line);
        if (!req) {
                result.Ok() = false;
                result.Message() = "COMMAND_NOT_FOUND";
                result.ErrorCode() = 127;
                m_socket->write(result.Response().toUtf8());
                return;
        }

        // commands factory...
        // should not return an error
        std::unique_ptr<Command> command = CommandFactory::create(req.value());

        // validate
        // BAD REQUEST error 400 (https)
        if (!command->validate()) {
                result.Ok() = false;
                result.Message() = "BAD_REQUEST";
                result.ErrorCode() = 400;
                m_socket->write(result.Response().toUtf8());
                return;
        }

        // execute the command
        result = command->execute();

        m_socket->write(result.Response().toUtf8());
        return;
}


