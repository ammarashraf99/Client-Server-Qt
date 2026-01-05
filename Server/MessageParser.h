#pragma once
#include <optional>
#include <QObject>

struct Request {
        QString command;
        QStringList arguments;
};

class MessageParser {
public:
        static std::optional<Request> parse(QString line);

};
