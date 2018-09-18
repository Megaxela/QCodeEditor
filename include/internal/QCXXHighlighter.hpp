#pragma once

// Qt
#include <QSyntaxHighlighter>
#include <QRegularExpression>
#include <QVector>

/**
 * @brief Class, that describes C++ code
 * highlighter.
 */
class QCXXHighlighter : public QSyntaxHighlighter
{
public:

    /**
     * @brief Constructor.
     * @param document Pointer to document.
     */
    explicit QCXXHighlighter(QTextDocument* document=nullptr);

private:

    struct HighlightRule
    {
        QRegularExpression pattern;
        QTextCharFormat format;
    };

    void prepareCommonKeywords();

    void prepareStrings();

    void prepareFunctions();

    void prepareComments();

protected:
    void highlightBlock(const QString& text) override;

private:

    QVector<HighlightRule> m_highlightRules;

    QRegularExpression m_commentStartPattern;
    QRegularExpression m_commentEndPattern;

    QTextCharFormat m_commentFormat;
};

