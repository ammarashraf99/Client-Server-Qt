#pragma once
#include <QStringList>
#include "commands/Command.h"
#include "core/Result.h"

class CreateCommand final : public Command
{
public:
        CreateCommand(const QStringList& args);
        ~CreateCommand();

        bool validate() const override;
        Result execute() override;

private:
        QStringList m_args;
};
