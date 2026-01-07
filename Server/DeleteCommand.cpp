#include "DeleteCommand.h"
#include "Result.h"
#include "Security.h"
#include <QFile>
#include <QTextStream>


DeleteCommand::DeleteCommand(const QStringList& args)
        :m_args(args) {}

DeleteCommand::~DeleteCommand() {}

bool DeleteCommand::validate() const
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

Result DeleteCommand::execute()
{
        Result result;
        if (!QFile::exists(m_args.first())) {
                result.Ok() = false;
                result.Message() = "NO_SUCH_FILE_OR_DIRECTORY";
                result.ErrorCode() = static_cast<int>(Result::ErrorCode::NO_SUCH_FILE_OR_DIRECTORY);
        } else if (!QFile::remove(m_args.first())) {
                result.Ok() = false;
                result.Message() = "CANT_DELETE_FILE";
                result.ErrorCode() = static_cast<int>(Result::ErrorCode::CANT_DELETE_FILE);
        } else {
                result.Ok() = true;
                result.Message() = "OK";
        }

        return result;
}
