#include "commands/WriteCommand.h"
#include "core/Result.h"
#include "security/Security.h"
#include <QFile>
#include <QTextStream>


WriteCommand::WriteCommand(const QStringList& args)
        :m_args(args)
{
}

WriteCommand::~WriteCommand() {}


bool WriteCommand::validate() const
{
        if (m_args.size() != 2) {
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

Result WriteCommand::execute()
{
        QFile file(m_args.first());
        Result result;

        if (!file.open(QIODevice::WriteOnly | QIODevice::ExistingOnly | QIODevice::Text)) {
                result.Ok() = false;
                result.Message() = file.errorString().toUpper().replace(' ', '_');

                switch (file.error()) {
                case QFile::FileError::OpenError:
                        result.ErrorCode() = static_cast<int>(Result::ErrorCode::NO_SUCH_FILE_OR_DIRECTORY);
                        break;
                case QFile::FileError::WriteError:
                        result.ErrorCode() = static_cast<int>(Result::ErrorCode::WRITE_ERROR);
                        break;
                case QFile::FileError::PermissionsError:
                        result.ErrorCode() = static_cast<int>(Result::ErrorCode::PERMISSION_ERROR);
                        break;
                default:
                        result.ErrorCode() = static_cast<int>(Result::ErrorCode::UNKNOWN_ERROR);
                        result.Message() = "UNKNOWN_ERROR";
                        break;
                }
        } else {
                QTextStream outStream(&file);
                outStream << m_args.last();
                file.close();
                result.Ok() = true;
                result.Message() = "OK data written successfully";
        }

        return result;
}
