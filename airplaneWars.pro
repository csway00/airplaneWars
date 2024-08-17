QT += widgets multimedia

CONFIG += c++17 cmdline

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        animation.cpp \
        bullet.cpp \
        enemyplane.cpp \
        game.cpp \
        grade.cpp \
        main.cpp \
        mainscene.cpp \
        map.cpp \
        mypushbutton.cpp \
        playerplane.cpp \
        sprite.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    Manager.h \
    animation.h \
    bullet.h \
    enemyplane.h \
    entity.h \
    game.h \
    global.h \
    grade.h \
    mainscene.h \
    map.h \
    mypushbutton.h \
    playerplane.h \
    sprite.h

RESOURCES += \
    sound.qrc \
    src.qrc
