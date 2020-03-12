SOURCES += $$files($$PWD/src/*.cpp, true) \
    $$PWD/src/LibPad/PsPad.c
SOURCES += $$files($$PWD/src/*.c, true)
HEADERS += $$files($$PWD/src/*.h, true) \
    $$PWD/src/LibPad/PsIo.h \
    $$PWD/src/LibPad/PsMemCard.h \
    $$PWD/src/LibPad/PsPad.h
INCLUDEPATH += $$PWD/Src
