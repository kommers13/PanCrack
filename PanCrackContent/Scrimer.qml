// Scrimer.qml
import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    id: root
    width: 300
    height: 300
    z: 1000
    visible: false

    property int minDuration: 60 // 2 секунды минимальная длительность
    property int maxDuration: 100 // 4 секунды максимальная длительность
    property int spawnInterval: 25000 // Интервал 20 секунд

    Image {
        id: scrimerImage
        anchors.fill: parent
        source: "img/panteleev.jpg"
        opacity: 0
    }

    // Таймер для начальной задержки
    Timer {
        id: initialDelayTimer
        interval: 40000 // 20 секунд задержки
        running: true
        onTriggered: {
            spawnTimer.start() // Запускаем основной таймер после задержки
        }
    }

    Timer {
        id: spawnTimer
        interval: spawnInterval
        running: false // Не запускаем сразу, ждем initialDelayTimer
        repeat: true
        onTriggered: {
            startScrimer();
        }
    }

    // Остальной код без изменений
    function startScrimer() {
        // Выбираем случайную стартовую позицию за пределами экрана
        var startX, startY;
        var side = Math.floor(Math.random() * 4); // 0-3: top, right, bottom, left

        switch(side) {
            case 0: // top
                startX = Math.random() * root.parent.width;
                startY = -root.height;
                break;
            case 1: // right
                startX = root.parent.width;
                startY = Math.random() * root.parent.height;
                break;
            case 2: // bottom
                startX = Math.random() * root.parent.width;
                startY = root.parent.height;
                break;
            case 3: // left
                startX = -root.width;
                startY = Math.random() * root.parent.height;
                break;
        }

        // Выбираем случайную конечную позицию (противоположная сторона)
        var endX, endY;
        switch((side + 2) % 4) { // Противоположная сторона
            case 0: // top
                endX = Math.random() * root.parent.width;
                endY = -root.height;
                break;
            case 1: // right
                endX = root.parent.width;
                endY = Math.random() * root.parent.height;
                break;
            case 2: // bottom
                endX = Math.random() * root.parent.width;
                endY = root.parent.height;
                break;
            case 3: // left
                endX = -root.width;
                endY = Math.random() * root.parent.height;
                break;
        }

        // Устанавливаем позицию и делаем видимым
        root.x = startX;
        root.y = startY;
        root.visible = true;
        scrimerImage.opacity = 1.0;

        // Длительность анимации
        var duration = root.minDuration + Math.random() * (root.maxDuration - root.minDuration);

        // Анимация движения
        movementAnim.stop();
        movementAnim.duration = duration;
        movementAnim.start();
    }

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
        onStopped: {
            root.visible = false;
        }
    }
}
