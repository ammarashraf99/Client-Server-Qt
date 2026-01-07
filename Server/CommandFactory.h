#pragma once
#include "Command.h"
#include "Request.h"
#include <memory>


class CommandFactory
{
public:
        static std::unique_ptr<Command> create(Request req);
};
