import QtQuick
import QtQuick.Controls


// plugs
import "plugs"
// real
// import signals

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

            signal submitInput() // подтверждение ввода

            function commandAccepted(command_line, command_answer) {
                // функция, которая будет вызываться после Accepted у каждого CommandSingleLine

                command_line.readOnly = true
                command_line.cursorDelegate = null

                // передаем информацию для того, чтобы обработать команду
                // signals_id.on_output_command(command_line.text, command_answer)

                // если сработало некое условие (строка ввода пустая
                // или в выводе ничего нет), то строка вывода будет нулевой
                // иначе в ней будет какая-то информация
                // (command_line.text.length > 9) - УСЛОВИЕ БУДЕТ ИЗМЕНЕНО
                command_answer.isLineEmpty = (command_line.text.length > 9)

                column.submitInput()

            }

            onSubmitInput: {

                let nextLineComponent = Qt.createComponent("CommandSingleLine.qml")
                let nextOutputComponent = Qt.createComponent("CommandSingleOutput.qml")
                if (nextLineComponent.status === Component.Ready) {

                    let nextLine = nextLineComponent.createObject(column, {
                                                                      focus: true,
                                                                      tiwidth: column.width,
                                                                      tipointSize: 25
                                                                  })

                    let nextOutput = nextOutputComponent.createObject(column, {})

                    nextLine.accepted.connect( () => {
                                                  commandAccepted(nextLine,
                                                                  nextOutput)
                                              })
                }
            }

            CommandSingleLine {
                id: commandSingleLine
                tiwidth: parent.width
                tipointSize: 25
                focus: true
                onAccepted: {
                    // функция, которая будет вызываться после Accepted у каждого CommandSingleLine

                    commandSingleLine.readOnly = true
                    commandSingleLine.cursorDelegate = null

                    // передаем информацию для того, чтобы обработать команду
                    // signals_id.on_output_command(commandSingleLine.text, commandOutput)

                    // если сработало некое условие (строка ввода пустая
                    // или в выводе ничего нет), то строка вывода будет нулевой
                    // иначе в ней будет какая-то информация
                    commandOutput.isLineEmpty = (commandSingleLine.text.length > 9)

                    column.submitInput()
                }
            }
            CommandSingleOutput {
                id: commandOutput
            }
        }
    }




}
