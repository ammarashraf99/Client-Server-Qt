#pragma once
#include <QStringList>
#include "Command.h"
#include "Result.h"

class ListCommand : public Command
{
public:
        ListCommand(const QStringList& args);
        ~ListCommand();

        bool validate() const override;
        Result execute() override;

private:
        QStringList m_args;
};
