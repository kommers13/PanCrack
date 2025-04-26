import QtQuick
import QtQuick.Controls
import QtQuick.Shapes 2.15

Rectangle {

    width: 850
    height: 920
    color: "#020808"

    Rectangle {
        x: vb.startX - width / 2
        y: vb.startY - height / 2
        width: 40
        height: 40
        radius: 100
        color: "blue"
    }

    Rectangle {
        x: ve.x - width / 2
        y: ve.y - height / 2
        width: 40
        height: 40
        radius: 100
        color: "green"
    }

    Shape {
        ShapePath {
            strokeWidth: 2
            strokeColor: "cyan"
            startX: 30; startY: 30
            id: vb
            PathLine { id: ve; x: 190; y: 190 }
        }
    }

}
