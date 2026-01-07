#include "AuthCommand.h"
#include "Result.h"


AuthCommand::AuthCommand(QStringList args)
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
        if (m_args.first() == Credentials.User && m_args.last() == Credentials.Pass) {
                Result res(true, "OK");
                return res;
        } else {
                Result res(false, "UNAUTHORIZED_ACCESS", 401);
                return res;
        }
}
