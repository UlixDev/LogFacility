#include <QCoreApplication>

#include "LoggerManager.h"
#include "logger.h"

void m1();
void m2();
void m3();
void m4();
void fn();
void error();

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    LoggerManager *loggerManager = LoggerManager::instance();
    loggerManager->outputDevice(argv[1]);

    Logger *logger = loggerManager->logger("MAIN");
    logger->setLevel(Logger::LogLevel::DEBUG);

    logger->debug("Program starts", "MAIN");

    logger->addStack();
    m1();

    logger->debug("Program runs", "MAIN");
    fn();
    logger->backTrace();
    logger->removeStack();

    logger->info("Program exits");
    return a.exec();
}

void m1()
{
    LoggerManager *loggerManager = LoggerManager::instance();
    Logger *logger = loggerManager->logger("MAIN");

    logger->debug("Program @ m1");

    logger->addStack();
    m2();
    logger->removeStack();
}

void m2()
{
    LoggerManager *loggerManager = LoggerManager::instance();
    Logger *logger = loggerManager->logger("MAIN");

    logger->debug("Program @ m2");
    logger->print("*************************************");
    logger->print("This is a plain string inside a frame");
    logger->print("*************************************");
    logger->addStack();
    m3();
    logger->removeStack();
}

void m3()
{
    LoggerManager *loggerManager = LoggerManager::instance();
    Logger *logger = loggerManager->logger("MAIN");

    logger->debug("Program @ m3");

    logger->addStack();
    m4();
    logger->removeStack();

}

void m4()
{
    LoggerManager *loggerManager = LoggerManager::instance();
    Logger *logger = loggerManager->logger("MAIN");

    logger->addStack();
    logger->debug("Program @ m4");

    logger->backTrace();
    logger->removeStack();
}

void fn()
{
    LoggerManager *loggerManager = LoggerManager::instance();

    // By default the level is INFO
    Logger *logger = loggerManager->logger("ALGORITHM");

    logger->debug("fn is working");
    int a = 1;
    logger->debug("Value of a is " + QString::number(a));
    error();
    a = 2;
    logger->warning("Value of a is " + QString::number(a));
}


void error()
{
    LoggerManager *loggerManager = LoggerManager::instance();
    // By default the level is INFO
    Logger *logger = loggerManager->logger("OUTPUT");

    logger->error("Critical error");
}
