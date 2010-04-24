#ifndef TABPANE_H
#define TABPANE_H

#include <QWidget>

#include "jisho.h"

class JishoTabPane: public QWidget
{
   Q_OBJECT

signals:

public:
   JishoTabPane();

   void setJishoStyle(const JishoStyle &style);
   void setGap(int from, int to);

protected:
   virtual void paintEvent(QPaintEvent *event);

private:
   JishoStyle m_style;
   int m_gapFrom, m_gapTo;
};

#endif // TABPANE_H
