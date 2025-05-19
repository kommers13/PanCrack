// Scrimer.qml
import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    id: root
    width: 400
    height: 400
    z: 10000
    visible: false

    property int minDuration: 60
    property int maxDuration: 100
    property int spawnInterval: 25000

    // Чёрный полупрозрачный фон
    Rectangle {
        id: background
        anchors.fill: parent
        color: "black"
        opacity: 0.7
    }

    // Основное изображение скримера
    Image {
        id: scrimerImage
        anchors.centerIn: parent
        width: parent.width * 0.9
        height: parent.height * 0.9
        source: "img/panteleev.jpg" // ПРОВЕРЬТЕ ПУТЬ К ФАЙЛУ!
        opacity: 0
        visible: opacity > 0

        // Эффект мерцания
        SequentialAnimation on opacity {
            id: flickerAnim
            running: false
            loops: Animation.Infinite
            NumberAnimation { to: 0.8; duration: 50 }
            NumberAnimation { to: 1.0; duration: 100 }
            NumberAnimation { to: 0.3; duration: 30 }
            NumberAnimation { to: 1.0; duration: 200 }
        }

        // Эффект дрожания
        ParallelAnimation {
            id: shakeAnim
            running: false
            loops: Animation.Infinite
            NumberAnimation {
                target: scrimerImage
                property: "rotation"
                from: -5; to: 5
                duration: 100
                easing.type: Easing.InOutBack
            }
            NumberAnimation {
                target: scrimerImage
                property: "x"
                from: scrimerImage.x - 10; to: scrimerImage.x + 10
                duration: 70
            }
        }
    }

    // Таймер начальной задержки
    Timer {
        id: initialDelayTimer
        interval: 40000
        running: true
        onTriggered: spawnTimer.start()
    }

    // Основной таймер появления
    Timer {
        id: spawnTimer
        interval: spawnInterval
        running: false
        repeat: true
        onTriggered: startScrimer()
    }

    function startScrimer() {
        // Случайная стартовая позиция
        var startX, startY;
        var side = Math.floor(Math.random() * 4);

        switch(side) {
            case 0: startX = Math.random() * root.parent.width; startY = -root.height; break;
            case 1: startX = root.parent.width; startY = Math.random() * root.parent.height; break;
            case 2: startX = Math.random() * root.parent.width; startY = root.parent.height; break;
            case 3: startX = -root.width; startY = Math.random() * root.parent.height; break;
        }

        // Случайная конечная позиция
        var endX, endY;
        switch((side + 2) % 4) {
            case 0: endX = Math.random() * root.parent.width; endY = -root.height; break;
            case 1: endX = root.parent.width; endY = Math.random() * root.parent.height; break;
            case 2: endX = Math.random() * root.parent.width; endY = root.parent.height; break;
            case 3: endX = -root.width; endY = Math.random() * root.parent.height; break;
        }

        // Установка позиции
        root.x = startX;
        root.y = startY;
        root.visible = true;
        scrimerImage.opacity = 1.0;
        flickerAnim.start();
        shakeAnim.start();

        // Длительность анимации
        var duration = root.minDuration + Math.random() * (root.maxDuration - root.minDuration);

        // Анимация движения
        movementAnim.stop();
        movementAnim.duration = duration;
        movementAnim.start();
    }

    // Анимация движения
    ParallelAnimation {
        id: movementAnim
        property real duration: 3000

        NumberAnimation {
            target: root
            property: "x"
            duration: movementAnim.duration
            easing.type: Easing.InOutQuad
        }
        NumberAnimation {
            target: root
            property: "y"
            duration: movementAnim.duration
            easing.type: Easing.InOutQuad
        }
        SequentialAnimation {
            NumberAnimation {
                target: scrimerImage
                property: "scale"
                from: 0.8
                to: 1.2
                duration: movementAnim.duration/2
                easing.type: Easing.InOutBack
            }
            NumberAnimation {
                target: scrimerImage
                property: "scale"
                from: 1.2
                to: 0.8
                duration: movementAnim.duration/2
                easing.type: Easing.InOutBack
            }
        }
        onStopped: {
            root.visible = false;
            scrimerImage.scale = 1.0;
            flickerAnim.stop();
            shakeAnim.stop();
        }
    }
}
