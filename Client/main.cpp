#include <QCoreApplication>
#include <QDebug>
#include "ClientApplication.h"

int main(int argc, char** argv)
{
        QCoreApplication a(argc, argv);

        ClientApplication client;

        return a.exec();
}
