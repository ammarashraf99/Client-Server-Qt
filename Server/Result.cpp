#include "Result.h"

Result::Result(bool ok, QString message, int error_code)
        :m_ok(ok), m_message(message), m_error_code(error_code)
{
}

QString Result::Response()
{
        if (m_ok) {
                return m_message;
        } else {
                return "ERROR " + QString::number(m_error_code)+" "+m_message;
        }
}

