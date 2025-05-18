import QtQuick 2.15
import QtQuick.Controls 2.15
// import QtQuick.Window 2.15

Window {
    id: duplicateWindow
    width: 420
    height: 220
    visible: true
    color: "#00000000"
    title: "PanCrack Clone"
    flags: Qt.Window | Qt.FramelessWindowHint

    property real originalX: 0
    property real originalY: 0
    property int windowShake: 0
    property bool contentsLocked: true
    property bool positionLocked: false
    property bool aggressiveMode: false
    property real progressValue: 0
    property bool showContent: false
    property bool isMainWindow: false
    property int aggressionLevel: 1

    // Дополнительные свойства
    property bool showBackground: false
    property bool matrixVisible: false
    property bool glitchActive: false

    Rectangle {
        id: mainRect
        anchors.fill: parent
        radius: 12
        color: showBackground ? "#000000" : "transparent"
        border.color: progressValue >= 1.0 ? "#ff0000" : "#00ff00"
        border.width: 2
        clip: true

        Rectangle {
            visible: !showContent
            anchors.fill: parent
            anchors.margins: 10
            color: "transparent"
            border.color: "#3300ff00"
            border.width: 1
            radius: 6
            opacity: 0.7
        }

        Loader {
            anchors.fill: parent
            active: showContent
            sourceComponent: showContent ? contentComponent : undefined
        }
    }

    Component {
        id: contentComponent
        Item {
            anchors.fill: parent
            anchors.margins: 10

            // Заголовок и версия с глитч-эффектами
            Text {
                id: mainTitle
                text: "PanCrack"
                font.pixelSize: 20
                color: "#00ff00"
                font.bold: true
                font.family: "Courier New"
                style: Text.Outline
                styleColor: "#002200"
                property real shakeX: 0
                property real shakeY: 0
                x: 20 + shakeX
                y: 15 + shakeY
            }

            Text {
                id: versionText
                text: "v2.4.1"
                font.pixelSize: 14
                color: "#00ff00"
                font.family: "Courier New"
                style: Text.Outline
                styleColor: "#002200"
                property real shakeX: 0
                property real shakeY: 0
                x: 20 + shakeX
                y: 40 + shakeY
            }

            // Сканирующая линия
            Rectangle {
                width: parent.width - 4
                height: 1
                color: "#00ff00"
                opacity: 0.3
                x: 2
                y: 0
                NumberAnimation on y {
                    from: 0
                    to: parent.height
                    duration: 1500
                    loops: Animation.Infinite
                }
            }

            // Matrix эффект
            Repeater {
                model: matrixVisible ? 30 : 0
                delegate: Text {
                    x: calculateColumnPosition(index)
                    y: -20 - Math.random() * 100
                    width: 20
                    height: parent.height + 40
                    text: generateMatrixColumn()
                    color: "#00ff00"
                    opacity: 0.3 + Math.random() * 0.2
                    font.pixelSize: 12
                    font.family: "Courier New"
                    style: Text.Outline
                    styleColor: "#000000"

                    property int speed: 50 + Math.random() * 150
                    property int columnLength: 10 + Math.random() * 15
                    property string chars: "01アイウエオカキクケコサシスセソタチツテトABCDEFGHIJKLMNOPQRSTUVWXYZ"

                    function calculateColumnPosition(idx) {
                        var columns = 30;
                        var spacing = parent.width / columns;
                        return idx * spacing + (Math.random() * spacing * 0.5);
                    }

                    function generateMatrixColumn() {
                        var result = "";
                        for (var i = 0; i < columnLength; i++) {
                            result += chars.charAt(Math.floor(Math.random() * chars.length)) + "\n";
                        }
                        return result;
                    }

                    Timer {
                        interval: parent.speed
                        running: true
                        repeat: true
                        onTriggered: {
                            parent.y += 5;
                            if (parent.y > parent.parent.height) {
                                parent.y = -parent.height - Math.random() * 50;
                                parent.text = parent.generateMatrixColumn();
                            }
                        }
                    }
                }
            }

            // Упрощённый прогресс-бар
            Rectangle {
                x: 20
                y: 140
                width: parent.width - 40
                height: 24
                color: "transparent"
                border.color: progressValue >= 1.0 ? "transparent" : "#00aa00"
                border.width: 2
                radius: 3

                Rectangle {
                    width: (parent.width - 4) * progressValue
                    height: parent.height - 4
                    anchors.left: parent.left
                    anchors.leftMargin: 2
                    anchors.verticalCenter: parent.verticalCenter
                    color: progressValue >= 1.0 ? "#ff0000" : "#00ff77"
                    radius: 2
                }

                Text {
                    anchors.centerIn: parent
                    text: Math.round(progressValue * 100) + "%"
                    font.pixelSize: 16
                    color: progressValue >= 1.0 ? "#ff0000" : "#ffffff"
                    font.bold: true
                    style: Text.Outline
                    styleColor: "#000000"
                }
            }

            // Глитч-эффект
            Timer {
                id: glitchTimer
                interval: 20
                running: glitchActive
                repeat: true
                onTriggered: {
                    mainTitle.shakeX = (Math.random() * 12 - 6)
                    mainTitle.shakeY = (Math.random() * 8 - 4)
                    versionText.shakeX = (Math.random() * 8 - 4)
                    versionText.shakeY = (Math.random() * 6 - 3)
                }
            }
        }
    }

    // Перемещение окна
    Timer {
        id: moveTimer
        interval: aggressiveMode ? 30 : 100
        running: true
        repeat: true
        onTriggered: {
            if (!positionLocked) {
                var moveX = (Math.random() * 40 - 20) * aggressionLevel;
                var moveY = (Math.random() * 30 - 15) * aggressionLevel;

                if (aggressiveMode && Math.random() > 0.7) {
                    moveX *= 3;
                    moveY *= 3;
                }

                // Ограничиваем перемещение границами экрана
                var newX = x + moveX;
                var newY = y + moveY;

                newX = Math.max(0, Math.min(Screen.width - width, newX));
                newY = Math.max(0, Math.min(Screen.height - height, newY));

                x = newX;
                y = newY;
            }
        }
    }

    // Мерцание окна
    Timer {
        id: flickerTimer
        interval: 100 + Math.random() * 200
        running: aggressiveMode
        repeat: true
        onTriggered: {
            visible = !visible
            interval = 50 + Math.random() * 200
        }
    }

    // Изменение размера окна
    Timer {
        id: resizeTimer
        interval: 800 + Math.random() * 1500//interval: 1000 + Math.random() * 2000
        running: aggressiveMode
        repeat: true
        onTriggered: {
            width = 420 + (Math.random() * 80 - 40)
            height = 220 + (Math.random() * 60 - 30)
        }
    }

    // Автоматическое уничтожение
    Timer {
        id: destroyTimer
        interval: 5000 + Math.random() * 5000
        running: true
        onTriggered: {
            destroy()
        }
    }

    Component.onCompleted: {
        x = originalX + (Math.random() * 100 - 50)
        y = originalY + (Math.random() * 80 - 40)

        if (progressValue >= 1.0) {
            aggressiveMode = true
            showContent = true
            glitchActive = true
            matrixVisible = true
            showBackground = true
            flickerTimer.start()
            resizeTimer.start()
        } else if (progressValue >= 0.7) {
            showContent = false
            matrixVisible = true
        }
    }
}
