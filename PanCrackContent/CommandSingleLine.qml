import QtQuick
import QtQuick.Controls

TextEdit {

    signal accepted()

    id: root_commandSingleLine
    text: "PanCrack>"
    color: "#3ffffc"
    wrapMode: Text.Wrap
    // textFormat: Text.MarkdownText
    selectionColor: "#4d633d"
    width: 700
    font.pointSize: 22
    cursorPosition: text.length
    focus: true
    font.family: "AcPlus IBM EGA 9x14"
    cursorDelegate: Cursor { focus: true; curwidth: font.pointSize / 2.6; curheight: font.pointSize * 1.274; curcolor: "#3ffffc"}
    Keys.onPressed: (event) => {
                        let lw = "PanCrack>".length
                        if (event.key === Qt.Key_Backspace) {
                            if (cursorPosition <= lw) {
                                insert(cursorPosition, " ")
                            }
                        }
                        else if ((event.key === Qt.Key_Enter || event.key === Qt.Key_Return) &&
                                 (event.modifiers & Qt.ShiftModifier)) {
                            // перенос на новую строку
                        }
                        else if (event.key === Qt.Key_Enter || event.key === Qt.Key_Return) {
                            accepted()
                            event.accepted = true   // prevent propagation
                        }

                    }
    onSelectionStartChanged: {
        let lw = "PanCrack>".length
        if (selectionStart < lw) {
            select(lw, selectionEnd)
        }
    }
}
