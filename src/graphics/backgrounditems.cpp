#include "backgrounditems.h"
#include "defines.h"
#include "shape.h"

#include <QFont>
#include <QFontMetrics>
#include <QPainter>
#include <QRectF>

namespace Graphics {

DashLine::DashLine(Shape* reg) {
    m_regPtr = reg;
}

QRectF DashLine::boundingRect() const {
    auto regRect = m_regPtr->sceneBoundingRect();
    return QRectF(QPointF(regRect.left(), regRect.top() - dashHeight),
                  QPointF(regRect.right(), regRect.bottom() + dashHeight));
}

void DashLine::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) {
    QPen pen(Qt::DashLine);
    pen.setColor(Colors::FoundersRock);
    pen.setWidth(2);
    painter->setPen(pen);
    auto regRect = m_regPtr->sceneBoundingRect();
    painter->drawLine(QPointF(regRect.left() + (regRect.width() / 2), regRect.top() - dashHeight),
                      QPointF(regRect.left() + (regRect.width() / 2), regRect.top()));

    painter->drawLine(QPointF(regRect.left() + (regRect.width() / 2), regRect.bottom()),
                      QPointF(regRect.left() + (regRect.width() / 2), regRect.bottom() + dashHeight));
}

Text::Text(QPointF pos) {
    m_pos = pos;
    m_font = QFont("Monospace");
    m_font.setStyleHint(QFont::Monospace);
    m_font.setPointSize(12);
}

QRectF Text::boundingRect() const {
    QFontMetrics obj(m_font);
    auto rect = obj.boundingRect(m_text);
    rect.moveTo(m_pos.toPoint());
    return rect;
}

void Text::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) {
    QFontMetrics obj(m_font);
    QRectF rect = obj.boundingRect(m_text);
    rect.moveTo(m_pos.toPoint());
    rect.translate(-rect.width() / 2, -rect.height() / 2);
    painter->setFont(m_font);
    painter->drawText(rect, Qt::AlignCenter, m_text);
}

}  // namespace Graphics