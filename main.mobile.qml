import QtQuick 2.5
import QtQuick.Window 2.2
import QtWebView 1.0   // mobile
//import QObject

Window {
    visible: true
    x: initialX
    y: initialY
    width: initialWidth
    height: initialHeight

    Rectangle {
        anchors.fill: parent

        WebView {
            id: webView
            objectName: "webView"
            anchors.fill: parent
            url: initialUrl
            /*
            function test() {
                runJavaScript("debug(this is a test);", function(result) { console.log(result); });
            }
            */
        }
    }
}
