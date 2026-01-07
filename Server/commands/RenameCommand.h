#pragma once
#include <QStringList>
#include "commands/Command.h"
#include "core/Result.h"

class RenameCommand : public Command
{
public:
        RenameCommand(const QStringList& args);
        ~RenameCommand();

        bool validate() const override;
        Result execute() override;

private:
        QStringList m_args;
};
