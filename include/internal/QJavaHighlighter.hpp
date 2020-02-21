#pragma once

// QCodeEditor
#include <QStyleSyntaxHighlighter> // Required for inheritance
#include <QHighlightRule>

// Qt
#include <QRegularExpression>
#include <QVector>

class QSyntaxStyle;

/**
 * @brief Derived to implement highlighting of Java code.
 */
class QJavaHighlighter : public QStyleSyntaxHighlighter
{
    Q_OBJECT
public:

    /**
     * @brief Constructs a new instance of a Java highlighter.
     * @param document The text document to be highlighted.
     * This may be a null pointer.
     */
    explicit QJavaHighlighter(QTextDocument* document=nullptr);

protected:
    /**
     * @brief Derived to highlight blocks of Java code.
     * @param text The block of text containing Java code.
     */
    void highlightBlock(const QString& text) override;

private:

    QVector<QHighlightRule> m_highlightRules;

    QRegularExpression m_commentStartPattern;
    QRegularExpression m_commentEndPattern;
};

