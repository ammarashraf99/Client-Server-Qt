#include "commands/ReadCommand.h"
#include "security/Security.h"
#include "core/Result.h"
#include <QFile>
#include <QTextStream>

ReadCommand::ReadCommand(const QStringList& args)
        :m_args(args) {}

ReadCommand::~ReadCommand() {}

bool ReadCommand::validate() const
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

Result ReadCommand::execute()
{
        QFile file(m_args.first());
        Result result;

        if (!file.open(QIODevice::ReadOnly | QIODevice::ExistingOnly | QIODevice::Text)) {
                result.Ok() = false;
                result.Message() = file.errorString().toUpper().replace(' ', '_');

                switch (file.error()) {
                case QFile::FileError::OpenError:
                        result.ErrorCode() = static_cast<int>(Result::ErrorCode::NO_SUCH_FILE_OR_DIRECTORY);
                        break;
                case QFile::FileError::ReadError:
                        result.ErrorCode() = static_cast<int>(Result::ErrorCode::READ_ERROR);
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
                QTextStream inStream(&file);
                inStream.setEncoding(QStringConverter::Utf8);
                result.Ok() = true;
                result.Message() = "OK " + QString::number(file.size()) + "\n" + inStream.readAll();
                file.close();
        }
        return result;
}
