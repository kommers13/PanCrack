

/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/
import QtQuick
import QtQuick.Controls
import PanCrack
import QtQuick.Timeline 1.0

Rectangle {
    width: Constants.width
    height: Constants.height

    color: Constants.backgroundColor

    CommandLine {
        id: commandLine
        x: 86
        y: 80
        clip: true
    }
    Rectangle {
        width: 100
        height: 100
        x: parent.width - 86 - 850
        y: 80
    }

    Canvas {
        id: canvas_graphdraw
        width: 850
        height: 920
        x: parent.width - 86 - width
        y: 80
    }

    Connections {
        target: canvas_graphdraw
        onAvailableChanged: {
            // заполняем соответствующей краской при создании Canvas-а
            if (canvas_graphdraw.available) {
                let ctx = canvas_graphdraw.getContext("2d");
                ctx.fillStyle = Qt.rgba(0.007, 0.03, 0.03, 1);
                ctx.fillRect(0, 0, canvas_graphdraw.width, canvas_graphdraw.height);
                canvas_graphdraw.requestPaint();
            }
        }
    }
}
