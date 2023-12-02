#ifndef LOGGERMANAGER_H
#define LOGGERMANAGER_H

#include <QObject>

#include <QString>
#include <QMap>

#include "logger.h"

class LoggerManager : public QObject
{
    Q_OBJECT

public:

    static LoggerManager * instance();
    Logger& logger(QString loggerName);

signals:

private:
    static LoggerManager *_logger_manager;

    QMap<QString, Logger> _loggers;

    explicit LoggerManager(QObject *parent = nullptr);


};

#endif // LOGGERMANAGER_H
