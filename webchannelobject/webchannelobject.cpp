#include "webchannelobject/webchannelobject.h"

#include <QtCore/QDebug>
#include <QtWebSockets/QWebSocketServer>
#include <QClipboard>

QT_BEGIN_NAMESPACE

CommunObject::CommunObject(QGuiApplication* app)
        : QObject(nullptr), m_app(app) {
    QObject::connect(this, &CommunObject::appExit, app, &QGuiApplication::quit);
}
CommunObject::~CommunObject() {
    //qDebug() << "~CommunObject()";
    //delete m_engine;
}

void CommunObject::receiveStatus(const QString& text) {
    qDebug() << "receiveText: " << text;
    emit sendStatus(text);
}

void CommunObject::receiveKey(const QString& key) {
    qDebug() << "receiveKey: " << key;
    // debug
    emit sendStatus(key);
    // do something
    // ...
}

void CommunObject::receiveInfo2Encrypt(const QString& info) {
    qDebug() << "receiveInfo2Encrypt: " << info;
    // debug
    emit sendStatus(info);

    // do something
    // ...

    emit sendResults(info);
}
void CommunObject::receiveInfo2Decrypt(const QString& info) {
    qDebug() << "receiveInfo2Decrypt: " << info;
    // debug
    emit sendStatus(info);

    // do something
    // ...


    emit sendResults(info);
}

void CommunObject::copy2clipboard(const QString& results) {
    qDebug() << "copy2clipboard: " << results;
    //if (results == "") return false;

    QClipboard* clipboard = QGuiApplication::clipboard();
    clipboard->setText(results);
    const QString originalText = clipboard->text();

    // debug
    emit sendStatus("Clipboard text: " + originalText);
}

void CommunObject::clearClipboard() {
    QClipboard* clipboard = QGuiApplication::clipboard();

    clipboard->clear();
    /*
     * Qt bug:          'Android: QClipboard::clear() not implemented'
     * Bug description: 'This is done by calling setMimeData() with a null pointer,
     *                   but when that happens in the Android plugin we just return
     *                   without doing anything.'
     */
#if defined(Q_OS_ANDROID)
    clipboard->setMimeData(nullptr);
#endif
}
void CommunObject::appQuit() {
#if defined(Q_OS_ANDROID) || defined(Q_OS_IOS)
    //emit appExit();
    //QGuiApplication::exit(0);
    qApp->exit(0);
#else
    // desktop using QtWebKit
    // Force Quit the Application regardless of memory leaks
    exit(0); /* LEAK: 1 WebPageProxy; 1 WebContext */

    // In QtWebKit environment, if the program is executed one of these statements:
    // 'emit appExit()', 'QGuiApplication::exit(0)', 'qApp->exit(0)'
    // WITHOUT main.cpp:Force_Quit_regardless_of_memory_leaks(),
    // then an ERROR occur: 'pure virtual method called'
#endif
}

QT_END_NAMESPACE
