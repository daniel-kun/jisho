#ifndef LOOKUP_H
#define LOOKUP_H

#include <QVector>
#include <QString>
#include <QStringList>

struct JishoLookupResult
{
   QString kanji;
   QStringList meanings;
};

enum JishoLookupMode
{
   LookupNative,
   LookupRomaji,
   LookupJapanese
};

JishoLookupMode jishoGuessLookupMode(const QString &term);

QVector<JishoLookupResult> jishoLookup(const QString &term, JishoLookupMode mode);

#endif // LOOKUP_H
