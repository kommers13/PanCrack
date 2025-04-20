import QtQuick
import QtQuick.Controls

TextEdit {
    property bool isLineEmpty: false
    id: commandAnswer
    height: !isLineEmpty ? 1 : font.pointSize * 1.7
    readOnly: true
    wrapMode: TextArea.Wrap
    textFormat: TextArea.MarkdownText
    font.family: "AcPlus IBM EGA 9x14"
    color: "#3ffffc"
    selectionColor: "#4d633d"
    font.pointSize: 22
    // text: "I AM BOBER"
}
