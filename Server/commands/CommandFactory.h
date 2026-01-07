#pragma once
#include "commands/Command.h"
#include "core/Request.h"
#include <memory>


class CommandFactory
{
public:
        static std::unique_ptr<Command> create(Request req);
};
