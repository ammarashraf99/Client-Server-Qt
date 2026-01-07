#include "security/Security.h"
#include <QFileInfo>
#include <QDir>

bool Security::isPath(QString file)
{
        QFileInfo info(file);

        // Reject absolute paths (/tmp/a, C:\a)
        if (info.isAbsolute())
                return true;

        // Reject paths (anything with directory components)
        if (info.path() != "." && info.path() != QString())
                return true;

        // Reject dot or dot-dot
        if (file == "." || file == "..")
                return true;

        return false;
}

bool Security::isRoot()
{
    QDir dir = QDir::current();
    return dir.isRoot();
}
