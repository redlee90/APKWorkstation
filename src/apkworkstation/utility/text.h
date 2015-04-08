#ifndef APKSTUDIO_UTILITY_TEXT_H
#define APKSTUDIO_UTILITY_TEXT_H

#include <QString>



namespace Utility {

class Text
{
public:
    static QString capitalize(const QString &text, bool force = false);
};

} // namespace Utility



#endif // APKSTUDIO_UTILITY_TEXT_H
