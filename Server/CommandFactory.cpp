#include "CommandFactory.h"
#include "AppendCommand.h"
#include "AuthCommand.h"
#include "CreateCommand.h"
#include "DeleteCommand.h"
#include "InfoCommand.h"
#include "ListCommand.h"
#include "ReadCommand.h"
#include "RenameCommand.h"
#include "Request.h"
#include "Command.h"
#include "WriteCommand.h"
#include <memory>


std::unique_ptr<Command> CommandFactory::create(Request req)
{
        switch (Command::GetCommand(req.command)) {
        case Command::CommandE::AUTH:
                return std::make_unique<AuthCommand>(req.arguments);
                break;
        case Command::CommandE::CREATE:
                return std::make_unique<CreateCommand>(req.arguments);
                break;
        case Command::CommandE::WRITE:
                return std::make_unique<WriteCommand>(req.arguments);
                break;
        case Command::CommandE::APPEND:
                return std::make_unique<AppendCommand>(req.arguments);
                break;
        case Command::CommandE::READ:
                return std::make_unique<ReadCommand>(req.arguments);
                break;
        case Command::CommandE::DELETE:
                return std::make_unique<DeleteCommand>(req.arguments);
                break;
        case Command::CommandE::RENAME:
                return std::make_unique<RenameCommand>(req.arguments);
                break;
        case Command::CommandE::LIST:
                return std::make_unique<ListCommand>(req.arguments);
                break;
        case Command::CommandE::INFO:
                return std::make_unique<InfoCommand>(req.arguments);
                break;
        }

        return std::make_unique<AuthCommand>(req.arguments);
}




