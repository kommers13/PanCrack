import QtQuick 2.15
import PanCrack
import QtQuick.Controls 2.15

// Антивирусный терминал (изначально скрыт)
Rectangle {
    id: terminalScreen
    anchors.fill: parent
    color: "#000c0c"
    visible: false

    property bool shouldRestartBsod: false
    property int level: 1
    property int progress: 0
    property bool challengeComplete: false
    property string userInput: ""
    property var currentChallengeObj: ({})
    property string currentChallenge: ""

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

    Timer {
        id: completeDelay
        interval: 3000
        onTriggered: {
            if (challengeComplete) {
                root.visible = false; // Полностью скрываем весь компонент
                bsodScreen.visible = false;
                terminalScreen.visible = false;
                // Убираем вызов startGame(), если не нужно начинать заново
            }
        }
    }

    Timer {
        id: resultTimer
        interval: 2000
        onTriggered: resultText.text = ""
    }

    function startGame() {
        level = 1;
        progress = 0;
        challengeComplete = false;
        terminalScreen.visible = true;
        generateChallenge();
        inputField.forceActiveFocus();
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

    Connections {
        target: bsod
        function onTerminalRequested() {
            terminalScreen.visible = true;
            startGame();
        }
    }

    MouseArea {
        anchors.fill: parent
        onClicked: inputField.forceActiveFocus()
    }
}
