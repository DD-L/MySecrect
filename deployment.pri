#unix:!android {
#    isEmpty(target.path) {
#        qnx {
#            target.path = /tmp/$${TARGET}/bin
#        } else {
#            target.path = /opt/$${TARGET}/bin
#        }
#        export(target.path)
#    }
#    INSTALLS += target
#}

#export(INSTALLS)

android-no-sdk {
    target.path = /data/user/qt
    export(target.path)
    INSTALLS += target
} else:android {
    x86 {
        target.path = /libs/x86
    } else: armeabi-v7a {
        target.path = /libs/armeabi-v7a
    } else {
        target.path = /libs/armeabi
    }
    export(target.path)
    INSTALLS += target

    #deployment.files += $files($PWD/html/*)
    html.path = /assets/html/
    html.files += ./html/home.htm
    css.path  = /assets/html/css
    css.files += ./html/css/jquery.mobile-1.4.5.min.css
    css.files += ./html/css/style.css
    css.files += ./html/css/ajax-loader.gif
    javascript.path = /assets/html/js
    javascript.files += ./html/js/jquery-1.10.2.min.js
    javascript.files += ./html/js/jquery.mobile-1.4.5.min.js
    javascript.files += ./html/js/qwebchannel.js
    javascript.files += ./html/js/home.js

    INSTALLS += html css javascript
} else:unix {
    isEmpty(target.path) {
        qnx {
            target.path = /tmp/$${TARGET}/bin
        } else {
            target.path = /opt/$${TARGET}/bin
        }
        export(target.path)
    }
    INSTALLS += target
}
export(INSTALLS)


