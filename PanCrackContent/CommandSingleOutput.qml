// CommandSingleOutput.qml
import QtQuick
import QtQuick.Controls

TextEdit {
    property bool isLineEmpty: false
    id: commandAnswer
    height: 1
    wrapMode: TextEdit.Wrap
    textFormat: TextEdit.AutoText
    font.family: "Courier New"
    font.bold: true
    color: "#ff5555"  // Ярко-красный
    selectionColor: "#00ff00"
    font.pixelSize: 16

    // Только тёмный фон без эффектов
    Rectangle {
        anchors.fill: parent
        color: "#000000"
        z: -1
    }

    onContentHeightChanged: {
        if (text !== "") {
            height = contentHeight
        }
    }
}
