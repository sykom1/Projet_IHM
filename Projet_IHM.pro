QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    barbuttonretouch.cpp \
    chosecolor.cpp \
    colorparameter.cpp \
    displaycontains.cpp \
    drawcolormenu.cpp \
    filters.cpp \
    imageforchange.cpp \
    initconfig.cpp \
    loadsettings.cpp \
    main.cpp \
    mainwindowmenu.cpp \
    formsandcrop.cpp \
    menusettings.cpp \
    resizepicture.cpp

HEADERS += \
    barbuttonretouch.h \
    chosecolor.h \
    colorparameter.h \
    displaycontains.h \
    drawcolormenu.h \
    filters.h \
    imageforchange.h \
    initconfig.h \
    loadsettings.h \
    mainwindowmenu.h \
    formsandcrop.h \
    menusettings.h \
    resizepicture.h

FORMS += \
    chosecolor.ui \
    colorparameter.ui \
    initconfig.ui \
    mainwindowmenu.ui
TRANSLATIONS += english.ts \ francais.ts

RC_ICONS = icon.ico

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    imgLogo.qrc \
    translations.qrc
