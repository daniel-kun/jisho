#include "mainwin.h"

JishoMainWin::JishoMainWin():
      m_glMain(this),
      m_vlPane(&m_pane)
{
   setWindowIcon(QIcon(":/resources/logo-jisho.ico"));

   QPalette pal = palette();
   pal.setBrush(QPalette::Window, Qt::white);
   setPalette(pal);

   m_glMain.setSpacing(0);
   m_glMain.addWidget(&m_btnLookup, 0, 0);
//   m_glMain.addWidget(&m_btnLearn, 0, 2);
   m_glMain.setColumnMinimumWidth(1, 5);
   m_glMain.setColumnStretch(3, 1);
   m_glMain.addWidget(&m_pane, 1, 0, 1, 4);

   m_vlPane.setMargin(0);
   m_vlPane.addWidget(&m_swPane);
   m_swPane.addWidget(&m_lookupWin);
   m_swPane.setCurrentWidget(&m_lookupWin);

   JishoStyle defaultStyle;
   defaultStyle.border = QColor("#AACCEE");
   defaultStyle.fill = QColor("#F4FAFF");
   defaultStyle.fillHighlight = QColor("#D6ECFF");

   setJishoStyle(defaultStyle);

   activateLookupPane();

   connect(&m_btnLookup, SIGNAL(clicked()), SLOT(activateLookupPane()));
   connect(&m_btnLearn, SIGNAL(clicked()), SLOT(activateLearnPane()));
   connect(&m_btnLookup, SIGNAL(geometryChanged()), SLOT(updateGap()));
   connect(&m_btnLearn, SIGNAL(geometryChanged()), SLOT(updateGap()));

   retranslateUi();
}

void JishoMainWin::activateLookupPane()
{
   m_btnLearn.setChecked(false);
   m_btnLookup.setChecked(true);

   m_lookupWin.focusLookupEdit();

   updateGap();
}

void JishoMainWin::activateLearnPane()
{
   m_btnLearn.setChecked(true);
   m_btnLookup.setChecked(false);

   updateGap();
}

void JishoMainWin::updateGap()
{
   QPushButton *btn;
   if (m_btnLearn.isChecked())
      btn = &m_btnLearn;
   else
      btn = &m_btnLookup;
   int x = btn->x() - m_pane.x();
   m_pane.setGap(x, btn->geometry().right() - m_pane.x());
}

void JishoMainWin::setJishoStyle(const JishoStyle &style)
{
   m_style = style;
   m_btnLookup.setJishoStyle(style);
   m_btnLearn.setJishoStyle(style);
   m_pane.setJishoStyle(style);
   m_lookupWin.setJishoStyle(style);
}

void JishoMainWin::retranslateUi()
{
   setWindowTitle("Jisho - The japanese dictionary");
   m_btnLookup.setText(tr("&Lookup"));
   m_btnLearn.setText(tr("Lear&n"));
}
