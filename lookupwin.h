#ifndef LOOKUPWIN_H
#define LOOKUPWIN_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QGridLayout>
#include <QToolButton>

#include "lookupedit.h"
#include "jisho.h"

class JishouToolButton: public QToolButton
{
   Q_OBJECT

public:
   JishouToolButton()
   {
//      setAutoRaise(true);
      setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
      setAutoFillBackground(true);
      setCheckable(true);
   }

   void setJishoStyle(const JishoStyle &style)
   {
      QPalette pal = palette();
      pal.setColor(QPalette::Window, style.fill);
      setPalette(pal);
   }
};

class JishoLookupWin: public QWidget
{
   Q_OBJECT
signals:

public:
   JishoLookupWin();

   void setJishoStyle(const JishoStyle &style);

   void retranslateUi();

   void focusLookupEdit();

private:
   QGridLayout m_glMain;
   JishoLookupEdit m_edLookup;
   QToolButton m_btnGo;
   JishouToolButton m_btnAutomatic, m_btnEnglish, m_btnRomaji, m_btnJapanese;
   QTextEdit m_htmlResults;

   QString defaultText() const;

private slots:
   void executeLookup();
};

#endif // LOOKUPWIN_H
