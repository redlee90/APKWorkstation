#ifndef SHOWJAVA_H
#define SHOWJAVA_H

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

class showjava : public QThread
{
    Q_OBJECT
public:
    showjava(const QString& _outDir);
    ~showjava(){}
    void run();
private:
    bool _done;
    QString _outDir;

signals:
    void output(const QString &);
    void newConsoleInfo(const QString &);
    void newStatusInfo(const QString&, const QString &);
};

}

#endif // SHOWJAVA_H
