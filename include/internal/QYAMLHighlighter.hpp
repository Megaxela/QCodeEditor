#pragma once

// QCodeEditor
#include <QStyleSyntaxHighlighter>

// Qt
#include <QRegularExpression>

/**
 * @brief Class, that describes YAML code
 * highlighter.
 */
class QYAMLHighlighter : public QStyleSyntaxHighlighter
{
    Q_OBJECT
public:

    explicit QYAMLHighlighter(QTextDocument* document=nullptr);

protected:

    void highlightBlock(const QString& text) override;

private:
    void highlightByRegex(const QTextCharFormat& format,
                          const QRegularExpression& regex,
                          const QString& text);

    QVector<QRegularExpression> m_yamlKeywordRegexes;
    QRegularExpression          m_yamlValuesRegex;
    QRegularExpression          m_yamlBooleansRegex;
    QRegularExpression          m_yamlNumbersRegex;
    QRegularExpression          m_yamlArraysRegex;
    QRegularExpression          m_yamlReservedRegex;
    QRegularExpression          m_yamlCommentRegex;
    QRegularExpression          m_yamlStringRegex;
    QRegularExpression          m_yamlEqualSignRegex;
};

