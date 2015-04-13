#ifndef SHOWJAVA_H
#define SHOWJAVA_H

#include <QString>
#include <QFileInfo>
#include <QList>
#include <QObject>
#include <QProcess>
#include <QStringList>

#include "../utility/format.h"
#include "../utility/configuration.h"

namespace Runtime {

class showjava : public QObject
//class showjava : public QThread
{
    Q_OBJECT
public:
    showjava(const QString& _outDir);
    ~showjava(){}
    void run();
private:
    bool _done;
    QString _outDir;
    QProcess* process;

signals:
    void output(const QString &);
    void newConsoleInfo(const QString &);
    void newStatusInfo(const QString &, const int);

private slots:
    void __finished(int);
    void __readRead();

};

}

#endif // SHOWJAVA_H
