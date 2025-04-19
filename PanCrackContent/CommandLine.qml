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
            width: 834
            height: 904

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

                // column.childrenRect - возвращает кортеж (x, y, width, height),
                // где x, y - это точка верхнего левого угла прямоугольника дочерних элементов
                // width, height - ширина и высота соответственно
                console.log(column.childrenRect.y, column.y)
                if (column.childrenRect.height >= height - 29) {
                    column.y -= 29

                }

                column.submitInput()

            }

            onSubmitInput: {

                // создание новой одиночной строки ввода и вывода
                // (CommandSingleLine и CommandSingleOutput)
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
                    nextLine.textChanged.connect( () => {
                        // координаты относительно корневого элемента
                        let gc = nextLine.mapToItem(root_commandLine, 0, 0)
                        console.log(gc.y + nextLine.height, height)
                        // если реальные координаты по "y" к одиночной строки ввода
                        // превышают высоту колонны, то нужно сдвинуть наверх на одну
                        // высоту строки, которая равна 29 пикселям (волшебная константа)
                        if (gc.y + nextLine.height - 29 >= height) {
                            console.log("FDSJKSLFD")
                            column.y -= 29
                        }
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
