#pragma once

#include <QTextEdit>

class QLineNumberArea;

/**
 * @brief Class, that describes code editor.
 */
class QCodeEditor : public QTextEdit
{
    Q_OBJECT

public:
    /**
     * @brief Constructor.
     * @param widget Pointer to parent widget.
     */
    explicit QCodeEditor(QWidget* widget=nullptr);

    /**
     * @brief Method for getting first visible block
     * index.
     * @return Index.
     */
    int getFirstVisibleBlock();

public slots:

    void updateLineNumberAreaWidth(int);

    void updateLineNumberArea(const QRect& rect);

    void updateExtraSelection();

private:

    /**
     * @brief Method, that adds highlighting of
     * currently selected line to extra selection list.
     */
    void highlightCurrentLine(QList<QTextEdit::ExtraSelection>& extraSelection);

protected:
    void paintEvent(QPaintEvent* e) override;

    void resizeEvent(QResizeEvent* e) override;

private:

    QLineNumberArea* m_lineNumberArea;
};

