#pragma once

// Qt
#include <QStyleSyntaxHighlighter>
#include <QRegularExpression>
#include <QVector>

class QSyntaxStyle;

/**
 * @brief Class, that describes C++ code
 * highlighter.
 */
class QCXXHighlighter : public QStyleSyntaxHighlighter
{
public:

    /**
     * @brief Constructor.
     * @param document Pointer to document.
     */
    explicit QCXXHighlighter(QTextDocument* document=nullptr);

protected:
    void highlightBlock(const QString& text) override;

private:

    struct HighlightRule
    {
        HighlightRule() :
            pattern(),
            formatName()
        {}

        HighlightRule(QRegularExpression p, QString f) :
            pattern(std::move(p)),
            formatName(std::move(f))
        {}

        QRegularExpression pattern;
        QString formatName;
    };

    void prepareCommonKeywords();

    void preparePrimitiveTypes();

    void prepareComments();

    QVector<HighlightRule> m_highlightRules;

    QRegularExpression m_includePattern;
    QRegularExpression m_functionPattern;
    QRegularExpression m_defTypePattern;

    QRegularExpression m_commentStartPattern;
    QRegularExpression m_commentEndPattern;
};

