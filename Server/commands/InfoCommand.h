#pragma once
#include <QStringList>
#include "commands/Command.h"
#include "core/Result.h"

class InfoCommand : public Command
{
public:
        InfoCommand(const QStringList& args);
        ~InfoCommand();

        bool validate() const override;
        Result execute() override;

private:
        QStringList m_args;
};
