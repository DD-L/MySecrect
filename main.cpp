#include <QObject>
#include <QtCore/QUrl>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml/QQmlContext>

#include <QStyleHints>
#include <QRect>
#include <QScreen>

#include <QDebug>
#include <QDir>

#ifdef QT_WEBVIEW_WEBENGINE_BACKEND
#include <QtWebEngine>
#endif // QT_WEBVIEW_WEBENGINE_BACKEND


//#include <QtCore/QCoreApplication>
//#include "websocket/echoserver.h"
//#include "websocket/sslechoserver.h"

#include <QtWebSockets/QWebSocketServer>
#include <QtWebChannel/QtWebChannel>
#include "websocketchannel/websocketclientwrapper.h"
#include "websocketchannel/websockettransport.h"
#include "webchannelobject/webchannelobject.h"


/**
 * @brief  listen_port
 * @param  server
 * @return listen port. port == 0: Failed to open web socket server;
 */
uint16_t listen_port(QWebSocketServer& server) {
    uint16_t port = 11000;
    const uint16_t max_port = 60000;
    for (; port <= max_port; ++port) {
        if (server.listen(QHostAddress::LocalHost, port)) {
            qDebug("listen port: %d", port);
            return port;
        }
        else {
            qWarning("Failed to listen port: %d", port);
        }
    }
    qFatal("Failed to open web socket server.");
    return 0;
}

/**
 * @brief load_qml
 * @param engine
 * @param baseUrlArg
 */
void load_qml(QQmlApplicationEngine& engine, const QString& baseUrlArg) {
    QQmlContext *context = engine.rootContext();

#if defined(Q_OS_ANDROID) || defined(Q_OS_IOS)
    //const QUrl initialUrl("file:///android_asset/html/home.htm?webChannelBaseUrl=ws://127.0.0.1:12345"); // mobile
    const QUrl initialUrl("file:///android_asset/html/home.htm" + baseUrlArg); // mobile
#else
    //const QUrl initialUrl("qrc:/html/home.htm?webChannelBaseUrl=ws://127.0.0.1:12345"); // Desktop
    const QUrl initialUrl("qrc:/html/home.htm" + baseUrlArg); // Desktop
#endif
    context->setContextProperty(QStringLiteral("initialUrl"), initialUrl);

    QRect geometry = QGuiApplication::primaryScreen()->availableGeometry();
    if (! QGuiApplication::styleHints()->showIsFullScreen()) {
        const QSize size = geometry.size() * 4 / 5;
        const QSize offset = (geometry.size() - size) / 2;
        const QPoint pos = geometry.topLeft() + QPoint(offset.width(), offset.height());
        geometry = QRect(pos, size);
    }
    context->setContextProperty(QStringLiteral("initialX"), geometry.x());
    context->setContextProperty(QStringLiteral("initialY"), geometry.y());
    context->setContextProperty(QStringLiteral("initialWidth"), geometry.width());
    context->setContextProperty(QStringLiteral("initialHeight"), geometry.height());
    //context->setContextProperty(QStringLiteral("webView.title"), "test");

#if defined(Q_OS_ANDROID) || defined(Q_OS_IOS)
    engine.load(QUrl(QStringLiteral("qrc:/main.mobile.qml")));
#else
    engine.load(QUrl(QStringLiteral("qrc:/main.desktop.qml")));
#endif


}

/**
 * @brief Force_Quit_regardless_of_memory_leaks
 */
//#include <thread>
//#include <chrono>
void Force_Quit_regardless_of_memory_leaks() {
    /**
     * If I do not, then I cant solve this problem:
     * 		ASSERTION FAILED: The string being removed is atomic in the string table of an other thread!
     * 		iterator != atomicStringTable.end()
     * 		wtf\text\AtomicString.cpp(430) : static void WTF::AtomicString::remove(WTF::StringImpl*)
     *
     * !!!! This is a QtWebKit bug: !!!!
     * see
     * https://bugreports.qt.io/browse/QTBUG-48305
     * ```````````````````````````````````````````
     * Perhaps same as, or not.
     *
     * And I found a similar situation:
     * https://lists.webkit.org/pipermail/webkit-dev/2013-September/025482.html
     */
    qWarning("Force Quit the Application regardless of memory leaks !!!!");
    //std::this_thread::sleep_for(std::chrono::seconds(1));
    exit(0);
}
int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

#if !defined(Q_OS_ANDROID) && !defined(Q_OS_IOS)
    // There are many problems and bugs in QtWebKit,
    QObject::connect(&app, &QGuiApplication::aboutToQuit ,&Force_Quit_regardless_of_memory_leaks);
#endif

#ifdef QT_WEBVIEW_WEBENGINE_BACKEND
    QtWebEngine::initialize();
#endif // QT_WEBVIEW_WEBENGINE_BACKEND


    // 1. ws://
    //uint16_t port = 1234; bool debug = false;
    //EchoServer *server = new EchoServer(port = 1234, debug = true);
    //QObject::connect(server, &EchoServer::closed, &app, &QGuiApplication::quit);
    // end 1. ws://

    // 2. wss://
    //SslEchoServer server(1234);
    //Q_UNUSED(server);
    // end 2. wss://

    //3. The server operates in non-secure mode (over ws)
    // setup the QWebSocketServer
    QWebSocketServer server(QStringLiteral("QWebChannel Standalone Example Server"),
                            QWebSocketServer::NonSecureMode);

    // The server operates in secure mode (over wss)
    //QWebSocketServer server(QStringLiteral("QWebChannel Standalone Example Server"),
    //                        QWebSocketServer::SecureMode);

    // listen
    const uint16_t port = listen_port(server);
    // get port
    const QString port_str = QString::number(port);
    if (port == 0) {
        return 1;
    }

    const QString base_url_arg =  "?webChannelBaseUrl=ws://127.0.0.1:" + port_str;
    load_qml(engine, base_url_arg);

    // wrap WebSocket clients in QWebChannelAbstractTransport objects
    WebSocketClientWrapper clientWrapper(&server);

    // setup the channel
    QWebChannel channel;
    QObject::connect(&clientWrapper, &WebSocketClientWrapper::clientConnected,
                     &channel, &QWebChannel::connectTo);

    // setup the commun_object and publish it to the QWebChannel
    CommunObject commun_object(&app);
    channel.registerObject(QStringLiteral("commun_object"), &commun_object);

    // end 3.

    return app.exec();
}
