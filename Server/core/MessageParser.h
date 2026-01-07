#pragma once
#include <optional>
#include <QObject>
#include "core/Request.h"


class MessageParser {
public:
        static std::optional<Request> parse(QString line);

};
