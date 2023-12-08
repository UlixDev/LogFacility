#include <QtGlobal>

#include <QByteArray>

#include <QFile>
#include <QIODevice>

#include "logger.h"


const QHash<QString, enum Logger::LogLevel> Logger::_levels = {
    {"CRITICAL", Logger::LogLevel::CRITICAL},
    {"ERROR", Logger::LogLevel::ERROR},
    {"WARNING", Logger::LogLevel::WARNING},
    {"INFO", Logger::LogLevel::INFO},
    {"DETAIL", Logger::LogLevel::DETAIL},
    {"DEBUG", Logger::LogLevel::DEBUG},
    {"STACK", Logger::LogLevel::STACK},
    {"PLAIN", Logger::LogLevel::PLAIN}
    };

const QHash<enum Logger::LogLevel, QString> Logger::_string_levels = {
    {Logger::LogLevel::CRITICAL, "CRITICAL"},
    {Logger::LogLevel::ERROR, "ERROR"},
    {Logger::LogLevel::WARNING, "WARNING"},
    {Logger::LogLevel::INFO, "INFO"},
    {Logger::LogLevel::DETAIL, "DETAIL"},
    {Logger::LogLevel::DEBUG, "DEBUG"},
    {Logger::LogLevel::STACK, "STACK"},
    {Logger::LogLevel::PLAIN, "PLAIN"}
};


Logger::Logger(QString loggerName, QObject *parent):
    _handler(_message_handler),
    _level(LogLevel::INFO), _module(loggerName),
    _stack(),
    QObject(parent)
{

    qInstallMessageHandler(_handler);
}

Logger::Logger(const Logger &X):
    _handler(X._handler),
    _level(X._level), _module(X._module), _device_name(X._device_name),
    _stack(X._stack)
{
    qInstallMessageHandler(_handler);
}

Logger& Logger::operator=(const Logger r)
{
    _handler = r._handler;

    _level = r._level;
    _module = r._module;
    _device_name = r._device_name;

    _stack = r._stack;

    qInstallMessageHandler(_handler);
    return *this;
}

void Logger::_message_handler(QtMsgType type, const QMessageLogContext &context, const QString &message)
{

    QStringList items = message.split(" ");
    QString outputFilename = items.at(0);
    items.pop_front();

    bool close = true;
    QFile of;
    if (outputFilename == "stdout") {
        close = false;
        of.open(1, QIODevice::WriteOnly);
    } else if(outputFilename == "stderr") {
        close = false;
        of.open(2, QIODevice::WriteOnly);
    } else {
        of.setFileName(outputFilename);
        of.open(QIODevice::Append);
    }
    QTextStream out(&of);

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
    const QString file = items.at(0);
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

    QString today = QDateTime::currentDateTime().toString();
    const QString customMessage = ((level == LogLevel::STACK) || (level == LogLevel::PLAIN)) ?
        data :
        "[" + today + "]" + " - " +
                                  "[" + strLevel + "]" + " - " +
                                  "[" + module + "]" + " - " +
                                  "[" + "file" + " " + file + "]" + " - " +
                                  "[" + "function" + " " + function + "]" + " - " +
                                  "[" + "line" + " " + line + "]" + " - " +
                                  "[" + data + "]";
    out << customMessage << Qt::endl;
    out.flush();
    if(close)
        of.close();
}

void Logger::bt(const QString &message)
{
    QString currentDeviceName = _device_name;
    _device_name = (_device_name == "stdout") ?
                       "log.bt" : (_device_name == "stderr") ?
                                                    "err.bt" : _device_name + QString(".") + QString("bt");

    QString level = QString("STACK") + QString("%") + QString("STACK");
    _print(message, level, "", "", "", 0);

    _device_name = currentDeviceName;
}

void Logger::print(const QString &message)
{
    QString level = QString("PLAIN") + QString("%") + QString("PLAIN");
    _print(message, level, "", "", "", 0);
}

void Logger::debug(const QString &message, QString module, const char * const file, const char * const function, const int line)
{
    QString level = QString("DEBUG") + QString("%") + Logger::_string_levels[_level];
    _print(message, level, module, file, function, line);
}

void Logger::detail(const QString &message, QString module, const char * const file, const char * const function, const int line)
{
    QString level = QString("DETAIL") + QString("%") + Logger::_string_levels[_level];
    _print(message, level, module, file, function, line);
}

void Logger::info(const QString &message, QString module, const char * const file, const char * const function, const int line)
{
    QString level = QString("INFO") + QString("%") + Logger::_string_levels[_level];
    _print(message, level, module, file, function, line);
}

void Logger::warning(const QString &message, QString module, const char * const file, const char * const function, const int line)
{
    QString level = QString("WARNING") + QString("%") + Logger::_string_levels[_level];
    _print(message, level, module, file, function, line);
}

void Logger::error(const QString &message, QString module, const char * const file, const char * const function, const int line)
{
    QString level = QString("ERROR") + QString("%") + Logger::_string_levels[_level];
    _print(message, level, module, file, function, line);
}

void Logger::critical(const QString &message, QString module, const char * const file, const char * const function, const int line)
{
    QString level = QString("CRITICAL") + QString(QString("%")) + Logger::_string_levels[_level];
    _print(message, level, module, file, function, line);
}

void Logger::_print(const QString message, const QString level, QString module, const char * const file, const char * const function, const int line)
{
    module = module.isEmpty() ? _module : module;
    qDebug().noquote() << _device_name << level << module << file << function << QString::number(line) << message;
}
