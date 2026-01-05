#include "MessageParser.h"
#include <utility>

std::optional<Request> MessageParser::parse(QString line)
{
        Request req;
        // trim line
        line = line.trimmed();
        req.command = line.section(' ', 0, 0);

        QStringList lineList = line.section(' ', 1, -1).split(';');
        for (auto& el : lineList) {
                el = el.trimmed();
        }
        req.arguments = std::move(lineList);

        return req;
}
