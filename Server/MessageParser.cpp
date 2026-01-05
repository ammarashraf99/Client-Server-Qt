#include "MessageParser.h"
#include <utility>

std::optional<Request> MessageParser::parse(QString line)
{
        Request req;
        // trim line
        line = line.trimmed();
        req.command = line.section(' ', 0, 0);

        QStringList lineList = line.split(';');
        req.arguments = std::move(lineList);

        return req;
}
