#include "LoggerManager.h"

LoggerManager *LoggerManager::_logger_manager = nullptr;

QMap<QString, *Logger> LoggerManager::_loggers = QMap<QString, *Logger>();

LoggerManager::LoggerManager(QObject *parent)
    : QObject{parent}
{

}

LoggerManager* LoggerManager::instance()
{
    if (_logger_manager == nullptr)
        _logger_manager = new LoggerManager();

    return _logger_manager;
}

Logger * LoggerManager::logger(QString loggerName)
{
    if(_loggers.contains(loggerName)
        return _loggers.value(loggerName))
}
