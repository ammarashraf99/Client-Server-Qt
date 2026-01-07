#pragma once
#include <QStringList>
#include "Command.h"
#include "Result.h"


class AuthCommand final : public Command
{
public:
        AuthCommand(QStringList args);
        ~AuthCommand();

        bool validate() const override;
        Result execute() override;


private:
        QStringList m_args;

        struct {
                QString User = "admin";
                QString Pass = "admin";
        }Credentials;
};

