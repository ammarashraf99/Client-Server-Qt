#include "commands/CreateCommand.h"
#include "core/Result.h"
#include "security/Security.h"
#include <QDebug>
#include <QFile>

CreateCommand::CreateCommand(const QStringList& args)
        :m_args(args)
{
}

CreateCommand::~CreateCommand() {}

bool CreateCommand::validate() const
{
        if (m_args.size() != 1) {
                return false;
        }
        if (Security::isRoot()) {
                return false;
        }
        // assuming that size is one..
        if (Security::isPath(m_args.first())) {
                return false;
        }
        return true;
}

Result CreateCommand::execute()
{
        QFile file(m_args.first());
        Result result;


        if (!file.open(QIODevice::NewOnly)) {
                result.Ok() = false;
                result.Message() = file.errorString().toUpper().replace(' ', '_');
                result.ErrorCode() = static_cast<int>(Result::ErrorCode::FILE_EXISTS);
        } else {
                result.Ok() = true;
                result.Message() = "OK";
                file.close();
        }
        return result;
}
