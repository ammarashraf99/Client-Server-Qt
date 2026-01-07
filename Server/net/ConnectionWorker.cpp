#include "net/ConnectionWorker.h"
#include "commands/Command.h"
#include "core/MessageParser.h"
#include "commands/CommandFactory.h"
#include "core/Result.h"
#include <memory>


ConnectionWorker::ConnectionWorker(qintptr socketDescriptor, QObject *parent)
        :QObject(parent), m_sockDescriptor(socketDescriptor), m_isAuth(false)
{
}


void ConnectionWorker::start()
{
        m_socket = new QTcpSocket(this);

        if (!m_socket->setSocketDescriptor(m_sockDescriptor)) {
                qWarning() << "[Warning] Failed to set socket descriptor";
                emit finished();
                return;
        }

        connect(m_socket, &QTcpSocket::readyRead,
                this, &ConnectionWorker::onReadyRead);

        connect(m_socket, &QTcpSocket::disconnected,
                this, &ConnectionWorker::onDisconnected);
}


void ConnectionWorker::onDisconnected()
{
        qInfo() << "[INFO] Client Disconnected";

        m_socket->deleteLater();
        emit finished();
}


void ConnectionWorker::onReadyRead()
{
        QString line = m_socket->readAll();
        handleLine(line);
}

void ConnectionWorker::handleLine(const QString& line)
{
        qInfo() << "[INFO] Started handling line";

        Result result;

        // 127 command not found (exit code shell/processes)
        std::optional<Request> req = MessageParser::parse(line);
        if (!req) {
                result.Ok() = false;
                result.Message() = "COMMAND_NOT_FOUND";
                result.ErrorCode() = static_cast<int>(Result::ErrorCode::COMMAND_NOT_FOUND);
                m_socket->write(result.Response().toUtf8() + "\n");
                return;
        }

        // check if authorized
        if (!m_isAuth && req->command != "AUTH") {
                result.Ok() = false;
                result.Message() = "UNAUTHORIZED_ACCESS";
                result.ErrorCode() = static_cast<int>(Result::ErrorCode::UNAUTHORIZED_ACCESS);
                m_socket->write(result.Response().toUtf8() + "\n");
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
                result.ErrorCode() = static_cast<int>(Result::ErrorCode::BAD_REQUEST);
                m_socket->write(result.Response().toUtf8() + "\n");
                return;
        }

        // execute the command
        result = command->execute();
        if (result.Ok() && req->command == "AUTH") {
                m_isAuth = true;
        }

        m_socket->write(result.Response().toUtf8() + "\n");
        return;
}

