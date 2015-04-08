#ifndef APKSTUDIO_UTILITY_FORMAT_H
#define APKSTUDIO_UTILITY_FORMAT_H

#include <QDateTime>
#include <QString>
#include <QStringList>
#include <QStringListIterator>

#include "../bridge/constant.h"



namespace Utility {

class Format
{
public:
    static QString size(float bytes);
    static QString time(const QDateTime & = QDateTime::currentDateTime(), const QString & = FORMAT_TIMESTAMP);
};

} // namespace Utility



#endif // APKSTUDIO_UTILITY_FORMAT_H
