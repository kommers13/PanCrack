import QtQuick
import QtQuick.Controls

TextEdit {
    property bool isLineEmpty: false
    id: commandAnswer
    // readOnly: true
    height: 1
    wrapMode: TextEdit.Wrap
    // textFormat: TextEdit.MarkdownText
    // textFormat: TextEdit.RichText
    textFormat: TextEdit.AutoText
    font.family: "AcPlus IBM EGA 9x14"
    color: "#3ffffc"
    selectionColor: "#4d633d"
    font.pointSize: 22
    onContentHeightChanged: {
        if (text !== "") {
            height = contentHeight
        }
    }
}
