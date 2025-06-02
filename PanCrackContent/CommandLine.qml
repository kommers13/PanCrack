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

    // Properties for hacker-style effects
    property bool glitchActive: false
    property bool isInputActive: false
    property int hackProgress: 0
    property string systemStatus: "SYSTEM_READY"
    property string securityLevel: "NORMAL"
    property var commandHistory: []
    property int historyIndex: -1
    property string lastValidCommand: ""
    property real glitchIntensity: 100



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
             // graph - QVariantMap
             DrawingUtils.clean_canvas(canvas_graphdraw, canvas_graphdraw.getContext("2d"), 1);
             DrawingUtils.init_scale(graph, canvas_graphdraw, canvas_graphdraw.getContext("2d"));
             DrawingUtils.draw_graph(graph, canvas_graphdraw, canvas_graphdraw.getContext("2d"));
         }
    }

    Rectangle {
        id: rect_console
        x: 0
        y: 0
        width: parent.width
        height: parent.height
        color: "#000000"

        // Улучшенная рамка с двойной линией
        Rectangle {
            id: outerBorder
            anchors.fill: parent
            color: "transparent"
            border.color: "#00ff00"
            border.width: 2
            radius: 5
        }

        Rectangle {
            id: innerBorder
            anchors.fill: parent
            anchors.margins: 4
            color: "transparent"
            border.color: "#00aa00"
            border.width: 1
            radius: 3
        }

        // Binary code background
        Text {
            id: binaryBackground
            anchors.fill: parent
            anchors.margins: 10
            color: "#00ff00"
            opacity: 0.07
            font.pixelSize: 10
            font.family: "Courier New"
            text: generateBinaryCode()
            wrapMode: Text.Wrap

            function generateBinaryCode() {
                var code = "";
                for (var i = 0; i < 2000; i++) {
                    code += Math.random() > 0.5 ? "1" : "0";
                    if (Math.random() > 0.95) code += ["@", "#", "$", "%", "&", "*"][Math.floor(Math.random()*6)];
                    if (i % 80 === 0) code += "\n";
                }
                return code;
            }

            Timer {
                interval: 100
                running: true
                repeat: true
                onTriggered: parent.text = parent.generateBinaryCode()
            }
        }

        // Scanlines effect with flicker
        Rectangle {
            anchors.fill: parent
            color: "transparent"
            opacity: 0.1

            Repeater {
                model: parent.height / 2
                Rectangle {
                    width: parent.width
                    height: 1
                    y: index * 2
                    color: "#00ff00"
                    opacity: 0.1 + Math.random() * 0.2
                }
            }

            Timer {
                interval: 100
                running: true
                repeat: true
                onTriggered: parent.opacity = 0.05 + Math.random() * 0.1
            }
        }
        // Static effect for glitches
        Rectangle {
            id: staticEffect
            anchors.fill: parent
            visible: glitchActive
            color: "black"
            opacity: 0
            z: 100

            Canvas {
                anchors.fill: parent
                onPaint: {
                    var ctx = getContext("2d");
                    for (var x = 0; x < width; x+=2) {
                        for (var y = 0; y < height; y+=2) {
                            var rnd = Math.random();
                            if (rnd > 0.7) {
                                ctx.fillStyle = rnd > 0.9 ? "#ffffff" : "#00ff00";
                                ctx.fillRect(x, y, 1, 1);
                            }
                        }
                    }
                }
            }

            Timer {
                interval: 50
                running: glitchActive
                repeat: true
                onTriggered: {
                    parent.opacity = Math.random() * 0.3;
                    // parent.requestPaint();
                }
            }
        }

        // Virus warning overlay with glitch effects
        Rectangle {
            id: virusWarningContainer
            anchors.fill: parent
            color: "transparent"
            visible: glitchActive
            z: 101

            property var warnings: [
                ">> Injecting graph virus",
                ">> Breaching vertex firewall",
                ">> Hijacking edge protocol",
                ">> Decrypting path matrix",
                ">> Bypassing node authentication",
                ">> Compiling graph exploit",
                ">> Spoofing adjacency links",
                ">> Scanning for weak vertices",
                ">> Intercepting route traffic",
                ">> Penetrating DAG defenses",
                ">> Uploading traversal worm",
                ">> Overclocking pathfinder AI",
                ">> Vertex override initiated",
                ">> Deploying edge sniffer",
                ">> Cyclomatic breach in progress",
                ">> Establishing control over graph core"
            ]

            Text {
                id: virusWarning
                text: warnings[Math.floor(Math.random() * warnings.length)]
                color: "#ff0000"
                font.pixelSize: 26
                font.family: "Courier New"
                font.bold: true
                horizontalAlignment: Text.AlignHCenter
                opacity: 0.7
                property real shakeX: 0
                property real shakeY: 0
                transform: Translate { x: virusWarning.shakeX; y: virusWarning.shakeY }

                function randomPosition() {
                    x = Math.random() * (parent.width - width)
                    y = Math.random() * (parent.height - height)
                }

                Component.onCompleted: randomPosition()
            }

            onVisibleChanged: {
                if (visible) {
                    virusWarning.text = warnings[Math.floor(Math.random() * warnings.length)]
                    virusWarning.randomPosition()
                }
            }
        }

        // Random glitch effect trigger - теперь срабатывает каждые 3 секунды
        Timer {
            interval: 7000
            running: true
            repeat: true
            onTriggered: {
                glitchActive = true;
                glitchTimer.start();
                virusGlitchTimer.start();
            }
        }

        Timer {
            id: glitchTimer
            interval: 1000
            running: false
            repeat: false
            onTriggered: glitchActive = false
        }

        // Glitch effect timer
        Timer {
            id: virusGlitchTimer
            interval: 20
            running: glitchActive
            repeat: true
            onTriggered: {
                if (virusWarning) {
                    virusWarning.shakeX = (Math.random() * 12 - 6) * (glitchIntensity / 100);
                    virusWarning.shakeY = (Math.random() * 8 - 4) * (glitchIntensity / 100);

                    if (Math.random() > 0.2) {
                        var colors = ["#00ff00", "#ff0000", "#0000ff", "#00ff77", "#ff00ff", "#ffff00"];
                        virusWarning.color = colors[Math.floor(Math.random() * colors.length)];
                    }
                }
            }
        }

        WheelHandler {
            onWheel: (event) => {
                if (event.angleDelta.y > 0) {
                    if (column.y + 25 <= 25) {
                        column.y += 25
                    }
                }
                else if (event.angleDelta.y < 0) {
                    let gc = column.children[column.children.length - 1].mapToItem(root_commandLine, 0, 0)
                    if (gc.y > 0 + root_commandLine.height) {
                        column.y -= 25
                    }
                }
            }
        }

        Column {
            id: column
            x: 15
            y: 25
            width: parent.width - 30
            height: parent.height - 50
            spacing: 5

            signal submitInput()

            function commandAccepted(command_line, command_answer) {
                command_line.readOnly = true
                command_line.enabled = false
                command_line.cursorDelegate = null
                command_answer.enabled = false

                var cmd = command_line.text.replace(/^PanCrack>\s*/g, "").trim();
                if (cmd.length > 0) {
                    commandHistory.push(cmd);
                    historyIndex = -1;
                    hackProgress = commandHistory.length;
                }

                // МЕСТО ВХОДА ВВОДА ПОЛЬЗОВАТЕЛЯ В C++ КОД
                // UNCOMMENT
                let answer = signals_id.output_command(command_line.text);
                // let answer = "Command executed" // Placeholder - replace with: signals_id.output_command(command_line.text)
                command_answer.text = answer

                let gca = command_answer.mapToItem(root_commandLine, 0, 0)
                let command_ans_real_bottom = gca.y + command_answer.height
                if (command_ans_real_bottom >= column.height) {
                    column.y -= (command_ans_real_bottom - column.height + 25)
                }
                // UNCOMMENT
                // CLEAR LIMPED FIX
                if (signals_id.isCleared) {
                    ConsoleUtils.clear(column);
                    signals_id.isCleared = false;
                }
                // CLEAR LIMPED FIX END


                column.submitInput();
            }

            onSubmitInput: {
                let nextOutputComponent = Qt.createComponent("CommandSingleOutput.qml")
                let nextLineComponent = Qt.createComponent("CommandSingleLine.qml")

                if (nextLineComponent.status === Component.Ready &&
                    nextOutputComponent.status === Component.Ready) {

                    let nextLine = nextLineComponent.createObject(column, {
                        focus: true,
                        width: column.width,
                        text: "PanCrack>"
                    })

                    let nextOutput = nextOutputComponent.createObject(column, {
                        width: column.width,
                    })

                    nextLine.accepted.connect(() => {
                        commandAccepted(nextLine, nextOutput)
                    })

                    nextLine.Keys.onUpPressed.connect(() => {
                        if (historyIndex < commandHistory.length - 1) {
                            historyIndex++;
                            nextLine.text = "PanCrack>" + commandHistory[commandHistory.length - 1 - historyIndex];
                        }
                        nextLine.cursorPosition = nextLine.text.length
                    })

                    nextLine.Keys.onDownPressed.connect(() => {
                        if (historyIndex > 0) {
                            historyIndex--;
                            nextLine.text = "PanCrack>" + commandHistory[commandHistory.length - 1 - historyIndex];
                        } else {
                            historyIndex = -1;
                            nextLine.text = "PanCrack>";
                        }
                        nextLine.cursorPosition = nextLine.text.length
                    })

                    nextLine.Keys.onPressed.connect((event) => {
                        if (event.key === Qt.Key_Shift && event.key === Qt.Key_Return) {
                            nextLine.text += "\nPanCrack>";
                        }
                    })

                    nextLine.textChanged.connect(() => {
                        let gc = nextLine.mapToItem(root_commandLine, 0, 0)
                        let nextLine_real_bottom = gc.y + nextLine.height
                        if (nextLine_real_bottom >= column.height) {
                            column.y -= (nextLine_real_bottom - column.height)
                        }
                    })
                }
            }

            CommandSingleLine {
                id: commandSingleLine
                width: parent.width
                text:
                    "______                _____                     _\n" +
                    "| ___ \\              /  __ \\                   | |\n" +
                    "| |_/ /  __ _  _ __  | /  \\/ _ __   __ _   ___ | | __\n" +
                    "|  __/  / _` || '_ \\ | |    | '__| / _` | / __|| |/ /\n" +
                    "| |    | (_| || | | || \\__/\\| |   | (_| || (__ |   <\n" +
                    "\\_|     \\__,_||_| |_| \\____/|_|    \\__,_| \\___||_|\\_\\\n" +
                    "\nWARNING: SYSTEM LOCKED\n" +
                    "SOLVE 12 GRAPH PROBLEMS TO UNLOCK\n" +
                    "Type 'help' for available commands\n" +
                    "Press ENTER to begin..."
                readOnly: true
                color: "#00ff00"
                font.pixelSize: 16
                font.family: "Courier New"

                onAccepted: {
                    systemStatus = "AWAITING_INPUT";
                    column.submitInput()
                }
            }
        }

        // Enhanced status bar
        Rectangle {
            id: statusBar
            anchors.bottom: parent.bottom
            width: parent.width
            height: 25
            color: "#001100"
            border.color: "#00aa00"
            border.width: 1
            opacity: 0

            NumberAnimation on opacity {
                from: 0
                to: 1
                duration: 1000
                running: true
            }

            Row {
                id: statusRow
                anchors.fill: parent
                anchors.leftMargin: 10
                anchors.rightMargin: 10
                spacing: 20
                opacity: 0

                NumberAnimation on opacity {
                    from: 0
                    to: 1
                    duration: 1000
                    running: true
                }

                Text {
                    width: parent.width * 0.4
                    anchors.verticalCenter: parent.verticalCenter
                    text: "STATUS: " + systemStatus
                    color: "#00ff00"
                    font.pixelSize: 14
                    font.family: "Courier New"
                }

                Text {
                    width: parent.width * 0.3
                    anchors.verticalCenter: parent.verticalCenter
                    text: "SECURITY: " + securityLevel
                    color: securityLevel === "NORMAL" ? "#00ff00" : "#ff0000"
                    font.pixelSize: 14
                    font.family: "Courier New"
                }

                Text {
                    width: parent.width * 0.2
                    anchors.verticalCenter: parent.verticalCenter
                    text: "COMMANDS: " + hackProgress
                    color: "#00ff00"
                    font.pixelSize: 14
                    font.family: "Courier New"
                }
            }

            Text {
                id: timeText
                text: Qt.formatTime(new Date(), "hh:mm:ss")
                anchors.right: parent.right
                anchors.rightMargin: 10
                anchors.verticalCenter: parent.verticalCenter
                color: "#00ff00"
                font.pixelSize: 14
                font.family: "Courier New"
                opacity: 0

                NumberAnimation on opacity {
                    from: 0
                    to: 1
                    duration: 1000
                    running: true
                }

                Timer {
                    interval: 1000
                    running: true
                    repeat: true
                    onTriggered: {
                        var d = new Date();
                        timeText.text = ("0" + d.getHours()).slice(-2) + ":" +
                                       ("0" + d.getMinutes()).slice(-2) + ":" +
                                       ("0" + d.getSeconds()).slice(-2);
                    }
                }
            }
        }
    }

    // Startup animation with flicker effect
    Component.onCompleted: {
        rect_console.opacity = 0;
        startupAnimation.start();
    }

    SequentialAnimation {
        id: startupAnimation
        ParallelAnimation {
            NumberAnimation {
                target: rect_console;
                property: "opacity";
                to: 1;
                duration: 1000
            }
            SequentialAnimation {
                NumberAnimation {
                    target: rect_console
                    property: "scale"
                    from: 0.95
                    to: 1.05
                    duration: 500
                }
                NumberAnimation {
                    target: rect_console
                    property: "scale"
                    from: 1.05
                    to: 1.0
                    duration: 500
                }
            }
        }
    }
}
