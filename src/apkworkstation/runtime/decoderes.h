#ifndef DECODERES_H
#define DECODERES_H

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

class decoderes : public QThread
{
    Q_OBJECT
public:
    decoderes(const QString& _apk, const QString& _outDir, const QString& _tag);
    ~decoderes(){}
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
#endif // DECODERES_H

