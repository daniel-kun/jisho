#include "lookup.h"

#include <QDir>
#include <QSet>
#include <QFile>
#include <QRegExp>
#include <QDesktopServices>

#include "sqlite3.h"

namespace
{
   QSet<QString> fileLoader(const QString &fileName)
   {
      QSet<QString> result;
      QFile file(fileName);
      if (file.open(QFile::ReadOnly))
      {
         while (!file.atEnd())
         {
            QByteArray line = file.readLine(128);
            result.insert(QString::fromUtf8(line.constData(), line.size()).trimmed());
         }
      }
      return result;
   }
}

JishoLookupMode jishoGuessLookupMode(const QString &term)
{
   if (term.indexOf(QRegExp("[abcdefghijklmnopqrstuvwxyz]")) >= 0)
   {
      static QSet<QString> kana = fileLoader(":/resources/kana.txt");
      QString checkTerm(term);
      bool kanaOk = true;
      while (!checkTerm.isEmpty())
      {
         bool found = false;
         foreach(QString k, kana)
         {
            if (checkTerm.startsWith(k))
            {
               found = true;
               checkTerm.remove(0, k.size());
               break;
            }
         }
         if (!found)
         {
            kanaOk = false;
            break;
         }
      }
      if (kanaOk)
         return LookupRomaji;
      else
         return LookupNative;
   }
   return LookupJapanese;
}

namespace
{
   void readToStringList(sqlite3_stmt *stmt, QStringList &list, int entry, const QString &lang = QString())
   {
      sqlite3_bind_int(stmt, 1, entry);
      if (!lang.isEmpty())
      {
         QByteArray ba = lang.toUtf8();
         sqlite3_bind_text(stmt, 2, ba.constData(), ba.size(), SQLITE_TRANSIENT);
      }
      int stepResult;
      while ((stepResult = sqlite3_step(stmt)) != SQLITE_DONE)
      {
         if (stepResult == SQLITE_ROW)
         {
            list.append(
                  QString::fromUtf8(
                        reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)),
                        -1));
         }

      }
   }
}

QVector<JishoLookupResult> jishoLookup(const QString &term, JishoLookupMode mode)
{
   QVector<JishoLookupResult> result;

   QDir appData(QDesktopServices::storageLocation(QDesktopServices::DataLocation));
   QString dbName = QDir::toNativeSeparators(appData.filePath("jpdict.sqlite3"));

   sqlite3 *db;
   if (sqlite3_open_v2(dbName.toUtf8().constData(), &db, SQLITE_OPEN_READONLY, 0) != SQLITE_OK)
      return result;

   QStringList statements;
   switch (mode)
   {
   case LookupNative:
      statements.append("select entry from gloss where lang='en' and upper(gloss)=upper(?)");
      break;
   case LookupRomaji:
      statements.append("select entry from reading where romaji=lower(?)");
      break;
   case LookupJapanese:
      statements.append("select entry from kanji where kanji=?");
      statements.append("select entry from reading where kana=?");
      break;
   }

   QSet<int> entries;

   foreach (QString sql, statements)
   {
      QByteArray baSql = sql.toUtf8();
      sqlite3_stmt *stmt;
      if (sqlite3_prepare_v2(db, baSql.constData(), baSql.size(), &stmt, 0) == SQLITE_OK)
      {
         QByteArray baParam = term.toUtf8();
         if (sqlite3_bind_text(stmt, 1, baParam.constData(), baParam.size(), SQLITE_TRANSIENT) == SQLITE_OK)
         {
            int stepResult;
            while ((stepResult = sqlite3_step(stmt)) != SQLITE_DONE)
            {
               if (stepResult == SQLITE_ROW)
                  entries.insert(sqlite3_column_int(stmt, 0));
            }
         }
         sqlite3_finalize(stmt);
      }
   }

   if (!entries.isEmpty())
   {
      sqlite3_stmt *stmtKana = 0, *stmtKanji = 0, *stmtMeanings = 0;
      if (sqlite3_prepare_v2(db, "select kana from reading where entry=?", -1, &stmtKana, 0) == SQLITE_OK &&
         sqlite3_prepare_v2(db, "select kanji from kanji where entry=?", -1, &stmtKanji, 0) == SQLITE_OK &&
         sqlite3_prepare_v2(db, "select gloss from gloss where entry=? and lang=? order by sense", -1, &stmtMeanings, 0) == SQLITE_OK)
      {
         foreach (int entry, entries)
         {
            sqlite3_reset(stmtKana);
            sqlite3_reset(stmtKanji);
            sqlite3_reset(stmtMeanings);
            QStringList kanas, kanjis, meanings;
            readToStringList(stmtKana, kanas, entry);
            readToStringList(stmtKanji, kanjis, entry);
            readToStringList(stmtMeanings, meanings, entry, "en");

            QString kanji;
            if (kanjis.isEmpty())
               kanji = kanas.join(", ");
            else
            {
               kanji = kanjis.join(", ");
               if (!kanas.isEmpty())
                  kanji += " (" + kanas.join(", ") + ")";
            }
            JishoLookupResult entry;
            entry.kanji = kanji;
            entry.meanings = meanings;
            result.append(entry);
         }
      }
      if (stmtKana)
         sqlite3_finalize(stmtKana);
      if (stmtKanji)
         sqlite3_finalize(stmtKanji);
      if (stmtMeanings);
      sqlite3_finalize(stmtMeanings);
   }

   sqlite3_close(db);


   return result;
}
