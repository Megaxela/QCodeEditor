#pragma once

#include <QWidget>

class QCodeEditor;

/**
 * @brief Class, that describes line number area widget.
 */
class QLineNumberArea : public QWidget
{
    Q_OBJECT

public:

    /**
     * @brief Constructor.
     * @param parent Pointer to parent QTextEdit widget.
     */
    explicit QLineNumberArea(QCodeEditor* parent=nullptr);

    QSize sizeHint() const override;

protected:
    void paintEvent(QPaintEvent* event) override;

private:

    QCodeEditor* m_codeEditParent;

};

