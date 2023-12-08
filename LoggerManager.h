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
    Logger * logger(QString loggerName);
    inline void outputDevice(const QString &deviceName) {_device_name = deviceName;}

signals:

private:
    static LoggerManager *_logger_manager;

    QString _device_name;
    QMap<QString, Logger *> _loggers;

    explicit LoggerManager(QObject *parent = nullptr);


};

#endif // LOGGERMANAGER_H
