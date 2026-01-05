#include <QCoreApplication>
#include "ServerApplication.h"

int main(int argc, char **argv)
{

        QCoreApplication a(argc, argv);
        ServerApplication server;
        return a.exec();
}
