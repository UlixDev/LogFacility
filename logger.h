#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>

#include <QString>
#include <QStringList>
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
        DEBUG,
        STACK
    };

    Logger(QString loggerName=QString(), QObject *parent=nullptr);
    Logger(const Logger& X);

    inline void setDevice(const QString deviceName) {_device_name = deviceName;}
    inline void setLevel(const LogLevel level) {_level = level;}
    inline void setModule(const QString module) {_module = module;}

    inline void addToStack(const char * const file=__builtin_FILE(), const char * const function=__builtin_FUNCTION(), const int line=__builtin_LINE()) {
        QString item = file + QString("@") + function + QString("@") + QString::number(line);
        _stack.push_front(item);
    }
    inline void removeFromStack() {_stack.pop_front();}
    inline void printStack() {
        for(auto each: _stack)
            stack(each);
    }

    inline QtMessageHandler handler() { return _handler;}

    void stack(const QString &message);
    void debug(const QString &message, QString module="", const char * const file=__builtin_FILE(), const char * const function=__builtin_FUNCTION(), const int line=__builtin_LINE());
    void detail(const QString &message, QString module="", const char * const file=__builtin_FILE(), const char * const function=__builtin_FUNCTION(), const int line=__builtin_LINE());
    void info(const QString &message, QString module="", const char * const file=__builtin_FILE(), const char * const function=__builtin_FUNCTION(), const int line=__builtin_LINE());
    void warning(const QString &message, QString module="", const char * const file=__builtin_FILE(), const char * const function=__builtin_FUNCTION(), const int line=__builtin_LINE());
    void error(const QString &message, QString module="", const char * const file=__builtin_FILE(), const char * const function=__builtin_FUNCTION(), const int line=__builtin_LINE());
    void critical(const QString &message, QString module="", const char * const file=__builtin_FILE(), const char * const function=__builtin_FUNCTION(), const int line=__builtin_LINE());

    Logger& operator=(const Logger r);

private:
    static const QHash<QString, enum LogLevel> _levels;
    static const QHash<enum LogLevel, QString> _string_levels;

    QtMessageHandler _handler;

    LogLevel _level;
    QString _module;

    QString _device_name;

    QStringList _stack;

    static void _message_handler(QtMsgType type, const QMessageLogContext &context, const QString &message);

    void _print(const QString message, const QString level, QString module, const char * const file, const char * const function, const int line);
};

#endif // LOGGER_H
