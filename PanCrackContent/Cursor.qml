import QtQuick
import QtQuick.Controls

Rectangle {
    id: root_cursor
    property int curwidth: 30
    property int curheight: 20
    property string curcolor: "#3ffffc"
    width: curwidth
    height: curheight
    color: curcolor
    Timer {
        interval: 400
        repeat: true
        running: true
        onTriggered: {
            root_cursor.visible = !root_cursor.visible
        }
    }

}
