# -------------------------------------------------
# Project created by QtCreator 2010-05-12T15:34:55
# -------------------------------------------------
QT += core \
    gui \
    opengl
CONFIG += qaxcontainer
TARGET = mpsqt
TEMPLATE = app
UI_DIR = tmp
MOC_DIR = tmp
OBJECTS_DIR = tmp
SOURCES += src/main.cpp \
    src/mainwindow.cpp \
    src/SharedData/SharedData.cpp \
    src/DataLoader/TempestLoader.cpp \
    src/DataLoader/FileMapping.cpp \
    src/WidgetNavigator/WNavigator.cpp \
    src/WidgetNavigator/NavModelWellList.cpp \
    src/WidgetNavigator/NavModelProxyWellList.cpp \
    src/3DView/glwidget.cpp \
    src/SharedSelector/SharedSelector.cpp \
    rateswidget.cpp
HEADERS += src/SharedData/SharedData.h \
    src/DataLoader/IDataLoader.h \
    src/DataLoader/TempestLoader.h \
    src/mainwindow.h \
    src/DataLoader/FileMapping.h \
    src/WidgetNavigator/WNavigator.h \
    src/WidgetNavigator/NavModelWellList.h \
    src/WidgetNavigator/NavModelProxyWellList.h \
    src/3DView/glwidget.h \
    src/SharedSelector/SharedSelector.h \
    rateswidget.h
FORMS += src/mainwindow.ui \
    rateswidget.ui
