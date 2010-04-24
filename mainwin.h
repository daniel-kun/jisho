#ifndef MAINWIN_H
#define MAINWIN_H

#include <QFrame>
#include <QGridLayout>
#include <QPushButton>
#include <QStackedWidget>

#include "lookupwin.h"
#include "tabbutton.h"
#include "tabpane.h"
#include "jisho.h"

class JishoMainWin: public QFrame
{
   Q_OBJECT
signals:

public:
   JishoMainWin();

   void setJishoStyle(const JishoStyle &style);

   virtual void retranslateUi();

public slots:
   void activateLookupPane();

   void activateLearnPane();

private:
   JishoStyle m_style;

   QGridLayout m_glMain;
   JishoTabButton m_btnLookup, m_btnLearn;
   JishoTabPane m_pane;
   QVBoxLayout m_vlPane;
   QStackedWidget m_swPane;
   JishoLookupWin m_lookupWin;

private slots:
   void updateGap();
};

#endif // MAINWIN_H
