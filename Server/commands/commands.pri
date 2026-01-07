INCLUDEPATH += $$PWD

HEADERS += \
    $$PWD/Command.h \
    $$PWD/CommandFactory.h \
    $$PWD/AuthCommand.h \
    $$PWD/AppendCommand.h \
    $$PWD/CreateCommand.h \
    $$PWD/DeleteCommand.h \
    $$PWD/ReadCommand.h \
    $$PWD/WriteCommand.h \
    $$PWD/RenameCommand.h \
    $$PWD/ListCommand.h \
    $$PWD/InfoCommand.h

SOURCES += \
    $$PWD/CommandFactory.cpp \
    $$PWD/AuthCommand.cpp \
    $$PWD/AppendCommand.cpp \
    $$PWD/CreateCommand.cpp \
    $$PWD/DeleteCommand.cpp \
    $$PWD/ReadCommand.cpp \
    $$PWD/WriteCommand.cpp \
    $$PWD/RenameCommand.cpp \
    $$PWD/ListCommand.cpp \
    $$PWD/InfoCommand.cpp
