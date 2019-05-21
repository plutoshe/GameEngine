#-------------------------------------------------
#
# Project created by QtCreator 2019-05-17T15:01:42
#
#-------------------------------------------------

QT       += core gui opengl widgets
LIBS += -lOpengl32 -glu32
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = opengltest
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp

HEADERS += \
        cyLib/cyAlphaDistribution.h \
        cyLib/cyBVH.h \
        cyLib/cyColor.h \
        cyLib/cyCore.h \
        cyLib/cyGL.h \
        cyLib/cyHairFile.h \
        cyLib/cyHeap.h \
        cyLib/cyIPoint.h \
        cyLib/cyLightingGrid.h \
        cyLib/cyMatrix.h \
        cyLib/cyPoint.h \
        cyLib/cyPointCloud.h \
        cyLib/cyQuat.h \
        cyLib/cySampleElim.h \
        cyLib/cySpatial.h \
        cyLib/cyString.h \
        cyLib/cyTimer.h \
        cyLib/cyTriMesh.h \
        mainwindow.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    shader.fs \
    shader.vs \
    teapot.obj
