#pragma once
#include <QStringList>
#include "commands/Command.h"
#include "core/Result.h"

class ReadCommand : public Command
{
public:
        ReadCommand(const QStringList& args);
        ~ReadCommand();

        bool validate() const override;
        Result execute() override;

private:
        QStringList m_args;
};
