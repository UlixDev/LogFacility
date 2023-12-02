#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>

#include <QString>
#include <QHash>
#include <QTextStream>

class Logger: public QObject
{
    Q_OBJECT

public:
    enum class LogLevel: char {
        CRITICAL = 1,
        ERROR,
        WARNING,
        INFO,
        DETAIL,
        DEBUG
    };

    Logger(QString loggerName, QObject *parent=nullptr);
    Logger(Logger& X);

    inline void setLevel(const LogLevel level) {_level = level;}
    inline void setModule(const QString module) {_module = module;}

    void debug(const QString &message, QString module="", const char * const function=__builtin_FUNCTION(), const int line=__builtin_LINE());
    void detail(const QString &message, QString module="", const char * const function=__builtin_FUNCTION(), const int line=__builtin_LINE());
    void info(const QString &message, QString module="", const char * const function=__builtin_FUNCTION(), const int line=__builtin_LINE());
    void warning(const QString &message, QString module="", const char * const function=__builtin_FUNCTION(), const int line=__builtin_LINE());
    void error(const QString &message, QString module="", const char * const function=__builtin_FUNCTION(), const int line=__builtin_LINE());
    void critical(const QString &message, QString module="", const char * const function=__builtin_FUNCTION(), const int line=__builtin_LINE());

private:
    static const QHash<QString, enum LogLevel> _levels;
    static const QHash<enum LogLevel, QString> _string_levels;

    LogLevel _level;
    QString _module;
    QTextStream _out;

    static void _message_handler(QtMsgType type, const QMessageLogContext &context, const QString &message);

    void _print(const QString &message, const QString& level, QString& module, const char * const function, const int line);
};

#endif // LOGGER_H
