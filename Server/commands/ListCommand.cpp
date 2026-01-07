#include "commands/ListCommand.h"

#include "core/Result.h"
#include "security/Security.h"
#include <QFile>
#include <QTextStream>
#include <QDir>


ListCommand::ListCommand(const QStringList& args)
        :m_args(args) {}

ListCommand::~ListCommand() {}

bool ListCommand::validate() const
{
        if (!m_args.empty()) {
                return false;
        }

        if (Security::isRoot()) {
                return false;
        }

        return true;
}

Result ListCommand::execute()
{
        Result result;
        QDir dir = QDir::current(); // Current working directory
        QStringList files = dir.entryList(QDir::Files | QDir::Hidden); // only files
        result.Ok() = true;
        for (const QString &file : files) {
                result.Message() += file + "\n";
        }

        return result;
}
