#include "commands/CommandFactory.h"
#include "commands/AppendCommand.h"
#include "commands/AuthCommand.h"
#include "commands/CreateCommand.h"
#include "commands/DeleteCommand.h"
#include "commands/InfoCommand.h"
#include "commands/ListCommand.h"
#include "commands/ReadCommand.h"
#include "commands/RenameCommand.h"
#include "commands/Command.h"
#include "commands/WriteCommand.h"
#include "core/Request.h"
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




