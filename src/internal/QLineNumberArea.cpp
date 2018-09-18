// QCodeEditor
#include <internal/QLineNumberArea.hpp>
#include <internal/QCodeEditor.hpp>

// Qt
#include <QDebug>
#include <QTextEdit>
#include <QPainter>
#include <QPaintEvent>
#include <QTextBlock>
#include <QScrollBar>
#include <QAbstractTextDocumentLayout>

QLineNumberArea::QLineNumberArea(QCodeEditor* parent) :
    QWidget(parent),
    m_codeEditParent(parent)
{

}

QSize QLineNumberArea::sizeHint() const
{
    if (m_codeEditParent == nullptr)
    {
        return QWidget::sizeHint();
    }

    // Calculating width
    int digits = 1;
    int max = qMax(1, m_codeEditParent->document()->blockCount());
    while (max >= 10) {
        max /= 10;
        ++digits;
    }

    int space = 13 + m_codeEditParent->fontMetrics().horizontalAdvance(QLatin1Char('9')) * digits;

    return QSize(space, 0);
}

void QLineNumberArea::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);

    // Clearing rect to update
    painter.fillRect(event->rect(), Qt::lightGray);

    int blockNumber = m_codeEditParent->getFirstVisibleBlock();
    auto block = m_codeEditParent->document()->findBlockByNumber(blockNumber);
    int top = (int) m_codeEditParent->document()->documentLayout()->blockBoundingRect(block).translated(0, -m_codeEditParent->verticalScrollBar()->value()).top();
    int bottom = top + (int) m_codeEditParent->document()->documentLayout()->blockBoundingRect(block).height();

    QColor currentLine(90, 255, 30); // Current line (custom green)
    QColor otherLines = Qt::black;   // Other lines  (custom darkgrey)

    painter.setFont(m_codeEditParent->font());

    while (block.isValid() && top <= event->rect().bottom())
    {
        if (block.isVisible() && bottom >= event->rect().top())
        {
            QString number = QString::number(blockNumber + 1);

            if (m_codeEditParent->textCursor().blockNumber() == blockNumber)
            {
                painter.setPen(currentLine);
            }
            else
            {
                painter.setPen(otherLines);
            }

            painter.drawText(
                -5,
                top,
                width(),
                m_codeEditParent->fontMetrics().height(),
                Qt::AlignRight,
                number
            );
        }

        block = block.next();
        top = bottom;
        bottom = top + (int) m_codeEditParent->document()->documentLayout()->blockBoundingRect(block).height();
        ++blockNumber;
    }
}
