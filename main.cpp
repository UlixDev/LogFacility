#include <QCoreApplication>

#include "LoggerManager.h"
#include "logger.h"

void m1();
void m2();
void m3(int a);
void m4();
void m5();
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

    qInfo() << "INFO from MAIN";
    TRACK_CALL(m1(), logger);

    logger->debug("Program runs", "MAIN");

    TRACK_CALL_AND_PRINT_BT(fn(), logger);

    logger->info("Program exits");
    return a.exec();
}

void m1()
{
    LoggerManager *loggerManager = LoggerManager::instance();
    Logger *logger = loggerManager->logger("MAIN");

    logger->debug("Program @ m1");
    qWarning() << "WARNING from MAIN";

    TRACK_CALL(m2(), logger);
}

void m2()
{
    LoggerManager *loggerManager = LoggerManager::instance();
    Logger *logger = loggerManager->logger("MAIN");

    logger->debug("Program @ m2");
    logger->print("*************************************");
    logger->print("This is a plain string inside a frame");
    logger->print("*************************************");

    TRACK_CALL(m3(10), logger);
}

void m3(int a)
{
    LoggerManager *loggerManager = LoggerManager::instance();
    Logger *logger = loggerManager->logger("MAIN");

    logger->debug("Program @ m3");
    logger->debug("The passed argument a reads " + QString::number(a));

    TRACK_CALL(m4(), logger);

}

void m4()
{
    LoggerManager *loggerManager = LoggerManager::instance();
    Logger *logger = loggerManager->logger("MAIN");

    logger->debug("Program @ m4");

    m5();

    logger->addStack();
    logger->backTrace();
    logger->removeStack();
}

void m5()
{

}

void fn()
{
    // By default the level is INFO
    Logger *logger = LoggerManager::getLogger("ALGORITHM");

    qCritical() << "CRITICAL from ALGORITHM";
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
