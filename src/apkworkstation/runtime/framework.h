#ifndef APKSTUDIO_RUNTIME_FRAMEWORK_H
#define APKSTUDIO_RUNTIME_FRAMEWORK_H

#include <QFileInfo>
#include <QList>
#include <QObject>
#include <QProcess>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QString>
#include <QStringList>
#include <QThread>

#include "../utility/format.h"
#include "../utility/configuration.h"

namespace Runtime {

class Framework : public QThread
{
    Q_OBJECT
private:
    // Variable
    QString _path;
    QString _tag;
    int _status;
public:
    // Constructor
    Framework(const QString &path, const QString &tag)
    {
        this->_path = path;
        this->_tag = tag;
    }
    // Function
    void run();
    // Destrcutor
    ~Framework() { }
signals:
    void framework(const QString &);
};

} // namespace Runtime

#endif // APKSTUDIO_RUNTIME_FRAMEWORK_H
