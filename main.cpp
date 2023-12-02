#include <QCoreApplication>

#include "logger.h"

void fn();
void error();

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Logger logger = Logger("main");
    logger.setLevel(Logger::LogLevel::DEBUG);
    logger.debug("Program starts", "MAIN");

    fn();
    return a.exec();
}

void fn()
{
    // By default the level is INFO
    Logger logger = Logger("ALGORITHM");

    logger.debug("fn is working");
    int a = 1;
    logger.debug("Value of a is " + QString::number(a));
    error();
    a = 2;
    logger.debug("Value of a is " + QString::number(a));
}


void error()
{
    Logger logger = Logger("OUTPUT");

    logger.error("Critical error");
}
