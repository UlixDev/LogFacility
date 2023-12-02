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
    loggerManager->outputDevice("stdout");

    Logger logger = loggerManager->logger("MAIN");
    logger.setLevel(Logger::LogLevel::DEBUG);
    logger.addToStack();

    logger.debug("Program starts", "MAIN");

    m1();
    logger.printStack();
    fn();
    logger.info("Program exits");
    return a.exec();
}

void m1()
{
    LoggerManager *loggerManager = LoggerManager::instance();
    Logger logger = loggerManager->logger("MAIN");

    logger.addToStack();
    logger.debug("Program @ m1");

    m2();
    logger.removeFromStack();
}

void m2()
{
    LoggerManager *loggerManager = LoggerManager::instance();
    Logger logger = loggerManager->logger("MAIN");

    logger.addToStack();
    logger.debug("Program @ m2");

    m3();
    logger.removeFromStack();
}

void m3()
{
    LoggerManager *loggerManager = LoggerManager::instance();
    Logger logger = loggerManager->logger("MAIN");

    logger.addToStack();
    logger.debug("Program @ m3");

    m4();
    logger.removeFromStack();

}

void m4()
{
    LoggerManager *loggerManager = LoggerManager::instance();
    Logger logger = loggerManager->logger("MAIN");

    logger.addToStack();
    logger.debug("Program @ m4");

    logger.printStack();
    logger.removeFromStack();
}

void fn()
{
    LoggerManager *loggerManager = LoggerManager::instance();

    // By default the level is INFO
    Logger logger = loggerManager->logger("ALGORITHM");

    logger.debug("fn is working");
    int a = 1;
    logger.debug("Value of a is " + QString::number(a));
    error();
    a = 2;
    logger.warning("Value of a is " + QString::number(a));
}


void error()
{
    LoggerManager *loggerManager = LoggerManager::instance();
    // By default the level is INFO
    Logger logger = loggerManager->logger("OUTPUT");

    logger.error("Critical error");
}
