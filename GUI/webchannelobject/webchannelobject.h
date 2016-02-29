#ifndef WEBCHANNELOBJECT_H
#define WEBCHANNELOBJECT_H

#include <QObject>
#include <QGuiApplication>
#include <QtCore/QDebug>
#include <QtWebSockets/QWebSocketServer>


class CommunObject : public QObject {
    Q_OBJECT
public:
    //explicit CommunObject(QObject* parent = 0) : QObject(parent) {}

    explicit CommunObject(QGuiApplication* app);
    virtual ~CommunObject();

public: signals:
    /*!
        This signal is emitted from the C++ side and the text displayed on the HTML client side.
    */
    void sendStatus(const QString& text);
    void sendResults(const QString& text);
    void appExit();
public slots:
    /*!
        This slot is invoked from the HTML client side and the text displayed on the server side.
    */
    void receiveStatus(const QString& text);
    //void receiveKey(const QString& key);
    //void receiveInfo2Encrypt(const QString& info);
    //void receiveInfo2Decrypt(const QString& info);
    void encrypt(const QString& key, const QString& info);
    void decrypt(const QString& key, const QString& info);

    void copy2clipboard(const QString& results);
    void clearClipboard();
    void appQuit();
private:
    QGuiApplication* m_app;
};

#endif // WEBCHANNELOBJECT_H
