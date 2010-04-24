#ifndef TABBUTTON_H
#define TABBUTTON_H

#include <QPushButton>
#include <QPainterPath>

#include "jisho.h"

class JishoTabButton: public QPushButton
{
   Q_OBJECT

signals:
   void geometryChanged();

public:
   JishoTabButton();

   void setJishoStyle(const JishoStyle &style);

protected:
   virtual void paintEvent(QPaintEvent *event);

   virtual void moveEvent(QMoveEvent *event);
   virtual void resizeEvent(QResizeEvent *event);

   virtual void checkStateSet();

private:
   JishoStyle m_style;
   QPainterPath m_path;
};

#endif // TABBUTTON_H
