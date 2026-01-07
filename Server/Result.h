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

private:
        bool m_ok;
        QString m_message;
        int m_error_code;
};
