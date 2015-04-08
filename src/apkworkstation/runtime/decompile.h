#ifndef APKSTUDIO_RUNTIME_DECOMPILE_H
#define APKSTUDIO_RUNTIME_DECOMPILE_H

#include <QFileInfo>
#include <QList>
#include <QObject>
#include <QProcess>
#include <QString>
#include <QStringList>
#include <QThread>

#include "../utility/format.h"
#include "../utility/configuration.h"

namespace Runtime {

class Decompile : public QThread
{
    Q_OBJECT
private:
    // Variable
    QString _apk;
    bool _done;
    QString _location;
    QString _tag;
public:
    // Constructor
    Decompile(const QString &, const QString &, const QString & = QString());
    // Function
    void run();
    // Destrcutor
    ~Decompile() { }
signals:
    void output(const QString &);
    void newStatusInfo(const QString &, const QString &);
    void newInfo(const QString &);
};

} // namespace Runtime

#endif // APKSTUDIO_RUNTIME_DECOMPILE_H
