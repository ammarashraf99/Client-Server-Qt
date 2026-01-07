#pragma once
#include <QStringList>
#include "Command.h"
#include "Result.h"

class WriteCommand : public Command
{
public:
        WriteCommand(const QStringList& args);
        ~WriteCommand();

        bool validate() const override;
        Result execute() override;

protected:
        QStringList m_args;
};

