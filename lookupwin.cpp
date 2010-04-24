#include "lookupwin.h"

#include <QPaintEvent>
#include <QPainter>
#include <QFile>

#include "lookup.h"

JishoLookupWin::JishoLookupWin():
      m_glMain(this)
{
   int row = 0;
   m_glMain.addWidget(&m_edLookup, row, 0, 1, 5);
   m_glMain.addWidget(&m_btnGo, row++, 5);
/*   m_glMain.addWidget(&m_btnAutomatic, row, 0);
   m_glMain.addWidget(&m_btnEnglish, row, 1);
   m_glMain.addWidget(&m_btnRomaji, row, 2);
   m_glMain.addWidget(&m_btnJapanese, row++, 3);*/
   m_glMain.addWidget(&m_htmlResults, row, 0, 1, 6);
   m_glMain.setColumnStretch(4, 1);
   m_glMain.setRowStretch(row++, 1);

   m_btnGo.setIcon(QPixmap(":/resources/icon-go.png"));
   m_btnAutomatic.setIcon(QPixmap(":/resources/icon-automatic.png"));
   m_btnEnglish.setIcon(QPixmap(":/resources/icon-abc.png"));
   m_btnRomaji.setIcon(QPixmap(":/resources/icon-romaji.png"));
   m_btnJapanese.setIcon(QPixmap(":/resources/icon-kanji.png"));

   m_btnGo.setAutoRaise(true);

   m_htmlResults.setFrameShape(QFrame::Box);
   m_htmlResults.setAutoFillBackground(true);
   m_htmlResults.setReadOnly(true);
   m_htmlResults.setHtml(defaultText());

   retranslateUi();

   connect(&m_edLookup, SIGNAL(returnPressed()), SLOT(executeLookup()));
   connect(&m_btnGo, SIGNAL(clicked()), SLOT(executeLookup()));
}

void JishoLookupWin::setJishoStyle(const JishoStyle &style)
{
   m_htmlResults.setStyleSheet(QString("background-color: %1;").arg(style.fillHighlight.name()));
   m_btnAutomatic.setJishoStyle(style);
   m_btnEnglish.setJishoStyle(style);
   m_btnRomaji.setJishoStyle(style);
   m_btnJapanese.setJishoStyle(style);
}

void JishoLookupWin::retranslateUi()
{
   m_btnAutomatic.setText(tr("&Auto"));
   m_btnEnglish.setText(tr("&English"));
   m_btnRomaji.setText(tr("&Romaji"));
   m_btnJapanese.setText(tr("&Japanese"));
}

void JishoLookupWin::focusLookupEdit()
{
   m_edLookup.setFocus(Qt::ShortcutFocusReason);
}

QString JishoLookupWin::defaultText() const
{
   QFile f(":/resources/default-text.html");
   f.open(QFile::ReadOnly);
   QByteArray defaultText(f.readAll());
   return QString::fromUtf8(defaultText.constData(), defaultText.size());
}

void JishoLookupWin::executeLookup()
{
   QString text = m_edLookup.text().trimmed();
   QString html;
   if (text.isEmpty())
   {
      html = defaultText();
   }
   else
   {
      QVector<JishoLookupResult> result =  jishoLookup(m_edLookup.text(), jishoGuessLookupMode(m_edLookup.text()));
      if (!result.isEmpty())
      {
         foreach (JishoLookupResult entry, result)
         {
            html += "<h1>" + entry.kanji + "</h1>";
            html += "<ol>";
            foreach (QString meaning, entry.meanings)
            {
               html += "<li>" + meaning + "</li>";
            }

            html += "</ol>\n";
         }
      }
      else
      {
         QFile f(":/resources/no-result.html");
         f.open(QFile::ReadOnly);
         QByteArray ba = f.readAll();
         html = QString::fromUtf8(ba.constData(), ba.size());
      }
   }
   m_htmlResults.setHtml(html);
}
