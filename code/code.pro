TEMPLATE = app

QT += qml quick core
CONFIG += c++11 console
TARGET = IpcCamera
QMAKE_CLEAN += $$TARGET

RESOURCES += \
    qml.Resources.qrc \
    resources.qrc

INCLUDEPATH += widgets models

equals( QT_MAJOR_VERSION, 5 ) {
    CONFIG += c++11
    QT += qml quick widgets network quickwidgets multimedia  serialport
    DEFINES += QT5VERSION
    message(" ================ QT 5 VERSION ================ ")
}
else {
    QMAKE_CXXFLAGS += -std=c++11
    QT += widgets declarative network serialport multimedia
    DEFINES += QT4VERSION
    message(" ================ QT 4 VERSION================= ")
}

CONFIG(debug, debug|release){
    DEFINES -= QT_NO_DEBUG_OUTPUT
}
else{
    DEFINES += QT_NO_DEBUG_OUTPUT
}

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    widgets/ApplicationContext.h \
    widgets/DeclarativeWindow.h \
    widgets/SlidingStackedWidget.h \
    widgets/Toast.h \
    widgets/Window.h \
    widgets/WinManager.h \
    IpcCameraApplication.h \
    models/LoginModel.h

SOURCES += \
    widgets/ApplicationContext.cpp \
    widgets/DeclarativeWindow.cpp \
    widgets/SlidingStackedWidget.cpp \
    widgets/Toast.cpp \
    widgets/Window.cpp \
    widgets/WinManager.cpp \
    IpcCameraApplication.cpp \
    main.cpp \
    models/LoginModel.cpp
