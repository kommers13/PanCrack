// Cursor.qml
import QtQuick
import QtQuick.Controls

Rectangle {
    id: root_cursor
    property int curwidth: 2
    property int curheight: 20
    property string curcolor: "#00ff00"
    width: curwidth
    height: curheight
    color: curcolor
    visible: true

    // Эффект "глючного" свечения (альтернатива Glow)
    Rectangle {
        anchors.centerIn: parent
        width: parent.width + 4
        height: parent.height + 4
        color: "#00ff00"
        opacity: 0.3
        visible: parent.visible
    }

    Timer {
        interval: 500
        repeat: true
        running: parent.parent.activeFocus
        onTriggered: {
            root_cursor.visible = !root_cursor.visible
        }
    }
}
