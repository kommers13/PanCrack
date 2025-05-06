import QtQuick
import QtQuick.Controls

Rectangle {
    id: root_dialogInput
    width: 500
    height: 500
    color: "#f00a2a2a"
    clip: false

    TextEdit {
        wrapMode: TextEdit.Wrap
        clip: true
        id: dialogInput_textedit
        x: 8
        y: 8
        width: 480
        height: 480
        color: "#3ffffc"
        font.pointSize: 22
        font.family: "AcPlus IBM EGA 9x14"
        focus: true
        cursorDelegate: Cursor { focus: true; curwidth: dialogInput_textedit.font.pointSize / 2.6; curheight: dialogInput_textedit.font.pointSize * 1.274; curcolor: "#3ffffc"}
    }
}
