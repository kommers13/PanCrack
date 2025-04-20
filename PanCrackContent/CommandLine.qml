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
        // color: "#bb1993"
        border.width: 0

        Column {
            id: column
            x: 8
            y: 8
            width: 834
            height: 904
            spacing: 0

            signal submitInput() // подтверждение ввода

            // функция, которая будет вызываться после Accepted у каждого CommandSingleLine
            function commandAccepted(command_line, command_answer) {

                command_line.readOnly = true
                command_line.cursorDelegate = null

                // передаем информацию для того, чтобы обработать команду
                // signals_id.on_output_command(command_line.text, command_answer)

                // БАЛУЕМСЯ
                if (command_line.text === "PanCrack>clear") {
                    console.log("COMMAND CLEAR")
                    for (let i = column.children.length - 1; i >= 1; i--) {
                        if (column.children[i] !== column) {
                            column.children[i].destroy()
                        }
                    }
                }
                // ЗАКОНЧИЛИ БАЛОВАТЬСЯ
                // если сработало некое условие (строка ввода пустая
                // или в выводе ничего нет), то строка вывода будет нулевой
                // иначе в ней будет какая-то информация
                // (command_line.text.length > 9) - УСЛОВИЕ БУДЕТ ИЗМЕНЕНО
                command_answer.isLineEmpty = (command_line.text.length > 9)

                // column.childrenRect - возвращает кортеж (x, y, width, height),
                // где x, y - это точка верхнего левого угла прямоугольника дочерних элементов
                // width, height - ширина и высота соответственно
                // узнаем координаты относительно корневого элемента
                // только что добавившихся элементов строки ввода и строки вывода
                let gca = command_answer.mapToItem(root_commandLine, 0, 0)  // global coordinates answer
                let command_ans_real_bottom = gca.y + command_answer.height // реальные координаты низа ответа
                // console.log("HEIGHT: ", command_line.height)
                // console.log("gci.y + command_line.height = command_line.bottom", gci.y + command_line.height)
                // console.log("<gca.y> + command_answer.height = command_answer.bottom", gca.y + command_answer.height)
                // console.log("DIFFERENCE: ", command_ans_real_bottom, height, command_ans_real_bottom - height)
                if (command_ans_real_bottom >= height) {
                    column.y -= (command_ans_real_bottom - height + 25) // 25 - magic constant is height of one command line
                }

                column.submitInput()

            }

            onSubmitInput: {

                // создание новой одиночной строки ввода и вывода
                // (CommandSingleLine и CommandSingleOutput)
                let nextOutputComponent = Qt.createComponent("CommandSingleOutput.qml")
                let nextLineComponent = Qt.createComponent("CommandSingleLine.qml")

                if (nextLineComponent.status === Component.Ready &&
                    nextOutputComponent.status === Component.Ready) {

                    let nextLine = nextLineComponent.createObject(column, {
                                                                      focus: true,
                                                                      width: column.width,
                                                                  })

                    let nextOutput = nextOutputComponent.createObject(column, {
                                                                      width: column.width,
                                                                      })




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
                                                     // высоту строки, которая равна 25 пикселям (волшебная константа)
                                                     if (gc.y + nextLine.height - 25 >= column.height) {
                                                         console.log(commandSingleLine.contentHeight)
                                                         console.log("FDSJKSLFD")
                                                         column.y -= 25
                                                     }
                                                 })
                }
            }

            CommandSingleLine {
                id: commandSingleLine
                width: parent.width
                text: "PanCrack [Version 0.0.6]\n(c) Some of students who has passion for programming and mathematics.\nAll rights reserved.\n\nGood time of the days! I am PanCrack. I am the virus dedicated to spread out the knowledge about Discrete Math. So, you wanted to download complete answers for upcoming test, but you got the virus that will destroy your computer unless you solve all my tasks concerned to discrete math, especially graphs. I wish you would solve all of it and prove that you are real programmer, but not an ordinary. Break a leg!\n\nClick Enter to start off\n"
                readOnly: true
                onAccepted: {
                    column.submitInput()
                }
            }
        }
    }
}
