import QtQuick
import QtQuick.Controls

TextInput {
    id: root_commandSingleLine
    property int tiwidth: 700
    property string ticolor: "#3ffffc"
    property int tipointSize: 30
    property string tifont: "AcPlus IBM EGA 9x14"
    property string tiselectionColor: "#4d633d"
    text: "PanCrack>"
    color: ticolor
    wrapMode: Text.Wrap
    selectionColor: tiselectionColor
    width: tiwidth
    font.pointSize: tipointSize
    font.family: "AcPlus IBM EGA 9x14"
    cursorDelegate: Cursor { curwidth: tipointSize / 2.6; curheight: tipointSize * 1.274; curcolor: ticolor}
    Keys.onPressed: (event) => {
                        let lw = "PanCrack>".length
                        if (event.key === Qt.Key_Backspace) {
                            if (cursorPosition <= lw) {
                                insert(cursorPosition, " ")
                            }
                        }
                    }
    onSelectionStartChanged: {
        let lw = "PanCrack>".length
        if (selectionStart < lw) {
            select(lw, selectionEnd)
        }
    }
}
