#include "LoggerManager.h"

LoggerManager *LoggerManager::_logger_manager = nullptr;


LoggerManager::LoggerManager(QObject *parent):
    _device_name("stdout"),
    QObject{parent}
{
    _loggers = QMap<QString, Logger *>();
}

LoggerManager* LoggerManager::instance()
{
    if (_logger_manager == nullptr)
        _logger_manager = new LoggerManager();

    return _logger_manager;
}

Logger* LoggerManager::getLogger(QString loggerName)
{
    return LoggerManager::instance()->logger(loggerName);
}

Logger* LoggerManager::logger(QString loggerName)
{
    if(!_loggers.contains(loggerName)) {
        Logger *l = new Logger(loggerName);
        l->setDevice(_device_name);
        _loggers.insert(loggerName, l);

    }

    return _loggers.value(loggerName);
}
