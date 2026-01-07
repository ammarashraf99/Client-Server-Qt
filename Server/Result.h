#pragma once
#include <QString>

class Result
{
public:
        Result(bool ok, QString message, int error_code = -1);
        Result() = default;

        QString Response();

        bool& Ok() {return m_ok;}
        QString& Message() {return m_message;}
        int& ErrorCode() {return m_error_code;}

        enum class ErrorCode {
                UNAUTHORIZED_ACCESS = 401,
                BAD_REQUEST = 400,
                COMMAND_NOT_FOUND = 127,
                FILE_EXISTS = 58,
                NO_SUCH_FILE_OR_DIRECTORY = 59,
                WRITE_ERROR = 73,
                READ_ERROR = 74,
                PERMISSION_ERROR = 13,
                UNKNOWN_ERROR = 520,
                CANT_DELETE_FILE = 433,
                CANT_RENAME_FILE = 433,
        };

private:
        bool m_ok;
        QString m_message;
        int m_error_code;
};
