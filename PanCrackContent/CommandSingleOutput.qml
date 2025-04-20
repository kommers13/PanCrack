import QtQuick
import QtQuick.Controls

TextArea {
    property bool isLineEmpty: false
    id: commandAnswer
    // width: 850
    height: !isLineEmpty ? 0 : font.pointSize * 1.7
    readOnly: true
    wrapMode: TextArea.Wrap
    textFormat: TextArea.MarkdownText
    font.family: "AcPlus IBM EGA 9x14"
    color: "#3ffffc"
    selectionColor: "#4d633d"
    font.pointSize: 25
    // text: "834jdfkslaplaksfd;kasdlkfjlkszjdlfajldskja;lsdjfl;aksdjfaksdjf;lkajsd;flkajs;ldfdsajf;lkajsdflkasd;fkasdj;flkasdfja;lfkdja;lksdj;lajsdlfkjas;dlkfjadjf;lkajsd;lfkjaldkfjalksdjf;lkasdjf;lkajsdlfkajsdlkfja;lsdjfl;aksdfs"
}
