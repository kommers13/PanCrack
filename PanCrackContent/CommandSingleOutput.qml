import QtQuick
import QtQuick.Controls

TextArea {
    property bool isLineEmpty: false
    id: commandAnswer
    height: !isLineEmpty ? 0 : font.pointSize * 1.274
    readOnly: true
    wrapMode: Text.Wrap
    textFormat: Text.MarkdownText
    font.family: "AcPlus IBM EGA 9x14"
    color: "#3ffffc"
    selectionColor: "#4d633d"
    font.pointSize: 25
}
