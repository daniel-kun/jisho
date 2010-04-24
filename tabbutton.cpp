#include "tabbutton.h"

#include <QPainter>
#include <QPaintEvent>

JishoTabButton::JishoTabButton()
{
   setCursor(Qt::PointingHandCursor);
   setCheckable(true);
}

void JishoTabButton::setJishoStyle(const JishoStyle &style)
{
   m_style = style;
   update();
}

void JishoTabButton::paintEvent(QPaintEvent *event)
{

   QPainter painter(this);

   QRect rect = geometry().adjusted(0, 0, -1, -1);
   qreal x = 0;
   qreal y = 0;
   qreal w = rect.width();
   qreal h = rect.height();
   qreal rxx2 = w*20/100;
   qreal ryy2 = h*60/100;

   QPainterPath path;
   path.moveTo(0, h);
   path.arcTo(x, y, rxx2, ryy2, 180, -90);
   path.arcTo(x+w-rxx2, y, rxx2, ryy2, 90, -90);
   path.lineTo(w, h);

   QColor bg;
   if (isChecked())
      bg = m_style.fill;
   else
      bg = m_style.fillHighlight;

   painter.setClipping(true);
   painter.setClipRect(event->rect());
   painter.setPen(m_style.border);
   painter.fillPath(path, bg);
   painter.drawPath(path);
   painter.setPen(bg);
   painter.drawLine(1, h, w - 1, h);

   painter.setPen(palette().color(QPalette::Text));
   painter.drawText(
         0,
         0,
         w,
         h,
         Qt::AlignHCenter |
         Qt::AlignVCenter |
         Qt::TextShowMnemonic,
         text());
}

void JishoTabButton::moveEvent(QMoveEvent *event)
{
   QPushButton::moveEvent(event);
   emit geometryChanged();
}

void JishoTabButton::resizeEvent(QResizeEvent *event)
{
   QPushButton::resizeEvent(event);
   emit geometryChanged();
}

void JishoTabButton::checkStateSet()
{
   QPushButton::checkStateSet();
   if (isChecked())
      setCursor(Qt::ArrowCursor);
   else
      setCursor(Qt::PointingHandCursor);
}
