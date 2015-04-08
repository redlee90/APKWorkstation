#include "text.h"



namespace Utility {

QString Text::capitalize(const QString &text, bool force)
{
    QString temporary = text;
    if (force)
        temporary = text.toLower();
    temporary[0] = temporary[0].toUpper();
    return temporary;
}

} // namespace Utility


