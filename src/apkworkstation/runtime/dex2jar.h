#ifndef DEX2JAR_H
#define DEX2JAR_H

#include <QString>
#include <QFileInfo>
#include <QList>
#include <QObject>
#include <QProcess>
#include <QStringList>
#include <QThread>

#include "../utility/format.h"
#include "../utility/configuration.h"

namespace Runtime {

class dex2jar : public QThread
{
    Q_OBJECT
public:
    dex2jar(const QString& _apk, const QString& _outDir, const QString& _tag);
    ~dex2jar(){}
    void run();
private:
    QString _apk;
    bool _done;
    QString _outDir;
    QString _tag;

signals:
    void output(const QString &);
    void newConsoleInfo(const QString &);
    void newStatusInfo(const QString&, const QString &);
};

}

#endif // DEX2JAR_H
