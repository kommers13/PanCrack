/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/
import QtQuick
import QtQuick.Controls
import PanCrack
import QtQuick.Timeline 1.0

Rectangle {
    width: Constants.width
    height: Constants.height

    color: "#000c0c"
    opacity: 0

    Bsod {
        id: bsod
        anchors.fill: parent
    }

    // Остальной код остается без изменений
    SequentialAnimation on opacity {
        running: true
        PauseAnimation {
            duration: 500
        }
        NumberAnimation {
            from: 0
            to: 1
            duration: 1500
            easing.type: Easing.InOutQuad
        }
    }

    // Intense flickering background with virus-like patterns
    Rectangle {
        anchors.fill: parent
        color: "#000c0c"
        opacity: 0.8
        NumberAnimation on opacity {
            from: 0.5
            to: 0.9
            duration: 50 + Math.random() * 150
            loops: Animation.Infinite
            easing.type: Easing.InOutSine
        }
    }

    // Extreme scanlines with intense flickering
    Repeater {
        model: 80 // Even more scanlines
        Rectangle {
            width: parent.width
            height: 1
            y: index * (parent.height / 80)
            color: "#00ff00"
            opacity: 0.1 + Math.random() * 0.15
            NumberAnimation on opacity {
                from: 0.1 + Math.random() * 0.15
                to: 0.25 + Math.random() * 0.15
                duration: 200 + Math.random() * 300
                loops: Animation.Infinite
                easing.type: Easing.InOutSine
            }
            NumberAnimation on y {
                from: index * (parent.height / 80)
                to: (index + 1) * (parent.height / 80)
                duration: 5000 + Math.random() * 3000
                loops: Animation.Infinite
            }
        }
    }

    // Hyper-aggressive grid pattern with distortion
    Repeater {
        model: 40 // Ultra-dense grid
        Rectangle {
            width: parent.width
            height: 1
            y: index * (parent.height / 40)
            color: "#00ff88"
            opacity: 0.3
            NumberAnimation on opacity {
                from: 0.3
                to: 0.7
                duration: 800 + index * 30
                loops: Animation.Infinite
                easing.type: Easing.InOutQuad
            }
            NumberAnimation on y {
                from: index * (parent.height / 40) - 2
                to: index * (parent.height / 40) + 2
                duration: 3000 + index * 100
                loops: Animation.Infinite
                easing.type: Easing.InOutBack
            }
        }
    }

    Repeater {
        model: 60 // More vertical lines with distortion
        Rectangle {
            width: 1
            height: parent.height
            x: index * (parent.width / 60)
            color: "#00ff88"
            opacity: 0.3
            NumberAnimation on opacity {
                from: 0.3
                to: 0.7
                duration: 800 + index * 30
                loops: Animation.Infinite
                easing.type: Easing.InOutQuad
            }
            NumberAnimation on x {
                from: index * (parent.width / 60) - 2
                to: index * (parent.width / 60) + 2
                duration: 3500 + index * 100
                loops: Animation.Infinite
                easing.type: Easing.InOutBack
            }
        }
    }

    // Binary rain with distortion and chaos
    Repeater {
        model: 40 // More elements, more chaos
        Text {
            text: "0101010101010101010101010101010101010101010101010101010101010101"
            color: index % 2 ? "#00ff88" : "#00ff00"
            font.family: "Courier New"
            font.pixelSize: 12 + index * 3
            rotation: -25 + index * 10
            opacity: 0.3 + index * 0.04
            x: -200 + index * 120
            y: 50 + index * 60

            NumberAnimation on x {
                from: -200 + index * 120
                to: width + 200
                duration: 3000 + index * 800
                loops: Animation.Infinite
            }
            NumberAnimation on y {
                from: 50 + index * 60
                to: 50 + index * 60 + (Math.random() > 0.5 ? 50 : -50)
                duration: 2000 + Math.random() * 3000
                loops: Animation.Infinite
                easing.type: Easing.InOutElastic
            }
        }
    }

    // Virus circles with extreme pulsing and distortion
    Repeater {
        model: 15
        Rectangle {
            width: 60 + index * 50
            height: width
            radius: width / 2
            color: "transparent"
            border.color: "#00ff88"
            border.width: 1.5 + index * 0.8
            opacity: 0.15
            x: Math.random() * parent.width
            y: Math.random() * parent.height

            RotationAnimation on rotation {
                from: 0
                to: 360
                duration: 4000 + index * 1500
                loops: Animation.Infinite
            }

            NumberAnimation on opacity {
                from: 0.15
                to: 0.4
                duration: 1500 + index * 400
                loops: Animation.Infinite
                easing.type: Easing.InOutQuad
            }

            NumberAnimation on width {
                from: 60 + index * 50
                to: 80 + index * 50
                duration: 3000 + index * 1000
                loops: Animation.Infinite
                easing.type: Easing.InOutBack
            }
            NumberAnimation on height {
                from: 60 + index * 50
                to: 80 + index * 50
                duration: 3000 + index * 1000
                loops: Animation.Infinite
                easing.type: Easing.InOutBack
            }
        }
    }

    // Window borders with extreme corner animations
    Rectangle {
        id: leftWindowBorder
        width: commandLine.width + 20
        height: commandLine.height + 20
        x: commandLine.x - 10
        y: commandLine.y - 10
        color: "transparent"
        border.color: "#00ff88"
        border.width: 3

        Repeater {
            model: 4
            Rectangle {
                property int corner: index
                width: 20
                height: 4
                color: "#00ff00"
                opacity: 0.9
                x: corner % 2 ? parent.width - width - 5 : 5
                y: corner < 2 ? 5 : parent.height - height - 5
                NumberAnimation on opacity {
                    from: 0.3
                    to: 1.0
                    duration: 300 + index * 80
                    loops: Animation.Infinite
                    easing.type: Easing.InOutSine
                }
                NumberAnimation on rotation {
                    from: -5
                    to: 5
                    duration: 500 + index * 200
                    loops: Animation.Infinite
                    easing.type: Easing.InOutBack
                }
            }
        }
        Repeater {
            model: 4
            Rectangle {
                property int corner: index
                width: 4
                height: 20
                color: "#00ff00"
                opacity: 0.9
                x: corner % 2 ? parent.width - width - 5 : 5
                y: corner < 2 ? 5 : parent.height - height - 5
                NumberAnimation on opacity {
                    from: 1.0
                    to: 0.3
                    duration: 300 + index * 80
                    loops: Animation.Infinite
                    easing.type: Easing.InOutSine
                }
                NumberAnimation on rotation {
                    from: 5
                    to: -5
                    duration: 500 + index * 200
                    loops: Animation.Infinite
                    easing.type: Easing.InOutBack
                }
            }
        }
    }

    Rectangle {
        id: rightWindowBorder
        width: canvas_graphdraw.width + 20
        height: canvas_graphdraw.height + 20
        x: canvas_graphdraw.x - 10
        y: canvas_graphdraw.y - 10
        color: "transparent"
        border.color: "#00ff88"
        border.width: 3

        Repeater {
            model: 4
            Rectangle {
                property int corner: index
                width: 20
                height: 4
                color: "#00ff00"
                opacity: 0.9
                x: corner % 2 ? parent.width - width - 5 : 5
                y: corner < 2 ? 5 : parent.height - height - 5
                NumberAnimation on opacity {
                    from: 1.0
                    to: 0.3
                    duration: 300 + index * 80
                    loops: Animation.Infinite
                    easing.type: Easing.InOutSine
                }
                NumberAnimation on rotation {
                    from: 5
                    to: -5
                    duration: 500 + index * 200
                    loops: Animation.Infinite
                    easing.type: Easing.InOutBack
                }
            }
        }
        Repeater {
            model: 4
            Rectangle {
                property int corner: index
                width: 4
                height: 20
                color: "#00ff00"
                opacity: 0.9
                x: corner % 2 ? parent.width - width - 5 : 5
                y: corner < 2 ? 5 : parent.height - height - 5
                NumberAnimation on opacity {
                    from: 0.3
                    to: 1.0
                    duration: 300 + index * 80
                    loops: Animation.Infinite
                    easing.type: Easing.InOutSine
                }
                NumberAnimation on rotation {
                    from: -5
                    to: 5
                    duration: 500 + index * 200
                    loops: Animation.Infinite
                    easing.type: Easing.InOutBack
                }
            }
        }
    }

    // Extreme window title animations
    Text {
        text: "COMMAND TERMINAL"
        color: "#00ff88"
        font.family: "Courier New"
        font.bold: true
        font.pixelSize: 18
        x: leftWindowBorder.x + 10
        y: leftWindowBorder.y - 35

        SequentialAnimation on opacity {
            loops: Animation.Infinite
            NumberAnimation {
                from: 0.2
                to: 1.0
                duration: 300
                easing.type: Easing.InOutQuad
            }
            NumberAnimation {
                from: 1.0
                to: 0.2
                duration: 300
                easing.type: Easing.InOutQuad
            }
        }

        SequentialAnimation on color {
            loops: Animation.Infinite
            ColorAnimation {
                from: "#00ff88"
                to: "#00ff00"
                duration: 700
                easing.type: Easing.InOutQuad
            }
            ColorAnimation {
                from: "#00ff00"
                to: "#ff00ff"
                duration: 700
                easing.type: Easing.InOutQuad
            }
            ColorAnimation {
                from: "#ff00ff"
                to: "#00ff88"
                duration: 700
                easing.type: Easing.InOutQuad
            }
        }

        NumberAnimation on x {
            from: leftWindowBorder.x + 8
            to: leftWindowBorder.x + 12
            duration: 2000
            loops: Animation.Infinite
            easing.type: Easing.InOutBack
        }
    }

    Text {
        text: "NETWORK GRAPH"
        color: "#00ff00"
        font.family: "Courier New"
        font.bold: true
        font.pixelSize: 18
        x: rightWindowBorder.x + 10
        y: rightWindowBorder.y - 35

        SequentialAnimation on opacity {
            loops: Animation.Infinite
            NumberAnimation {
                from: 1.0
                to: 0.2
                duration: 300
                easing.type: Easing.InOutQuad
            }
            NumberAnimation {
                from: 0.2
                to: 1.0
                duration: 300
                easing.type: Easing.InOutQuad
            }
        }

        SequentialAnimation on color {
            loops: Animation.Infinite
            ColorAnimation {
                from: "#00ff00"
                to: "#ff00ff"
                duration: 700
                easing.type: Easing.InOutQuad
            }
            ColorAnimation {
                from: "#ff00ff"
                to: "#00ff88"
                duration: 700
                easing.type: Easing.InOutQuad
            }
            ColorAnimation {
                from: "#00ff88"
                to: "#00ff00"
                duration: 700
                easing.type: Easing.InOutQuad
            }
        }

        NumberAnimation on x {
            from: rightWindowBorder.x + 8
            to: rightWindowBorder.x + 12
            duration: 2000
            loops: Animation.Infinite
            easing.type: Easing.InOutBack
        }
    }

    // Extreme data stream effect at bottom
    Rectangle {
        width: parent.width
        height: 40
        anchors.bottom: parent.bottom
        color: "transparent"

        Repeater {
            model: 80
            Rectangle {
                width: 4
                height: 10 + Math.random() * 30
                x: index * (parent.width / 80)
                y: parent.height - height
                color: "#00ff00"
                opacity: 0.6 + Math.random() * 0.4

                NumberAnimation on height {
                    from: 10 + Math.random() * 30
                    to: 10 + Math.random() * 30
                    duration: 200 + Math.random() * 500
                    loops: Animation.Infinite
                    easing.type: Easing.InOutQuad
                }
                NumberAnimation on y {
                    from: parent.height - height
                    to: parent.height - height - (Math.random() * 15)
                    duration: 500 + Math.random() * 1000
                    loops: Animation.Infinite
                    easing.type: Easing.InOutElastic
                }
            }
        }
    }

    // Additional random glitch elements
    Repeater {
        model: 10
        Rectangle {
            width: 50 + Math.random() * 100
            height: 3
            color: "#00ff00"
            opacity: 0.3 + Math.random() * 0.7
            x: Math.random() * parent.width
            y: Math.random() * parent.height
            rotation: Math.random() * 360

            NumberAnimation on opacity {
                from: 0.3 + Math.random() * 0.7
                to: 0
                duration: 500 + Math.random() * 1500
                loops: Animation.Infinite
                easing.type: Easing.InOutQuad
            }
            NumberAnimation on x {
                from: Math.random() * parent.width
                to: Math.random() * parent.width
                duration: 2000 + Math.random() * 3000
                loops: Animation.Infinite
                easing.type: Easing.InOutBack
            }
        }
    }

    CommandLine {
        id: commandLine
        x: 86
        y: 80
        clip: true
    }

    Rectangle {
        width: 100
        height: 100
        x: parent.width - 86 - 850
        y: 80
    }

    Canvas {
        id: canvas_graphdraw
        width: 850
        height: 920
        x: parent.width - 86 - width
        y: 80

        Rectangle {
            anchors.fill: parent
            color: "transparent"
            border.color: "#00ff88"
            border.width: 2
            opacity: 0.7
            NumberAnimation on opacity {
                from: 0.5
                to: 0.9
                duration: 1000
                loops: Animation.Infinite
                easing.type: Easing.InOutQuad
            }
        }

        Rectangle {
            width: parent.width
            height: 2
            color: "#00ff00"
            opacity: 0.8
            y: parent.height / 2
            NumberAnimation on y {
                from: 0
                to: parent.height
                duration: 3000
                loops: Animation.Infinite
            }
            NumberAnimation on opacity {
                from: 0.8
                to: 0
                duration: 3000
                loops: Animation.Infinite
            }
        }

        Repeater {
            model: 20
            Rectangle {
                width: 1
                height: parent.height
                x: index * (parent.width / 20)
                color: "#00ff88"
                opacity: 0.1
            }
        }
        Repeater {
            model: 20
            Rectangle {
                width: parent.width
                height: 1
                y: index * (parent.height / 20)
                color: "#00ff88"
                opacity: 0.1
            }
        }
    }

    Connections {
        target: canvas_graphdraw
        onAvailableChanged: {
            if (canvas_graphdraw.available) {
                let ctx = canvas_graphdraw.getContext("2d")
                ctx.fillStyle = Qt.rgba(0.007, 0.03, 0.03, 1)
                ctx.fillRect(0, 0, canvas_graphdraw.width,
                             canvas_graphdraw.height)
                canvas_graphdraw.requestPaint()
            }
        }
    }
}
