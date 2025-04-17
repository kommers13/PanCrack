import QtQuick
import QtQuick.Controls


// plugs
// import "plugs"
// real
import signals

Item {
    id: root_commandLine
    width: 850
    height: 920

    Signals {
        id: signals_id
        objectName: "signals_id_"
    }

    Rectangle {
        id: rect_console
        x: 0
        y: 0
        width: parent.width
        height: parent.height
        color: "#020808"
        border.width: 0

        Column {
            id: column
            x: 8
            y: 8
            width: parent.width
            height: parent.height

            CommandSingleLine {
                id: commandSingleLine
                tiwidth: parent.width
                tipointSize: 25
                focus: true
                onAccepted: {
                    // commandAnswer.append("**Command**: create - ...")
                    // commandAnswer.append("**Synopsis**: create [OPTIONS] GRAPH_NAME")
                    // commandAnswer.append("**Description**: ...")
                    readOnly = true
                    cursorDelegate = null

                    signals_id.on_output_command(commandSingleLine.text, commandAnswer)
                }
            }
            TextArea {
                id: commandAnswer
                readOnly: true
                text: ""
                wrapMode: Text.Wrap
                textFormat: Text.MarkdownText
                font.family: "AcPlus IBM EGA 9x14"
                color: "#3ffffc"
                selectionColor: "#4d633d"
                font.pointSize: 25
            }
        }
    }
}
