#include <QtGlobal>

#include <QByteArray>

#include <QTime>
#include <QDateTime>

#include "logger.h"


const QHash<QString, enum Logger::LogLevel> Logger::_levels = {
    {"CRITICAL", Logger::LogLevel::CRITICAL},
    {"ERROR", Logger::LogLevel::ERROR},
    {"WARNING", Logger::LogLevel::WARNING},
    {"INFO", Logger::LogLevel::INFO},
    {"DETAIL", Logger::LogLevel::DETAIL},
    {"DEBUG", Logger::LogLevel::DEBUG}};

const QHash<enum Logger::LogLevel, QString> Logger::_string_levels = {
    {Logger::LogLevel::CRITICAL, "CRITICAL"},
    {Logger::LogLevel::ERROR, "ERROR"},
    {Logger::LogLevel::WARNING, "WARNING"},
    {Logger::LogLevel::INFO, "INFO"},
    {Logger::LogLevel::DETAIL, "DETAIL"},
    {Logger::LogLevel::DEBUG, "DEBUG"}};

Logger::Logger(QString loggerName, QObject *parent):
    _level(LogLevel::INFO), _module(loggerName), _out(QTextStream(stdout)),
    QObject(parent)
{
    qInstallMessageHandler(Logger::_message_handler);
}

Logger::Logger(Logger &X):
    _level(X._level), _module(X._module), _out(QTextStream(stdout))
{
    qInstallMessageHandler(Logger::_message_handler);
}

void Logger::_message_handler(QtMsgType type, const QMessageLogContext &context, const QString &message)
{

    static QTextStream out = QTextStream(stdout);

    enum LogLevel level = LogLevel::DEBUG;
    enum LogLevel referencelevel = LogLevel::INFO;

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
    QString levels = items.at(0);

    QString strLevel = levels.split("%")[0];
    QString strReference = levels.split("%")[1];

    if (Logger::_levels.contains(strLevel)) {
        level = Logger::_levels[strLevel];
        items.pop_front();
    }
    if (Logger::_levels.contains(strReference)) {
        referencelevel = Logger::_levels[strReference];
    }

    if(level > referencelevel)
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
    out << customMessage << Qt::endl;
}

void Logger::debug(const QString &message, QString module, const char * const function, const int line)
{
    QString level = QString("DEBUG") + QString("%") + Logger::_string_levels[_level];
    _print(message, level, module, function, line);
}

void Logger::detail(const QString &message, QString module, const char * const function, const int line)
{
    QString level = QString("DETAIL") + QString("%") + Logger::_string_levels[_level];
    _print(message, level, module, function, line);
}

void Logger::info(const QString &message, QString module, const char * const function, const int line)
{
    QString level = QString("INFO") + QString("%") + Logger::_string_levels[_level];
    _print(message, level, module, function, line);
}

void Logger::warning(const QString &message, QString module, const char * const function, const int line)
{
    QString level = QString("WARNING") + QString("%") + Logger::_string_levels[_level];
    _print(message, level, module, function, line);
}

void Logger::error(const QString &message, QString module, const char * const function, const int line)
{
    QString level = QString("ERROR") + QString("%") + Logger::_string_levels[_level];
    _print(message, level, module, function, line);
}

void Logger::critical(const QString &message, QString module, const char * const function, const int line)
{
    QString level = QString("CRITICAL") + QString(QString("%")) + Logger::_string_levels[_level];
    _print(message, level, module, function, line);
}

void Logger::_print(const QString &message, const QString& level, QString& module, const char * const function, const int line)
{
    module = module.isEmpty() ? _module : module;
    qDebug().noquote() << level << module << function << QString::number(line) << message;
}
