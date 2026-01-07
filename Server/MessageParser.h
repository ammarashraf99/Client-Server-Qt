#pragma once
#include <optional>
#include <QObject>
#include "Request.h"


class MessageParser {
public:
        static std::optional<Request> parse(QString line);

};
