#ifndef LOGGER_H
#define LOGGER_H

#include <QString>
#include <QHash>
#include <QTextStream>

class Logger
{
public:
    enum class LogLevel: char {
        CRITICAL = 1,
        ERROR,
        WARNING,
        INFO,
        DETAIL,
        DEBUG
    };

    // To avoid pointer reassignment;
    Logger * operator=(Logger *) = delete;

    static Logger * instance();
    inline void setLevel(const LogLevel level) {Logger::_level = level;}
    inline void setModule(const QString module) {_module = module;}

    void debug(const QString &message, QString module="", const char * const function=__builtin_FUNCTION(), const int line=__builtin_LINE());
    void detail(const QString &message, QString module="", const char * const function=__builtin_FUNCTION(), const int line=__builtin_LINE());
    void info(const QString &message, QString module="", const char * const function=__builtin_FUNCTION(), const int line=__builtin_LINE());
    void warning(const QString &message, QString module="", const char * const function=__builtin_FUNCTION(), const int line=__builtin_LINE());
    void error(const QString &message, QString module="", const char * const function=__builtin_FUNCTION(), const int line=__builtin_LINE());
    void critical(const QString &message, QString module="", const char * const function=__builtin_FUNCTION(), const int line=__builtin_LINE());

private:
    static Logger *_logger;
    static QTextStream _out;

    static const QHash<QString, enum LogLevel> _levels;
    static LogLevel _level;

    static void _message_handler(QtMsgType type, const QMessageLogContext &context, const QString &message);

    QString _module;
    Logger();
};

#endif // LOGGER_H
