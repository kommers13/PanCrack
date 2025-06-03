import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    id: root
    anchors.fill: parent
    visible: cursorVisible

    // Настройки
    property bool cursorVisible: true
    property color cursorColor: "#00ff00"
    property bool isPressed: false
    property real cursorScale: 1.0

    // Основной курсор
    Item {
        id: cursorCross
        width: 24
        height: 24
        transform: Scale { origin.x: cursorCross.width/2; origin.y: cursorCross.height/2; xScale: cursorScale; yScale: cursorScale }

        Rectangle {
            id: crossPart1
            width: parent.width
            height: 3
            color: cursorColor
            rotation: 45
            opacity: 0.9
            antialiasing: true
            anchors.centerIn: parent

            Rectangle {
                width: parent.width
                height: parent.height
                color: parent.color
                rotation: 90
                anchors.centerIn: parent
            }
        }

        // Точки в углах
        Repeater {
            model: 4
            Rectangle {
                width: 4
                height: 4
                radius: 2
                color: cursorColor
                x: index % 2 === 0 ? 0 : cursorCross.width - width
                y: index < 2 ? 0 : cursorCross.height - height
                opacity: 0.7
            }
        }
    }

    // Эффект нажатия (кольца)
    Repeater {
        id: clickRings
        model: 2
        Rectangle {
            id: ring
            property real ringScale: 1
            width: 20 + index*20
            height: 20 + index*20
            radius: width/2
            color: "transparent"
            border.color: cursorColor
            border.width: 2
            visible: false
            opacity: 0.8 - index*0.3
            x: cursorCross.x + cursorCross.width/2 - width/2
            y: cursorCross.y + cursorCross.height/2 - height/2
            transform: Scale { origin.x: width/2; origin.y: height/2; xScale: ringScale; yScale: ringScale }
        }
    }

    // Эффект частиц
    Repeater {
        id: particles
        model: 10
        Rectangle {
            property real life: 0
            width: 2 + Math.random()*3
            height: width
            radius: width/2
            color: Qt.rgba(0, 1, 0, 0.7)
            visible: life > 0
            x: cursorCross.x + cursorCross.width/2 - width/2 + (Math.random()-0.5)*20
            y: cursorCross.y + cursorCross.height/2 - height/2 + (Math.random()-0.5)*20
            opacity: life
        }
    }

    // MouseArea для управления курсором
    MouseArea {
        id: mouseArea
        anchors.fill: parent
        hoverEnabled: true
        cursorShape: Qt.BlankCursor
        acceptedButtons: Qt.LeftButton | Qt.RightButton
        propagateComposedEvents: true

        onPositionChanged: (mouse) => {
            cursorCross.x = mouse.x - cursorCross.width/2
            cursorCross.y = mouse.y - cursorCross.height/2

        //     if (isPressed) {
        //         // Обновляем позицию всех активных частиц
        //         for (var i = 0; i < particles.count; i++) {
        //             var particle = particles.itemAt(i)
        //             if (particle.life > 0) {
        //                 particle.x = mouse.x - particle.width/2 + (Math.random()-0.5)*10
        //                 particle.y = mouse.y - particle.height/2 + (Math.random()-0.5)*10
        //             }
        //         }

        //         // Создаём новые частицы
        //         for (var j = 0; j < 2; j++) {
        //             var newParticle = particles.itemAt(Math.floor(Math.random()*particles.count))
        //             if (newParticle) {
        //                 newParticle.life = 1.0
        //                 newParticle.x = mouse.x - newParticle.width/2 + (Math.random()-0.5)*10
        //                 newParticle.y = mouse.y - newParticle.height/2 + (Math.random()-0.5)*10
        //                 particleLifeAnim.target = newParticle
        //                 particleLifeAnim.start()
        //             }
        //         }
        //     }
         }

        onPressed: (mouse) => {
            if (mouse.button === Qt.LeftButton) {
                isPressed = true
                cursorScale = 0.8
                showClickEffect()
                mouse.accepted = true // Передаём событие дальше
            }
        }

        onReleased: (mouse) => {
            if (mouse.button === Qt.LeftButton) {
                isPressed = false
                cursorScale = 1.0
                mouse.accepted = true // Передаём событие дальше
            }
        }
    }

    // Анимация частиц
    NumberAnimation {
        id: particleLifeAnim
        property: "life"
        to: 0
        duration: 500
    }

    // Показываем эффект нажатия
    function showClickEffect() {
        for (var i = 0; i < clickRings.count; i++) {
            var ring = clickRings.itemAt(i)
            ring.visible = true
            ring.opacity = 0.8 - i*0.3
            ring.ringScale = 0.5 + i*0.2

            var ringAnim = ringAnimComponent.createObject(root, {
                "targetRing": ring,
                "index": i
            })
            ringAnim.start()
        }
    }

    // Компонент анимации колец
    Component {
        id: ringAnimComponent
        ParallelAnimation {
            property Item targetRing
            property int index
            NumberAnimation {
                target: targetRing
                property: "ringScale"
                from: 0.5 + index*0.2
                to: 2.0
                duration: 400
            }
            NumberAnimation {
                target: targetRing
                property: "opacity"
                from: 0.8 - index*0.3
                to: 0
                duration: 400
            }
            onStopped: {
                targetRing.visible = false
                destroy()
            }
        }
    }

    // Автоматическое скрытие
    Timer {
        interval: 100
        running: true
        repeat: true
        onTriggered: {
            root.visible = cursorVisible && Qt.application.active
        }
    }

    Component.onCompleted: {
        cursorCross.x = parent.width/2 - cursorCross.width/2
        cursorCross.y = parent.height/2 - cursorCross.height/2
    }
}
