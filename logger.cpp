#include <QtGlobal>

#include <QByteArray>

#include <QTime>
#include <QDateTime>

#include "logger.h"

Logger * Logger::_logger = nullptr;
Logger::LogLevel Logger::_level = Logger::LogLevel::INFO;
QTextStream Logger::_out = QTextStream(stdout);


const QHash<QString, enum Logger::LogLevel> Logger::_levels = {
    {"CRITICAL", Logger::LogLevel::CRITICAL},
    {"ERROR", Logger::LogLevel::ERROR},
    {"WARNING", Logger::LogLevel::WARNING},
    {"INFO", Logger::LogLevel::INFO},
    {"DETAIL", Logger::LogLevel::DETAIL},
    {"DEBUG", Logger::LogLevel::DEBUG}};

Logger::Logger(): _module("")
{
    qInstallMessageHandler(Logger::_message_handler);
}

Logger* Logger::instance()
{
    if (_logger == nullptr)
        _logger = new Logger();

    return _logger;
}

void Logger::_message_handler(QtMsgType type, const QMessageLogContext &context, const QString &message)
{


    enum LogLevel level = LogLevel::DEBUG;
    switch (type) {
    case QtDebugMsg:
        break;
    case QtInfoMsg:
        level = LogLevel::INFO;
        break;
    case QtWarningMsg:
        level = LogLevel::WARNING;
        break;
    case QtCriticalMsg:
        level = LogLevel::ERROR;
        break;
    case QtFatalMsg:
        level = LogLevel::CRITICAL;
        break;
    }

    QStringList items = message.split(" ");
    QString strLevel = items.at(0);
    if (Logger::_levels.contains(strLevel)) {
        level = Logger::_levels[strLevel];
        items.pop_front();
    }

    if(level > Logger::_level)
        return ;

    const QString module = items.at(0);
    items.pop_front();
    const QString function = items.at(0);
    items.pop_front();
    const QString line = items.at(0);
    items.pop_front();

    QByteArray data;
    for (auto item: items) {
        data.append(item.toStdString().c_str());
        data.append(" ");
    }
    data.removeLast();

    QString now = QTime::currentTime().toString();
    const QString customMessage = "[" + now + "]" + " - " +
                                  "[" + strLevel + "]" + " - " +
                                  "[" + module + "]" + " - " +
                                  "[" + "function " + function + "]" + " - " +
                                  "[" + "line " + line + "]" + " - " +
                                  "[" + data + "]";
    _out << customMessage << Qt::endl;
}

void Logger::debug(const QString &message, QString module, const char * const function, const int line)
{
    module = module.isEmpty() ? _module : module;
    qDebug().noquote() << "DEBUG" << module << function << QString::number(line) << message;
}

void Logger::detail(const QString &message, QString module, const char * const function, const int line)
{
    module = module.isEmpty() ? _module : module;
    qDebug().noquote() << "DETAIL" << module << function << QString::number(line) << message;
}

void Logger::info(const QString &message, QString module, const char * const function, const int line)
{
    module = module.isEmpty() ? _module : module;
    qDebug().noquote() << "INFO" << module << function << QString::number(line) << message;
}

void Logger::warning(const QString &message, QString module, const char * const function, const int line)
{
    module = module.isEmpty() ? _module : module;
    qDebug().noquote() << "WARNING" << module << function << QString::number(line) << message;
}

void Logger::error(const QString &message, QString module, const char * const function, const int line)
{
    module = module.isEmpty() ? _module : module;
    qDebug().noquote() << "ERROR" << module << function << QString::number(line) << message;
}

void Logger::critical(const QString &message, QString module, const char * const function, const int line)
{
    module = module.isEmpty() ? _module : module;
    qDebug().noquote() << "CRITICAL" << module << function << QString::number(line) << message;
}
