#ifndef APKSTUDIO_RUNTIME_RECOMPILE_H
#define APKSTUDIO_RUNTIME_RECOMPILE_H

#include <QDir>
#include <QFileInfo>
#include <QList>
#include <QObject>
#include <QProcess>
#include <QString>
#include <QStringList>
#include <QThread>

#include "../utility/configuration.h"
#include "../utility/format.h"
#include "../utility/resource.h"

namespace Runtime {

class Recompile : public QThread
{
    Q_OBJECT
private:
    // Variable
    QString _dir;
    // Resource
    static QIcon icon(const char *name)
    {
        return Utility::Resource::icon("recompile", name);
    }
    static QString text(const char *key)
    {
        return Utility::Resource::text("recompile", key);
    }
public:
    // Constructor
    Recompile(const QString &dir)
    {
        this->_dir = dir;
    }
    // Function
    void run();
    // Destrcutor
    ~Recompile() { }
signals:
    void output(const QString &);
    void recompile(const QString &, const QString &);
    void newInfo(const QString &);
};

} // namespace Runtime

#endif // APKSTUDIO_RUNTIME_RECOMPILE_H
