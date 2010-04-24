#include "lookupedit.h"

#include <QPainter>
#include <QPaintEvent>

JishoLookupEdit::JishoLookupEdit()
{
}

void JishoLookupEdit::paintEvent(QPaintEvent *event)
{
   QLineEdit::paintEvent(event);

   if (text().isEmpty())
   {
      QPainter painter(this);
      QRect r = event->rect();
      int marginLeft, marginTop, marginRight, marginBottom;
      getTextMargins(
            &marginLeft,
            &marginTop,
            &marginRight,
            &marginBottom);
      r.adjust(marginLeft + 15, marginTop, -marginRight - 15, -marginBottom);
      painter.setPen(palette().color(QPalette::Dark));
      painter.drawText(r, Qt::AlignHCenter | Qt::AlignVCenter, tr("Enter search phrase here"));
   }
}
