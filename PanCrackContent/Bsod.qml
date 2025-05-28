import QtQuick 2.15
import PanCrack
import QtQuick.Controls 2.15

Item {
    id: root
    width: Constants.width
    height: Constants.height
    z: 10000
    visible: false

    property int progress: 0
    property bool canClose: false
    property bool inProgress: false // Флаг, что сбор данных в процессе

    Rectangle {
        anchors.fill: parent
        color: "#0078d7"

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

    // Таймер прогресса
    Timer {
        id: progressTimer
        interval: 450//500 // Базовый интервал
        running: root.visible && !inProgress
        repeat: true
        onTriggered: {
            if (progress < 100) {
                inProgress = true;
                // Скачки по 8-18% с небольшими вариациями
                var jump = Math.floor(Math.random() * 11) + 8;
                progress = Math.min(progress + jump, 100);

                // Случайная задержка (300-700мс)
                progressTimer.interval = Math.floor(Math.random() * 400) + 300;

                // 20% chance для небольшой паузы
                if (Math.random() > 0.8) {
                    progressTimer.interval = Math.floor(Math.random() * 500) + 500;
                }
            } else {
                // После 100% ждем 1.5 секунды
                completeDelay.start();
                progressTimer.stop();
            }
            inProgress = false;
        }
    }

    // Задержка перед закрытием после 100%
    Timer {
        id: completeDelay
        interval: 1500
        onTriggered: {
            canClose = true;
            root.visible = false;
            progress = 0; // Сбрасываем только при закрытии
            canClose = false;
            progressTimer.interval = 500;
        }
    }

    // Таймер показа (каждые 20 секунд)
    Timer {
        id: showTimer
        // interval: 60000//20000
        interval: 600000
        running: true
        repeat: true
        onTriggered: {
            if (!root.visible) {
                progress = 0;
                root.visible = true;
                canClose = false;
            }
        }
    }

    MouseArea {
        anchors.fill: parent
        onClicked: {
            if (canClose) {
                root.visible = false;
                progress = 0;
                canClose = false;
            }
        }
    }

    onVisibleChanged: {
        if (!visible) {
            canClose = false;
        }
    }
}
