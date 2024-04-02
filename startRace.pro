QT       += core widgets
TARGET = startRace
TEMPLATE = app 

CONFIG += c++11

SOURCES += \
    horse.cpp \
    startRace.cpp \
    gamewindow.cpp\
    bet.cpp

HEADERS  += gamewindow.h \
            bet.h \
            horse.h \
            startRace.h

RESOURCES += \
    derbyRes.qrc
