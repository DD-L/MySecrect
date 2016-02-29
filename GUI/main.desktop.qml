import QtQuick 2.5
import QtQuick.Window 2.2
import QtQuick.Controls 1.1
import QtWebKit 3.0   // Desktop

//import QtWebChannel 1.0
//import QtWebKit.experimental 1.0
//import QtWebEngine 1.1


//import QtQuick.Layouts 1.1
//import QtQuick.Controls.Styles 1.2


//Window {
ApplicationWindow {
    visible: true
    x: initialX
    y: initialY
    width: initialWidth
    height: initialHeight
    title: webView.title

    Rectangle {
        anchors.fill: parent


        /*
        QtObject {
            id: foo
            WebChannel.id: "foo"
            signal someSignal(string message);

            function someMethod(message) {
                console.log(message);
                someSignal(message);
                return "foobar";
            }
            property string hello: "world"
        }
        */

        WebView {
            id: webView
            objectName: "webView"
            anchors.fill: parent
            url: initialUrl
            //experimental.webChannel.registeredObjects: [foo]

        }
    }
}
