HEADERS += mainwin.h \
    lookupwin.h \
    tabbutton.h \
    jisho.h \
    tabpane.h \
    lookupedit.h \
    lookup.h
SOURCES += mainwin.cpp \
    jisho.cpp \
    lookupwin.cpp \
    tabbutton.cpp \
    tabpane.cpp \
    lookupedit.cpp \
    ../../../Qt/2010.02.1/qt/src/3rdparty/sqlite/sqlite3.c \
    lookup.cpp
INCLUDEPATH += ../../../Qt/2010.02.1/qt/src/3rdparty/sqlite/
RESOURCES += jisho.qrc
