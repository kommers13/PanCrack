// CommandSingleLine.qml
import QtQuick
import QtQuick.Controls


TextEdit {
    signal accepted()

    id: root_commandSingleLine
    text: "PanCrack>"
    color: "#00ff00"
    wrapMode: Text.Wrap
    selectionColor: "#00ff00"
    selectedTextColor: "#000000"
    width: 700
    font.pixelSize: 16
    // cursorPosition: text.length
    focus: true
    font.family: "Courier New"
    font.bold: true

    // Подключаем наш моргающий курсор
    cursorDelegate: Cursor {
        curwidth: 2
        curheight: font.pixelSize * 1.2
        curcolor: "#00ff00"
    }

    // Только тёмный фон без рамки
    Rectangle {
        anchors.fill: parent
        color: "#111111"
        z: -1
    }

    Keys.onPressed: (event) => {
        let lw = "PanCrack>".length
        if (event.key === Qt.Key_Backspace || event.key === Qt.Key_Delete) {
            let current_cursorPosition = cursorPosition;
            if (cursorPosition <= lw) {
                // clear();
                // insert(0, "PanCrack>");
                event.accepted = true;  // приняли event, дальше не пускаем
                // insert(cursorPosition, " ")
            }
            cursorPosition = current_cursorPosition;
        }
        else if ((event.key === Qt.Key_Enter || event.key === Qt.Key_Return) &&
                 (event.modifiers & Qt.ShiftModifier)) {
            // перенос на новую строку
        }
        else if (event.key === Qt.Key_Enter || event.key === Qt.Key_Return) {
            accepted()
            event.accepted = true
        }
    }

    onSelectionStartChanged: {
        let lw = "PanCrack>".length
        if (selectionStart <= lw) {
            if (selectionStart == selectionEnd) {
                select(lw, lw)
            }
            else {
                select(lw, selectionEnd)
            }
        }
    }

    Component.onCompleted: {
        forceActiveFocus()      // принудительный фокус к объекту после его создания
        cursorPosition = text.length
    }
}
