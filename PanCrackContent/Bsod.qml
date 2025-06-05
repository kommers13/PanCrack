import QtQuick 2.15
import PanCrack
import QtQuick.Controls 2.15

Item {
    id: root
    width: Constants.width
    height: Constants.height
    z: 10000
    visible: false

    property int level: 1
    property int progress: 0
    property string currentChallenge: ""
    property string userInput: ""
    property bool challengeComplete: false
    property var currentChallengeObj: null


    // CustomCursor {
    //     anchors.fill: parent
    //     cursorVisible: true
    // }

    // Список заданий
    property var challenges: [
        {cmd: "algorithm -d GRAPH_A A", desc: "Perform DFS starting from vertex A for GRAPH_A", solution: "algorithm -d GRAPH_A A"},
        {cmd: "algorithm -b GRAPH_B B", desc: "Perform BFS starting from vertex B for GRAPH_B", solution: "algorithm -b GRAPH_B B"},
        {cmd: "prufer -c GRAPH_C", desc: "Get Prufer code for GRAPH_C", solution: "prufer -c GRAPH_C"},
        {cmd: "check -e GRAPH_D", desc: "Check if GRAPH_D is Eulerian", solution: "check -e GRAPH_D"},
        {cmd: "view -d GRAPH_E", desc: "Show vertex degrees for GRAPH_E", solution: "view -d GRAPH_E"}
    ]

    // Основной экран смерти
    Rectangle {
        id: bsodScreen
        anchors.fill: parent
        color: "#0078d7"
        visible: true

        Column {
                    anchors {
                        left: parent.left
                        leftMargin: 80
                        right: parent.right
                        rightMargin: 80
                        verticalCenter: parent.verticalCenter
                    }
                    spacing: 20

                    Text {
                        text: ":("
                        color: "white"
                        font.family: "Segoe UI"
                        font.pixelSize: 120
                        font.weight: Font.Light
                    }

                    Text {
                        width: parent.width
                        text: "Your graph system ran into a problem and needs to restart."
                        color: "white"
                        font.family: "Segoe UI"
                        font.pixelSize: 28
                        font.weight: Font.Light
                        wrapMode: Text.WordWrap
                        lineHeight: 1.2
                    }

                    Text {
                        width: parent.width
                        text: "We're just collecting some error info, and then we'll restart for you."
                        color: "white"
                        font.family: "Segoe UI"
                        font.pixelSize: 24
                        font.weight: Font.Light
                        wrapMode: Text.WordWrap
                    }

                    Text {
                        width: parent.width
                        text: progress + "% complete"
                        color: "white"
                        font.family: "Segoe UI"
                        font.pixelSize: 20
                        font.weight: Font.Light
                        bottomPadding: 30
                    }

                    Row {
                        width: parent.width
                        spacing: 40

                        Image {
                            source: "img/qr.png"
                            width: 160
                            height: 160
                            fillMode: Image.PreserveAspectFit
                        }

                        Text {
                            width: parent.width - 200
                            text: "For more information about this issue and possible fixes, visit https://graphsecurity.com/stopcode\n\n" +
                                  "If you call a support person, give them this info:\n" +
                                  "Stop code: GRAPH_CORRUPTION_ERROR\n" +
                                  "Virus signature: 0x" + Math.random().toString(16).substr(2,8).toUpperCase()
                            color: "white"
                            font.family: "Segoe UI"
                            font.pixelSize: 18
                            font.weight: Font.Light
                            wrapMode: Text.WordWrap
                            lineHeight: 1.3
                        }
                    }
                }
            }

    // Антивирусный терминал (изначально скрыт)
    Rectangle {
        id: terminalScreen
        anchors.fill: parent
        color: "#000c0c"
        visible: false

        Rectangle {
            id: terminal
            width: parent.width * 0.8
            height: parent.height * 0.7
            anchors.centerIn: parent
            color: "black"
            border.color: "#00ff00"
            border.width: 2
            opacity: 0.9

            NumberAnimation on opacity {
                id: flickerAnimation
                running: true
                from: 0.85; to: 1.0
                duration: 300 + Math.random() * 700
                loops: Animation.Infinite
                easing.type: Easing.InOutSine
            }

            Column {
                anchors {
                    fill: parent
                    margins: 20
                }
                spacing: 15

                Text {
                    id: challengeText
                    width: parent.width
                    color: "#00ff00"
                    font.family: "Courier New"
                    font.pixelSize: 16
                    wrapMode: Text.WordWrap
                    textFormat: Text.PlainText
                }

                Rectangle {
                    id: glitchLine
                    width: parent.width
                    height: 2
                    color: "#00ff00"
                    opacity: 0.1

                    NumberAnimation on opacity {
                        running: true
                        from: 0.1; to: 0.3
                        duration: 100 + Math.random() * 200
                        loops: Animation.Infinite
                        easing.type: Easing.InOutSine
                    }

                    NumberAnimation on y {
                        running: true
                        from: y; to: y + (Math.random() > 0.5 ? 2 : -2)
                        duration: 200 + Math.random() * 300
                        loops: Animation.Infinite
                    }
                }

                Text {
                    text: "ANTIVIRUS TERMINAL [v2.4.1]"
                    color: "#00ff88"
                    font.family: "Courier New"
                    font.pixelSize: 18
                }

                TextInput {
                    id: inputField
                    width: parent.width
                    color: "#00ff00"
                    font.family: "Courier New"
                    font.pixelSize: 16
                    focus: true
                    cursorVisible: true
                    text: "> " + userInput
                    onTextEdited: {
                        userInput = text.substring(2);
                    }
                    Keys.onReturnPressed: {
                        if (userInput.trim() === currentChallengeObj.solution) {
                            if (level < 3) {
                                level++;
                                progress += 33;
                                resultText.text = "ACCESS GRANTED! MOVING TO LEVEL " + level;
                                resultText.color = "#00ff00";
                                generateChallenge();
                            } else {
                                progress = 100;
                                challengeComplete = true;
                                resultText.text = "FIREWALL BREACHED!\nSYSTEM RECOVERY COMPLETE";
                                resultText.color = "#00ff00";
                                completeDelay.start();
                            }
                        } else {
                            resultText.text = "ACCESS DENIED! TRY AGAIN";
                            resultText.color = "#ff5555";
                            resultTimer.start();
                        }
                        inputField.text = "> ";
                        userInput = "";
                    }
                }

                Text {
                    id: resultText
                    width: parent.width
                    color: "#ff5555"
                    font.family: "Courier New"
                    font.pixelSize: 16
                    wrapMode: Text.Wrap
                    visible: text !== ""
                }

                Text {
                    text: "PROGRESS: " + progress + "%"
                    color: progress < 50 ? "#ff5555" : (progress < 80 ? "#ffff00" : "#00ff00")
                    font.family: "Courier New"
                    font.pixelSize: 16
                    font.bold: true
                }
            }
        }

        // Scanlines overlay
        Repeater {
            model: 60
            Rectangle {
                width: parent.width
                height: 1
                y: index * (parent.height / 60)
                color: "#00ff00"
                opacity: 0.05 + Math.random() * 0.1
            }
        }
    }

    Timer {
        id: showTimer
        interval: 4000//30000
        running: true
        repeat: true
        onTriggered: {
            if (!root.visible) {
                startGame();
            }
        }
    }

    Timer {
        id: bsodTimer
        interval: 3000
        onTriggered: {
            bsodScreen.visible = false;
            terminalScreen.visible = true;
            inputField.forceActiveFocus();
        }
    }

    Timer {
        id: resultTimer
        interval: 2000
        onTriggered: resultText.text = ""
    }

    Timer {
        id: completeDelay
        interval: 3000
        onTriggered: {
            if (challengeComplete) {
                root.visible = false;  // Полностью скрываем компонент
                bsodScreen.visible = false;
                terminalScreen.visible = false;

                // Останавливаем все таймеры, чтобы не было повторных запусков
                showTimer.stop();
                bsodTimer.stop();
                resultTimer.stop();
            }
        }
    }

    function startGame() {
        level = 1;
        progress = 0;
        challengeComplete = false;
        root.visible = true;
        bsodTimer.start();
        generateChallenge();
    }

    function generateChallenge() {
        var idx = Math.floor(Math.random() * challenges.length);
        currentChallengeObj = challenges[idx];
        currentChallenge = currentChallengeObj.cmd.split(" ")[0] + " [args]";
        challengeText.text = "BREACH DETECTED! LEVEL " + level + " FIREWALL\n\n" +
                           "To bypass, execute:\n" +
                           currentChallengeObj.desc + "\n\n" +
                           "Expected command format:\n" + currentChallenge;
        userInput = "";
        inputField.text = "> ";
    }

    MouseArea {
        anchors.fill: parent
        onClicked: inputField.forceActiveFocus()
    }
}
