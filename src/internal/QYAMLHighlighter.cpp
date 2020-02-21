#include <QYAMLHighlighter>
#include <QSyntaxStyle>


QYAMLHighlighter::QYAMLHighlighter(QTextDocument *document)
    : QStyleSyntaxHighlighter(document),
    m_yamlKeywordRegexes(),
    m_yamlValuesRegex(R"(:\s.+$)"),
    m_yamlBooleansRegex(R"( (y|yes|n|no|true|false|on|off)$)"),
    m_yamlNumbersRegex(R"( [[:digit:]]+(\.[[:digit:]]+)?)"),
    m_yamlArraysRegex(R"(\[" "\]" ":\s+[|>]" "^\s*- )"),
    m_yamlReservedRegex(R"((^| )!!(binary|bool|float|int|map|null|omap|seq|set|str) )"),
    m_yamlCommentRegex(R"(#.*$)"),
    m_yamlStringRegex(R"(["'][^'"]*["'])"),
    m_yamlEqualSignRegex(R"(:( |$))")
{
    m_yamlKeywordRegexes
        << QRegularExpression(R"(^\s*[\$A-Za-z0-9_-]+\:)")
        << QRegularExpression(R"(^\s*@[\$A-Za-z0-9_-]+\:)");
}

void QYAMLHighlighter::highlightBlock(const QString &text)
{
    for (const auto& regex : m_yamlKeywordRegexes)
    {
        highlightByRegex(
            syntaxStyle()->getFormat("Keyword"),
            regex,
            text
        );
    }

    highlightByRegex(
        syntaxStyle()->getFormat("Text"),
        m_yamlValuesRegex,
        text
    );

    highlightByRegex(
        syntaxStyle()->getFormat("Text"),
        m_yamlBooleansRegex,
        text
    );

    highlightByRegex(
        syntaxStyle()->getFormat("Number"),
        m_yamlNumbersRegex,
        text
    );

    highlightByRegex(
        syntaxStyle()->getFormat("Text"),
        m_yamlArraysRegex,
        text
    );

    highlightByRegex(
        syntaxStyle()->getFormat("Keyword"),
        m_yamlReservedRegex,
        text
    );

    highlightByRegex(
        syntaxStyle()->getFormat("String"),
        m_yamlStringRegex,
        text
    );

    highlightByRegex(
        syntaxStyle()->getFormat("Text"),
        m_yamlEqualSignRegex,
        text
    );

    highlightByRegex(
        syntaxStyle()->getFormat("Comment"),
        m_yamlCommentRegex,
        text
    );
}

void
QYAMLHighlighter::highlightByRegex(const QTextCharFormat& format, const QRegularExpression& regex, const QString& text)
{
    auto matchIterator = regex.globalMatch(text);

    while (matchIterator.hasNext())
    {
        auto match = matchIterator.next();

        setFormat(
            match.capturedStart(),
            match.capturedLength(),
            format
        );
    }
}
