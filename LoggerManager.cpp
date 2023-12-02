#include "LoggerManager.h"

LoggerManager *LoggerManager::_logger_manager = nullptr;


LoggerManager::LoggerManager(QObject *parent):
    QObject{parent}
{
    _loggers = QMap<QString, Logger>();
}

LoggerManager* LoggerManager::instance()
{
    if (_logger_manager == nullptr)
        _logger_manager = new LoggerManager();

    return _logger_manager;
}

Logger& LoggerManager::logger(QString loggerName)
{
    if(!_loggers.contains(loggerName)) {
        Logger& l = Logger();
        l.setModule(loggerName);
        _loggers.insert(loggerName, l);
    }

    return _loggers.value(loggerName);
}
