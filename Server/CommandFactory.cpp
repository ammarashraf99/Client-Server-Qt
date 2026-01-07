#include "CommandFactory.h"
#include "AuthCommand.h"
#include "Request.h"
#include "Command.h"
#include <memory>


std::unique_ptr<Command> CommandFactory::create(Request req)
{
        switch (Command::GetCommand(req.command)) {
        case Command::CommandE::AUTH:
                return std::make_unique<AuthCommand>(req.arguments);
                break;
                // continue othersss
        }

        return std::make_unique<AuthCommand>(req.arguments);
}




