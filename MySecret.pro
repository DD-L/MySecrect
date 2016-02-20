TEMPLATE = app
TARGET = MySecret

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


DISTFILES +=

HEADERS += \
    websocketchannel/websocketclientwrapper.h \
    websocketchannel/websockettransport.h \
    webchannelobject/webchannelobject.h

INCLUDEPATH += ./lproxy/contrib/cryptopp/cryptopp ./lproxy/src/core/crypto

# Please modify the following statements by yourself
android {
        x86 {
            LIBS += -L ./libs/Androidx86 -lcryptopp
        }
        else : armeabi-v7a {
            LIBS += -L ./libs/Androidarmeabiv7a -lcryptopp
        }
        else {
            LIBS += -L ./libs/Android -lcryptopp
        }
}
win32 {
        LIBS += -L ./libs/MinGW32bit -lcryptopp
}


# Default rules for deployment.
include(deployment.pri)
