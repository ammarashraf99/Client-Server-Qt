#include "commands/AuthCommand.h"
#include "core/Result.h"
#include <QDebug>


AuthCommand::AuthCommand(const QStringList& args)
        :m_args(args)
{
}

AuthCommand::~AuthCommand() {}

bool AuthCommand::validate() const
{
        // should be on argument
        if (m_args.size() != 1) {
                return false;
        }

        QStringList usr_pass = m_args.first().split(',');
        if(usr_pass.size() != 2) {
                return false;
        }

        return true;
}


Result AuthCommand::execute()
{
        m_args = m_args.first().split(',');

        if (m_args.first() == m_Credentials.User && m_args.last() == m_Credentials.Pass) {
                Result res(true, "OK");
                return res;
        } else {
                Result res(false, "UNAUTHORIZED_ACCESS",
                           static_cast<int>(Result::ErrorCode::UNAUTHORIZED_ACCESS));
                return res;
        }
}
