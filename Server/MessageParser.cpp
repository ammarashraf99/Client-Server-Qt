#include "MessageParser.h"
#include "Command.h"
#include <optional>
#include <utility>


std::optional<Request> MessageParser::parse(QString line)
{
        Request req;
        line = line.trimmed();
        req.command = line.section(' ', 0, 0);

        if (!Command::isCommand(req.command.toStdString())) {
                return std::nullopt;
        }

        QStringList lineList = line.section(' ', 1, -1).split(';');
        for (auto& el : lineList) {
                el = el.trimmed();
        }
        req.arguments = std::move(lineList);


        return req;
}
