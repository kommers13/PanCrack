import QtQuick
import QtQuick.Controls


// js
import "js/console_utils.js" as ConsoleUtils
import "js/draw_utils.js" as DrawingUtils

// plugs
// import "plugs"
// real
import signals

Item {
    id: root_commandLine
    width: 850
    height: 920

    Signals {
        property bool isCleared: false;
        property bool isCreated: false;
        id: signals_id
        objectName: "signals_id_"
        // этот компонент зарегистрирован из C++
        // он дает возможность испускать сигналы из C++ и ловить их в этом же классе и обрабатывать,
        // но испускать сигналы из QML мы можем откуда угодно
        // этот компонент еще будет обрабатывать сигналы, испущенные из C++ кодом, который отвечает за команды консоли
        // здесь мы просто вызываем функции, чтобы они сделали свое дело, но не имели никаких понятий о том,
        // что нам пришлось сделать, чтобы вызвать их
        // UNCOMMENT
        onClearCommand: {
            isCleared = true
        }
        onGraphDraw: (graph) => {
            DrawingUtils.draw_graph(graph, canvas_graphdraw)
        }
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
            y: 25
            width: 834
            height: 904
            spacing: 0

            signal submitInput() // подтверждение ввода

            // функция, которая будет вызываться после Accepted у каждого CommandSingleLine
            function commandAccepted(command_line, command_answer) {

                command_line.readOnly = true
                command_line.enabled = false
                command_line.cursorDelegate = null

                command_answer.enabled = false

                // передаем информацию для того, чтобы обработать команду
                // signals_id.on_output_command(command_line.text)

                // если сработало некое условие (строка ввода пустая
                // или в выводе ничего нет), то строка вывода будет нулевой
                // иначе в ней будет какая-то информация
                // (command_line.text.length > 9) - УСЛОВИЕ БУДЕТ ИЗМЕНЕНО

                // МЕСТО ВХОДА ВВОДА ПОЛЬЗОВАТЕЛЯ В C++ КОД
                // UNCOMMENT
                let answer = signals_id.output_command(command_line.text)
                // ДАННАЯ ФУНКЦИЯ ВОЗВРАЩАЕТ ОТВЕТ КОМАНДЫ И ИСПОЛНЯЕТ ТО, ЧТО ПРОСИТ КОМАНДА
                command_answer.text = answer

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
                if (command_ans_real_bottom >= column.height) {
                    // нам нужно поднять на столько, на сколько вылезло за пределы экрана, и плюсом к тому на одну высоту строки
                    column.y -= (command_ans_real_bottom - column.height + 25) // 25 - magic constant is height of one command line
                }

                // UNCOMMENT
                // CLEAR LIMPED FIX
                // это единственное, что можно было придумать, не меняя логики программы с корнем
                if (signals_id.isCleared) {
                    // column_id - id колонны, которую мы очищаем
                    ConsoleUtils.clear(column)
                    signals_id.isCleared = false
                }
                // CLEAR LIMPED FIX END

                // console.log("AFTER COLUMN.Y", column.y)
                column.submitInput()        // создаем следующие элементы после потверждения ввода здесь
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

                    // console.log(nextOutput.height)


                    nextLine.accepted.connect( () => {
                                                  commandAccepted(nextLine,
                                                                  nextOutput)
                                              })
                    nextLine.textChanged.connect( () => {
                                                     // координаты относительно корневого элемента
                                                     let gc = nextLine.mapToItem(root_commandLine, 0, 0)
                                                     let nextLine_real_bottom = gc.y + nextLine.height
                                                     // console.log(gc.y + nextLine.height, height)
                                                     // если реальные координаты по "y" к одиночной строки ввода
                                                     // превышают высоту колонны, то нужно сдвинуть наверх на одну
                                                     // высоту строки, которая равна 25 пикселям (волшебная константа)
                                                     if (nextLine_real_bottom >= column.height) {
                                                         // console.log(commandSingleLine.contentHeight)
                                                         // console.log("FDSJKSLFD")
                                                         // здесь нам нужно поднять только на высоту, которая вылезла за пределы экрана
                                                         column.y -= (nextLine_real_bottom - column.height)
                                                     }
                                                 })
                }
            }
            Keys.onPressed: (event) => {
                if (event.key === Qt.Key_Up) {
                    // когда консоль движется вниз, она движется вверх, и ее координата "y" уменьшается
                    if (column.y + 25 <= 25) {   // magic const 25 - origin y
                        column.y += 25
                    }
                }
                else if (event.key === Qt.Key_Down) {
                    // нужно запретить спускаться ниже крайнего ребенка "column"
                    // крайним ребенком всегда будет CommandSingleLine
                    // console.log("RCB: ", root_commandLine.y + root_commandLine.height)
                    let gc = column.children[children.length - 1].mapToItem(root_commandLine, 0, 0)
                    // console.log("LOWER CHILD BOTTOM: ", gc.y + 25)
                    // console.log("COLUMN Y: ", column.y)
                    // console.log("COLUMN HEIGHT: ", column.height)
                    // console.log("COLUMN BOTTOM: ", column.y + column.height)
                    // console.log("ROOT COMMAND LINE Y: ", root_commandLine.y)
                    // console.log(gc.y > root_commandLine.y + root_commandLine.height)
                    // gc.y > root_commandLine.y + root_commandLine.height
                    if (gc.y > 0 + root_commandLine.height) {
                         column.y -= 25
                     }
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
