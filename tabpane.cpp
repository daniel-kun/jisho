#include "tabpane.h"

#include <QPainter>
#include <QPaintEvent>

JishoTabPane::JishoTabPane():
      m_gapFrom(0),
      m_gapTo(0)
{
   setMinimumSize(400, 300);
   setAutoFillBackground(true);
}

void JishoTabPane::setJishoStyle(const JishoStyle &style)
{
   m_style = style;
   update();
}

void JishoTabPane::setGap(int from, int to)
{
   m_gapFrom = from;
   m_gapTo = to;
   update();
}

void JishoTabPane::paintEvent(QPaintEvent *event)
{
   QWidget::paintEvent(event);

   QPainter painter(this);
   painter.fillRect(event->rect(), m_style.fill);
   painter.setPen(m_style.border);

   QRect r = event->rect();

   painter.drawLine(r.topLeft(), r.bottomLeft());
   painter.drawLine(r.bottomLeft(), r.bottomRight());
   painter.drawLine(r.bottomRight(), r.topRight());

   if (m_gapFrom > 0)
   {
      painter.drawLine(r.topLeft(), QPoint(m_gapFrom, 0));
   }
   painter.drawLine(QPoint(m_gapTo, 0), r.topRight());
}
