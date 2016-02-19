TEMPLATE = app

QT += qml quick core websockets webchannel
#webkitwidgets webchannel
CONFIG += c++11 console

!osx:qtHaveModule(webengine) {
        QT += webengine
        DEFINES += QT_WEBVIEW_WEBENGINE_BACKEND
}

SOURCES += main.cpp \
    websocketchannel/websocketclientwrapper.cpp \
    websocketchannel/websockettransport.cpp \
    webchannelobject/webchannelobject.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

DISTFILES +=

HEADERS += \
    websocketchannel/websocketclientwrapper.h \
    websocketchannel/websockettransport.h \
    webchannelobject/webchannelobject.h


