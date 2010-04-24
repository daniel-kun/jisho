#include <QApplication>

#include "mainwin.h"

int main(int argc, char *argv[])
{
   QApplication app(argc, argv);
   app.setApplicationName("Jisho");
   app.setOrganizationName("");

   JishoMainWin mainWin;
   mainWin.show();

   return app.exec();
}
