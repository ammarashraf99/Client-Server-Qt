#include "commands/InfoCommand.h"
#include "core/Result.h"
#include "security/Security.h"
#include <QFile>
#include <QTextStream>
#include <QFileInfo>

InfoCommand::InfoCommand(const QStringList& args)
        :m_args(args) {}

InfoCommand::~InfoCommand() {}

bool InfoCommand::validate() const
{
        if (m_args.size() != 1) {
                return false;
        }

        if (Security::isPath(m_args.first())) {
                return false;
        }

        if (Security::isRoot()) {
                return false;
        }

        return true;
}

Result InfoCommand::execute()
{
        Result result;
        QFileInfo info(m_args.first());

        if (!info.exists()) {
                result.Ok() = false;
                result.ErrorCode() = static_cast<int>(Result::ErrorCode::NO_SUCH_FILE_OR_DIRECTORY);
                result.Message() = "NO_SUCH_FILE_OR_DIRECTORY";
        } else {
                result.Ok() = true;
                result.Message() = "OK size = " + QString::number(info.size()) + " modified = " + info.lastModified().toString();
        }
        return result;
}
