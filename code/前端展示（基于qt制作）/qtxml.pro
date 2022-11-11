QT       += core gui
QT       +=sql
RC_ICONS = images/icon.ico
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    author_works.cpp \
    authorcount.cpp \
    cluster.cpp \
    fuzzsearch.cpp \
    graph.cpp \
    main.cpp \
    mainwindow.cpp \
    menu.cpp \
    show_coauthor.cpp \
    show_detail.cpp \
    yearsanalysiswidget.cpp

HEADERS += \
    author_works.h \
    authorcount.h \
    beautifulqss.h \
    cluster.h \
    fuzzsearch.h \
    graph.h \
    mainwindow.h \
    menu.h \
    show_coauthor.h \
    show_detail.h \
    yearsanalysiswidget.h

FORMS += \
    author_works.ui \
    authorcount.ui \
    cluster.ui \
    fuzzsearch.ui \
    graph.ui \
    mainwindow.ui \
    menu.ui \
    show_coauthor.ui \
    show_detail.ui \
    yearsanalysiswidget.ui

TRANSLATIONS += \
    qtxml_zh_CN.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    images/bg.jpg \
    images/icon.ico

RESOURCES += \
    images.qrc
