#ifndef LOOKUPEDIT_H
#define LOOKUPEDIT_H

#include <QLineEdit>

class JishoLookupEdit: public QLineEdit
{
   Q_OBJECT
public:
    JishoLookupEdit();

protected:
    virtual void paintEvent(QPaintEvent *event);
};

#endif // LOOKUPEDIT_H
