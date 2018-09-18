// QCodeEditor
#include <internal/QCXXHighlighter.hpp>


QCXXHighlighter::QCXXHighlighter(QTextDocument* document) :
    QSyntaxHighlighter(document)
{
    prepareCommonKeywords();
    prepareStrings();
    prepareFunctions();
    prepareComments();

    QTextCharFormat format;

    format.setForeground(Qt::blue);

    m_highlightRules.append({
        QRegularExpression("#[a-zA-Z_]+\\s"),
        format
    });
}

void QCXXHighlighter::prepareCommonKeywords()
{
    QStringList keywordPatterns;
    keywordPatterns << "char"     << "class"     << "const"
                    << "double"   << "enum"      << "explicit"
                    << "friend"   << "inline"    << "int"
                    << "long"     << "namespace" << "operator"
                    << "private"  << "protected" << "public"
                    << "short"    << "signals"   << "signed"
                    << "slots"    << "static"    << "struct"
                    << "template" << "typedef"   << "typename"
                    << "union"    << "unsigned"  << "virtual"
                    << "void"     << "volatile"  << "bool";

    QTextCharFormat keywordFormat;
    keywordFormat.setForeground(Qt::darkBlue);
    keywordFormat.setFontWeight(QFont::Bold);

    for (auto &pattern : keywordPatterns)
    {
        m_highlightRules.append({
            QRegularExpression(pattern),
            keywordFormat
        });
    }
}

void QCXXHighlighter::prepareStrings()
{
    QTextCharFormat format;
    format.setForeground(Qt::darkGreen);

    m_highlightRules.append({
        QRegularExpression("\".*\""),
        format
    });
}

void QCXXHighlighter::prepareFunctions()
{
    QTextCharFormat format;
    format.setFontItalic(true);
    format.setForeground(Qt::blue);

    m_highlightRules.append({
        QRegularExpression("\\b[A-Za-z0-9_]+(?=\\()"),
        format
    });
}

void QCXXHighlighter::prepareComments()
{
    m_commentFormat.setForeground(Qt::red);

    // Single line
    m_highlightRules.append({
        QRegularExpression("//[^\n]*"),
        m_commentFormat
    });

    m_commentStartPattern = QRegularExpression("/\\*");
    m_commentEndPattern   = QRegularExpression("\\*/");
}

void QCXXHighlighter::highlightBlock(const QString& text)
{
    for (auto& rule : m_highlightRules)
    {
        auto matchIterator = rule.pattern.globalMatch(text);

        while (matchIterator.hasNext())
        {
            auto match = matchIterator.next();

            setFormat(match.capturedStart(), match.capturedLength(), rule.format);
        }
    }

    setCurrentBlockState(0);

    int startIndex = 0;
    if (previousBlockState() != 1)
    {
        startIndex = text.indexOf(m_commentStartPattern);
    }

    while (startIndex >= 0)
    {
        auto match = m_commentEndPattern.match(text, startIndex);

        int endIndex = match.capturedStart();
        int commentLength = 0;

        if (endIndex == -1)
        {
            setCurrentBlockState(1);
            commentLength = text.length() - startIndex;
        }
        else
        {
            commentLength = endIndex - startIndex + match.capturedLength();
        }

        setFormat(startIndex, commentLength, m_commentFormat);
        startIndex = text.indexOf(m_commentStartPattern, startIndex + commentLength);
    }
}
