#pragma once
#include <QString>
#include <unordered_map>
#include <string_view>
#include "Result.h"

class Command
{

public:
        enum class CommandE {
                AUTH,
                CREATE,
                WRITE,
                APPEND,
                READ,
                DELETE,
                RENAME,
                LIST,
                INFO,
        };

        static bool isCommand(std::string_view s){
                auto it = map.find(s);
                if (it != map.end()) {
                        return true;
                } else {
                        return false;
                }
        }
        static Command::CommandE GetCommand(QString cmd)
        {
                auto it = map.find(cmd.toStdString());
                return it->second;
        }


private:
        inline static const std::unordered_map<std::string_view, CommandE> map {
                {"AUTH", CommandE::AUTH},
                {"CREATE", CommandE::CREATE},
                {"WRITE", CommandE::WRITE},
                {"WRITE", CommandE::WRITE},
                {"READ", CommandE::READ},
                {"DELETE", CommandE::DELETE},
                {"RENAME", CommandE::RENAME},
                {"LIST", CommandE::LIST},
                {"INFO", CommandE::INFO},
        };


public:

        virtual ~Command() = default;

        virtual bool validate() const = 0;

        virtual Result execute() = 0;

};

