#pragma once
#include <QStringList>
#include "commands/Command.h"
#include "core/Result.h"


class DeleteCommand : public Command
{
public:
        DeleteCommand(const QStringList& args);
        ~DeleteCommand();

        bool validate() const override;
        Result execute() override;

private:
        QStringList m_args;
};
