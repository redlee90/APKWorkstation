#include "xmlhighlighter.h"



namespace UI {

static const QColor DEFAULT_SYNTAX_CHAR		= QColor("#003471");
static const QColor DEFAULT_ELEMENT_NAME	= QColor("#004A80");
static const QColor DEFAULT_COMMENT			= QColor("#CCCCCC");
static const QColor DEFAULT_ATTRIBUTE_NAME	= QColor("#0072BC");
static const QColor DEFAULT_ATTRIBUTE_VALUE	= QColor("#39B54A");
static const QColor DEFAULT_ERROR			= QColor("#CC0000");
static const QColor DEFAULT_OTHER			= QColor("#333333");

static const QString EXPR_COMMENT			= "<!--[^-]*-([^-][^-]*-)*->";
static const QString EXPR_COMMENT_BEGIN		= "<!--";
static const QString EXPR_COMMENT_END		= "[^-]*-([^-][^-]*-)*->";
static const QString EXPR_ATTRIBUTE_VALUE	= "\"[^<\"]*\"|'[^<']*'";
static const QString EXPR_NAME				= "([A-Za-z_:]|[^\\x00-\\x7F])([A-Za-z0-9_:.-]|[^\\x00-\\x7F])*";

XMLHighlighter::XMLHighlighter(QObject* parent)
: QSyntaxHighlighter(parent)
{
}

XMLHighlighter::XMLHighlighter(QTextDocument* parent)
: QSyntaxHighlighter(parent)
{
}

XMLHighlighter::XMLHighlighter(QPlainTextEdit* parent)
: QSyntaxHighlighter(parent)
{
}

XMLHighlighter::~XMLHighlighter()
{
}

void XMLHighlighter::initialize()
{
    fmtSyntaxChar.setForeground(DEFAULT_SYNTAX_CHAR);
    fmtElementName.setForeground(DEFAULT_ELEMENT_NAME);
    fmtComment.setForeground(DEFAULT_COMMENT);
    fmtAttributeName.setForeground(DEFAULT_ATTRIBUTE_NAME);
    fmtAttributeValue.setForeground(DEFAULT_ATTRIBUTE_VALUE);
    fmtError.setForeground(DEFAULT_ERROR);
    fmtOther.setForeground(DEFAULT_OTHER);
}

void XMLHighlighter::setHighlightColor(HighlightType type, QColor color, bool foreground)
{
    QTextCharFormat format;
    if (foreground)
        format.setForeground(color);
    else
        format.setBackground(color);
    setHighlightFormat(type, format);
}

void XMLHighlighter::setHighlightFormat(HighlightType type, QTextCharFormat format)
{
    switch (type)
    {
        case SyntaxChar:
            fmtSyntaxChar = format;
            break;
        case ElementName:
            fmtElementName = format;
            break;
        case Comment:
            fmtComment = format;
            break;
        case AttributeName:
            fmtAttributeName = format;
            break;
        case AttributeValue:
            fmtAttributeValue = format;
            break;
        case Error:
            fmtError = format;
            break;
        case Other:
            fmtOther = format;
            break;
    }
    rehighlight();
}

void XMLHighlighter::highlightBlock(const QString& text)
{
    int i = 0;
    int pos = 0;
    int brackets = 0;

    state = (previousBlockState() == InElement ? ExpectAttributeOrEndOfElement : NoState);

    if (previousBlockState() == InComment)
    {
        // search for the end of the comment
        QRegExp expression(EXPR_COMMENT_END);
        pos = expression.indexIn(text, i);

        if (pos >= 0)
        {
            // end comment found
            const int iLength = expression.matchedLength();
            setFormat(0, iLength - 3, fmtComment);
            setFormat(iLength - 3, 3, fmtSyntaxChar);
            i += iLength; // skip comment
        }
        else
        {
            // in comment
            setFormat(0, text.length(), fmtComment);
            setCurrentBlockState(InComment);
            return;
        }
    }
    for (; i < text.length(); i++)
    {
        switch (text.at(i).toLatin1())
        {
        case '<':
            brackets++;
            if (brackets == 1)
            {
                setFormat(i, 1, fmtSyntaxChar);
                state = ExpectElementNameOrSlash;
            }
            else
            {
                // wrong bracket nesting
                setFormat(i, 1, fmtError);
            }
            break;

        case '>':
            brackets--;
            if (brackets == 0)
            {
                setFormat(i, 1, fmtSyntaxChar);
            }
            else
            {
                // wrong bracket nesting
                setFormat( i, 1, fmtError);
            }
            state = NoState;
            break;

        case '/':
            if (state == ExpectElementNameOrSlash)
            {
                state = ExpectElementName;
                setFormat(i, 1, fmtSyntaxChar);
            }
            else
            {
                if (state == ExpectAttributeOrEndOfElement)
                {
                    setFormat(i, 1, fmtSyntaxChar);
                }
                else
                {
                    processDefaultText(i, text);
                }
            }
            break;

        case '=':
            if (state == ExpectEqual)
            {
                state = ExpectAttributeValue;
                setFormat(i, 1, fmtOther);
            }
            else
            {
                processDefaultText(i, text);
            }
            break;

        case '\'':
        case '\"':
            if (state == ExpectAttributeValue)
            {
                // search attribute value
                QRegExp expression(EXPR_ATTRIBUTE_VALUE);
                pos = expression.indexIn(text, i);

                if (pos == i) // attribute value found ?
                {
                    const int iLength = expression.matchedLength();

                    setFormat(i, 1, fmtOther);
                    setFormat(i + 1, iLength - 2, fmtAttributeValue);
                    setFormat(i + iLength - 1, 1, fmtOther);

                    i += iLength - 1; // skip attribute value
                    state = ExpectAttributeOrEndOfElement;
                }
                else
                {
                    processDefaultText(i, text);
                }
            }
            else
            {
                processDefaultText(i, text);
            }
            break;

        case '!':
            if (state == ExpectElementNameOrSlash)
            {
                // search comment
                QRegExp expression(EXPR_COMMENT);
                pos = expression.indexIn(text, i - 1);

                if (pos == i - 1) // comment found ?
                {
                    const int iLength = expression.matchedLength();

                    setFormat(pos, 4, fmtSyntaxChar);
                    setFormat(pos + 4, iLength - 7, fmtComment);
                    setFormat(iLength - 3, 3, fmtSyntaxChar);
                    i += iLength - 2; // skip comment
                    state = NoState;
                    brackets--;
                }
                else
                {
                    // Try find multiline comment
                    QRegExp expression(EXPR_COMMENT_BEGIN); // search comment start
                    pos = expression.indexIn(text, i - 1);

                    //if (pos == i - 1) // comment found ?
                    if (pos >= i - 1)
                    {
                        setFormat(i, 3, fmtSyntaxChar);
                        setFormat(i + 3, text.length() - i - 3, fmtComment);
                        setCurrentBlockState(InComment);
                        return;
                    }
                    else
                    {
                        processDefaultText(i, text);
                    }
                }
            }
            else
            {
                processDefaultText(i, text);
            }

            break;

        default:
            const int iLength = processDefaultText(i, text);
            if (iLength > 0)
                i += iLength - 1;
            break;
        }
    }

    if (state == ExpectAttributeOrEndOfElement)
    {
        setCurrentBlockState(InElement);
    }
}

int XMLHighlighter::processDefaultText(int i, const QString& text)
{
    // length of matched text
    int iLength = 0;

    switch(state)
    {
    case ExpectElementNameOrSlash:
    case ExpectElementName:
        {
            // search element name
            QRegExp expression(EXPR_NAME);
            const int pos = expression.indexIn(text, i);

            if (pos == i) // found ?
            {
                iLength = expression.matchedLength();

                setFormat(pos, iLength, fmtElementName);
                state = ExpectAttributeOrEndOfElement;
            }
            else
            {
                setFormat(i, 1, fmtOther);
            }
        }
        break;

    case ExpectAttributeOrEndOfElement:
        {
            // search attribute name
            QRegExp expression(EXPR_NAME);
            const int pos = expression.indexIn(text, i);

            if (pos == i) // found ?
            {
                iLength = expression.matchedLength();

                setFormat(pos, iLength, fmtAttributeName);
                state = ExpectEqual;
            }
            else
            {
                setFormat(i, 1, fmtOther);
            }
        }
        break;

    default:
        setFormat(i, 1, fmtOther);
        break;
    }
    return iLength;
}

} // namespace UI


