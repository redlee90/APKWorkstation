#ifndef VARIANT_H
#define VARIANT_H

#include <QMetaType>
#include <QRegularExpression>
#include <QString>
#include <QStringList>
#include <QTextCharFormat>



namespace Bridge {

struct Command {
    QStringList arguments;
    QString binary;
};

struct Device {
    QString id;
    enum Status {
        BOOTLOADER = 1,
        OFFLINE,
        ONLINE
    } status;
    enum Type {
        DEVICE = 1,
        EMULATOR
    } type;
};

struct File {
    QString date;
    QString group;
    QString link;
    QString name;
    QString owner;
    QString path;
    struct Permission {
        QString display;
        struct Group {
            bool execute;
            bool read;
            bool write;
        } group;
        struct Owner {
            bool execute;
            bool read;
            bool write;
        } owner;
        struct World {
            bool execute;
            bool read;
            bool write;
        } world;
    } permission;
    float size;
    QString time;
    enum Type {
        CHARACTER = 0,
        BLOCK,
        DIRECTORY,
        FILE,
        OTHER,
        PIPE,
        SOCKET,
        SYMLINK,
        SYMLINK_FILE,
        SYMLINK_DIRECTORY
    } type;
};

struct Highlight {
    QTextCharFormat format;
    QRegularExpression regex;
    QString type;
};

struct Log {
    QString priority;
    QString line;
    QString pid;
    QString tid;
    QString tag;
    QString message;
    QString time;
};

struct Application {
    File file;
    QString package;
    bool state;
    enum Type {
        SYSTEM = 1,
        USER
    } type;
};

struct Partition {
    QStringList flags;
    QString fs;
    QString device;
    QString mount;
};

} // namespace Bridge



Q_DECLARE_METATYPE(Bridge::Application)
Q_DECLARE_METATYPE(Bridge::Command)
Q_DECLARE_METATYPE(Bridge::File)
Q_DECLARE_METATYPE(Bridge::Highlight)

#endif // VARIANT_H
