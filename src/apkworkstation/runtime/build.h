#ifndef APKSTUDIO_RUNTIME_BUILD_H
#define APKSTUDIO_RUNTIME_BUILD_H

#include <QMap>
#include <QObject>
#include <QProcess>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QString>
#include <QThread>

#include "../bridge/constant.h"
#include "../utility/configuration.h"

namespace Runtime {

class Build : public QThread
{
    Q_OBJECT
private:
    // Variable
    QString _device;
public:
    Build(const QString &device)
    {
        this->_device = device;
    }
    void run();
signals:
    void build(const QMap<QString, QString> &);
};

} // namespace Runtime

#endif // APKSTUDIO_RUNTIME_INFO_H
