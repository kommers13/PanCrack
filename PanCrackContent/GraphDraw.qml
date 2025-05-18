import QtQuick
import QtQuick.Controls
import QtQuick.Shapes 2.15

Rectangle {

    id: root_graphdraw
    width: 850
    height: 920
    color: "#4A6A2E"

    Canvas {
        id: canvas_graphdraw
        width: parent.width
        height: parent.height
    }

}
