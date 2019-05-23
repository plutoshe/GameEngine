#-------------------------------------------------
#
# Project created by QtCreator 2019-05-23T20:25:57
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Flight
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
        Engine/Collider2D.cpp \
        Engine/Delegate.cpp \
        Engine/GameManager.cpp \
        Engine/GameObject.cpp \
        Engine/GameObjectBasicAttr.cpp \
        Engine/GameObjectManager.cpp \
        Engine/GeoLine.cpp \
        Engine/GeoMethod.cpp \
        Engine/GeoPoint.cpp \
        Engine/InputController.cpp \
        Engine/Log.cpp \
        Engine/LuaUtil.cpp \
        Engine/Matrix4x4.cpp \
        Engine/Message.cpp \
        Engine/MessageController.cpp \
        Engine/PhysicsComponent.cpp \
        Engine/PhysicsController.cpp \
        Engine/RenderComponent.cpp \
        Engine/RenderController.cpp \
        Engine/SSERedef.cpp \
        Engine/SmartPointer.cpp \
        Engine/Status.cpp \
        Engine/Timing.cpp \
        Engine/Vector.cpp \
        Engine/Vector2D.cpp \
        Engine/Vector3D.cpp \
        Engine/Vector4D.cpp \
        Engine/stdafx.cpp \
        main.cpp \
        mainwindow.cpp

HEADERS += \
        Engine/BasicMacros.h \
        Engine/Collider2D.h \
        Engine/Delegate.h \
        Engine/Engine.h \
        Engine/GameManager.h \
        Engine/GameObject.h \
        Engine/GameObjectBasicAttr.h \
        Engine/GameObjectManager.h \
        Engine/GeoLine.h \
        Engine/GeoMethod.h \
        Engine/GeoPoint.h \
        Engine/InputController.h \
        Engine/List.h \
        Engine/Log.h \
        Engine/LuaUtil.h \
        Engine/Matrix4x4.h \
        Engine/Message.h \
        Engine/MessageController.h \
        Engine/PhysicsComponent.h \
        Engine/PhysicsController.h \
        Engine/RenderComponent.h \
        Engine/RenderController.h \
        Engine/SmartPointer.h \
        Engine/StaticVariable.h \
        Engine/Status.h \
        Engine/Timing.h \
        Engine/Vector.h \
        Engine/Vector2D.h \
        Engine/Vector3D.h \
        Engine/Vector4D.h \
        Engine/VectorUtil.h \
        Engine/sseRedef.h \
        Engine/stdafx.h \
        Engine/targetver.h \
        mainwindow.h

FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    Engine/Engine.vcxproj \
    Engine/Engine.vcxproj.filters
