#include "RenameCommand.h"
#include "Result.h"
#include "Security.h"
#include <QFile>
#include <QTextStream>


RenameCommand::RenameCommand(const QStringList& args)
        :m_args(args) {}

RenameCommand::~RenameCommand() {}

bool RenameCommand::validate() const
{
        if (m_args.size() != 2) {
                return false;
        }

        if (Security::isRoot()) {
                return false;
        }

        if (Security::isPath(m_args.first())) {
                return false;
        }
        if (Security::isPath(m_args.last())) {
                return false;
        }
        return true;
}

Result RenameCommand::execute()
{
        Result result;
        QString oldPath = m_args.first();
        QString newPath = m_args.last();

        if (!QFile::exists(oldPath)) {
                result.Ok() = false;
                result.Message() = "NO_SUCH_FILE_OR_DIRECTORY";
                result.ErrorCode() = static_cast<int>(Result::ErrorCode::NO_SUCH_FILE_OR_DIRECTORY);
                return result;
        }

        if (QFile::exists(newPath)) {
                result.Ok() = false;
                result.Message() = "FILE_EXISTS";
                result.ErrorCode() = static_cast<int>(Result::ErrorCode::FILE_EXISTS);
                return result;
        }

        if (!QFile::rename(oldPath, newPath)) {
                result.Ok() = false;
                result.Message() = "CANT_RENAME";
                result.ErrorCode() = static_cast<int>(Result::ErrorCode::CANT_RENAME_FILE);
                return result;
        }

        result.Ok() = true;
        result.Message() = "OK";
        return result;
}

