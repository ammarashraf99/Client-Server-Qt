#pragma once
#include <QStringList>
#include "Result.h"
#include "WriteCommand.h"

class AppendCommand final : public WriteCommand
{
public:
        AppendCommand(const QStringList& args);
        Result execute() override;
};
