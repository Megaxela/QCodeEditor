// QCodeEditor
#include <internal/QCXXHighlighter.hpp>
#include <QSyntaxStyle>


QCXXHighlighter::QCXXHighlighter(QTextDocument* document) :
    QStyleSyntaxHighlighter(document)
{
//    prepareCommonKeywords();
//    prepareStrings();
//    prepareFunctions();
//    prepareComments();
//
//    QTextCharFormat format;
//
//    format.setForeground(Qt::blue);
//
//    m_highlightRules.append({
//        QRegularExpression("#[a-zA-Z_]+\\s"),
//        format
//    });
//
    m_includePattern = QRegularExpression(R"(#include\s+([<"][a-zA-Z0-9*._]+[">]))");
    m_functionPattern = QRegularExpression(R"(\b([A-Za-z0-9_]+(?:\s+|::))*([A-Za-z0-9_]+)(?=\())");
    m_defTypePattern = QRegularExpression(R"(\b([A-Za-z0-9_]+)\s+[A-Za-z]{1}[A-Za-z0-9_]+\s*[;=])");

    // Numbers
    m_highlightRules.append({
        QRegularExpression(R"(\b(0b|0x){0,1}\d+\b)"),
        "Number"
    });

    // Strings
    m_highlightRules.append({
        QRegularExpression("\".*\""),
        "String"
    });

    prepareCommonKeywords();
    preparePrimitiveTypes();
    prepareComments();
}

void QCXXHighlighter::prepareCommonKeywords()
{
    QStringList keywordPatterns;
    keywordPatterns << "alignas"          << "alignof"         << "and"
                    << "and_eq"           << "asm"             << "atomic_cancel"
                    << "atomic_commit"    << "atomic_noexcept" << "auto"
                    << "bitand"           << "bitor"           << "break"
                    << "case"             << "catch"           << "class"
                    << "compl"            << "concept"         << "const"
                    << "constexpr"        << "const_cast"      << "continue"
                    << "co_await"         << "co_return"       << "co_yield"
                    << "decltype"         << "default"         << "delete"
                    << "do"               << "dynamic_cast"    << "else"
                    << "enum"             << "explicit"        << "export"
                    << "extern"           << "false"           << "for"
                    << "friend"           << "goto"            << "if"
                    << "import"           << "inline"          << "module"
                    << "mutable"          << "namespace"       << "new"
                    << "noexcept"         << "not"             << "not_eq"
                    << "nullptr"          << "operator"        << "or"
                    << "or_eq"            << "private"         << "protected"
                    << "public"           << "reflexpr"        << "register"
                    << "reinterpret_cast" << "requires"        << "return"
                    << "sizeof"           << "static"          << "static_assert"
                    << "static_cast"      << "struct"          << "switch"
                    << "synchronized"     << "template"        << "this"
                    << "thread_local"     << "throw"           << "true"
                    << "try"              << "typedef"         << "typeid"
                    << "typename"         << "union"           << "using(1)"
                    << "virtual"          << "volatile"        << "while"
                    << "xor"              << "xor_eq";

    for (auto &pattern : keywordPatterns)
    {
        m_highlightRules.append({
            QRegularExpression("\\b" + pattern + "\\b"),
            "Keyword"
        });
    }
}

void QCXXHighlighter::preparePrimitiveTypes()
{
    QStringList keywordPatterns;
    keywordPatterns << "char"     << "char16_t" << "char32_t"
                    << "float"    << "double"   << "int"
                    << "long"     << "short"    << "signed"
                    << "unsigned" << "wchar_t"  << "void"
                    << "bool";

    for (auto &pattern : keywordPatterns)
    {
        m_highlightRules.append({
            QRegularExpression("\\b" + pattern + "\\b"),
            "PrimitiveType"
        });
    }
}

void QCXXHighlighter::prepareComments()
{
    // Single line
    m_highlightRules.append({
        QRegularExpression("//[^\n]*"),
        "Comment"
    });

    m_commentStartPattern = QRegularExpression(R"(/\*)");
    m_commentEndPattern   = QRegularExpression(R"(\*/)");
}

void QCXXHighlighter::highlightBlock(const QString& text)
{
    // Checking for include
    {
        auto matchIterator = m_includePattern.globalMatch(text);

        while (matchIterator.hasNext())
        {
            auto match = matchIterator.next();

            setFormat(
                match.capturedStart(),
                match.capturedLength(),
                syntaxStyle()->getFormat("Preprocessor")
            );

            setFormat(
                match.capturedStart(1),
                match.capturedLength(1),
                syntaxStyle()->getFormat("String")
            );
        }
    }
    // Checking for function
    {
        auto matchIterator = m_functionPattern.globalMatch(text);

        while (matchIterator.hasNext())
        {
            auto match = matchIterator.next();

            setFormat(
                match.capturedStart(),
                match.capturedLength(),
                syntaxStyle()->getFormat("Type")
            );

            setFormat(
                match.capturedStart(2),
                match.capturedLength(2),
                syntaxStyle()->getFormat("Function")
            );
        }
    }
    {
        auto matchIterator = m_defTypePattern.globalMatch(text);

        while (matchIterator.hasNext())
        {
            auto match = matchIterator.next();

            setFormat(
                match.capturedStart(1),
                match.capturedLength(1),
                syntaxStyle()->getFormat("Type")
            );
        }
    }

    for (auto& rule : m_highlightRules)
    {
        auto matchIterator = rule.pattern.globalMatch(text);

        while (matchIterator.hasNext())
        {
            auto match = matchIterator.next();

            setFormat(
                match.capturedStart(),
                match.capturedLength(),
                syntaxStyle()->getFormat(rule.formatName)
            );
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

        setFormat(
            startIndex,
            commentLength,
            syntaxStyle()->getFormat("Comment")
        );
        startIndex = text.indexOf(m_commentStartPattern, startIndex + commentLength);
    }
}
