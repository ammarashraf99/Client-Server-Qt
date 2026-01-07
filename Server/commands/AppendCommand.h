#pragma once
#include <QStringList>
#include "core/Result.h"
#include "commands/WriteCommand.h"

class AppendCommand final : public WriteCommand
{
public:
        AppendCommand(const QStringList& args);
        Result execute() override;
};
