import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Timeline 1.0
// import QtQuick.Window 2.15

Window {
    id: mainWindow
    width: 420
    height: 220
    visible: true
    color: "#00000000"
    title: "PanCrack v2.4.1"
    flags: Qt.Window | Qt.FramelessWindowHint

    property bool glitchActive: false
    property int glitchIntensity: 100
    property bool matrixVisible: false
    property int windowShake: 0
    property int duplicateWindows: 0
    property bool invertedColors: false
    property bool aggressiveMode: false
    property bool contentsLocked: false
    property real originalX: Screen.width / 2 - width / 2
    property real originalY: Screen.height / 2 - height / 2
    property bool positionLocked: false
    property bool virusEffectVisible: false // Новое свойство для вирусного эффекта

    // Основное окно с закругленными углами
    Rectangle {
        anchors.fill: parent
        radius: 12
        color: "#000000"
        border.color: progressBar.value >= 1.0 ? "#ff0000" : "#00ff00"
        border.width: 2
        clip: true

        // Внутренняя рамка
        Rectangle {
            anchors.fill: parent
            anchors.margins: 10
            color: "transparent"
            border.color: "#3300ff00"
            border.width: 1
            radius: 6
        }

        // Фоновый шум
        Rectangle {
            anchors.fill: parent
            anchors.margins: 2
            opacity: 0.05
            radius: parent.radius - 2
            layer.enabled: true
            // layer.effect: ShaderEffect {
            //     property real time: 0
            //     fragmentShader: "
            //         uniform lowp float qt_Opacity;
            //         uniform highp float time;
            //         varying highp vec2 qt_TexCoord0;
            //         void main() {
            //             highp vec2 uv = qt_TexCoord0;
            //             highp float noise = fract(sin(dot(uv, vec2(12.9898, 78.233)) * 43758.5453 + time));
            //             gl_FragColor = vec4(vec3(noise), 1.0) * qt_Opacity;
            //         }"
            //     NumberAnimation on time {
            //         from: 0
            //         to: 1000
            //         duration: 10000
            //         loops: Animation.Infinite
            //     }
            // }
        }

        // Сканирующая линия
        Rectangle {
            id: scanLine
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
                opacity: matrixVisible ? (0.3 + Math.random() * 0.2) : 0
                font.pixelSize: 12
                font.family: "Courier New"
                style: Text.Outline
                styleColor: "#000000"

                property int speed: 50 + Math.random() * 150
                property int columnLength: 10 + Math.random() * 15
                property string chars: "01アイウエオカキクケコサシスセソタチツテトABCDEFGHIJKLMNOPQRSTUVWXYZ"
                property int columnIndex: index

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
                    running: matrixVisible
                    repeat: true
                    onTriggered: {
                        parent.y += 5;
                        if (parent.y > parent.parent.height) {
                            parent.y = -parent.height - Math.random() * 50;
                            parent.text = parent.generateMatrixColumn();
                        }
                    }
                }

                Behavior on opacity {
                    NumberAnimation { duration: 1000 }
                }
            }
        }

        // Вирусный эффект (появляется при 40% и исчезает при 70%)
        Rectangle {
            id: virusEffect
            anchors.fill: parent
            visible: virusEffectVisible
            color: "transparent"
            z: 10

            // Красные линии сканирования
            Repeater {
                model: virusEffectVisible ? 5 : 0
                Rectangle {
                    width: parent.width
                    height: 1
                    color: "#ff0000"
                    opacity: 0.5
                    y: index * (parent.height / 5)
                    NumberAnimation on y {
                        from: 0
                        to: parent.height
                        duration: 800 + index * 200
                        loops: Animation.Infinite
                    }
                }
            }

            // Взломанный текст
            Text {
                anchors.centerIn: parent
                text: "GRAPH CORE UNLOCKED"//"RUNNING solve --all-graphs"//"ALGORITHM CORE UNLOCKED"//"SYSTEM BREACH DETECTED"
                font.pixelSize: 16
                font.family: "Courier New"
                font.bold: true
                color: "#ff0000"
                style: Text.Outline
                styleColor: "#000000"
                opacity: 0.8
                visible: virusEffectVisible

                SequentialAnimation on scale {
                    running: virusEffectVisible
                    loops: Animation.Infinite
                    NumberAnimation { to: 1.05; duration: 500 }
                    NumberAnimation { to: 0.95; duration: 500 }
                }

                SequentialAnimation on rotation {
                    running: virusEffectVisible
                    loops: Animation.Infinite
                    NumberAnimation { to: 1; duration: 300 }
                    NumberAnimation { to: -1; duration: 300 }
                    NumberAnimation { to: 0; duration: 300 }
                }
            }

            // Бинарный код атаки
            Text {
                anchors.fill: parent
                anchors.margins: 10
                text: generateVirusBinary()
                font.pixelSize: 10
                font.family: "Courier New"
                color: "#ff0000"
                opacity: 0.6
                wrapMode: Text.Wrap
                visible: virusEffectVisible

                function generateVirusBinary() {
                    var result = "";
                    for (var i = 0; i < 100; i++) {
                        result += Math.random() > 0.3 ? "1" : "0";
                        if (Math.random() > 0.7) result += " ";
                        if (i % 10 === 0) result += "\n";
                    }
                    return result;
                }

                Timer {
                    interval: 100
                    running: virusEffectVisible
                    repeat: true
                    onTriggered: parent.text = parent.generateVirusBinary()
                }
            }
        }

        // Основной контент
        Item {
            id: root
            anchors.fill: parent
            anchors.margins: 10
            z: 5

            MouseArea {
                id: dragArea
                anchors.fill: parent
                drag.target: contentsLocked ? null : parent
                onPressed: {
                    if (!contentsLocked) {
                        mainWindow.startSystemMove();
                    }
                }
            }

            Item {
                id: titleContainer
                x: 20
                y: 15
                width: 150
                height: 40

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
                    property bool isHacked: false
                    x: shakeX
                    y: shakeY

                    SequentialAnimation on opacity {
                        running: true
                        loops: Animation.Infinite
                        NumberAnimation { to: 0.8; duration: 2000 }
                        NumberAnimation { to: 1.0; duration: 2000 }
                    }
                }

                Text {
                    id: versionText
                    y: mainTitle.height
                    text: "v2.4.1"
                    font.pixelSize: 14
                    color: "#00ff00"
                    font.family: "Courier New"
                    style: Text.Outline
                    styleColor: "#002200"
                    property real shakeX: 0
                    property real shakeY: 0
                    property bool isHacked: false
                    x: shakeX
                }
            }

            Text {
                id: _text2
                x: 20
                y: 110
                width: 200
                height: 16
                text: "STATUS: WAITING"
                font.pixelSize: 14
                color: "#00ff00"
                font.family: "Courier New"
                style: Text.Outline
                styleColor: "#002200"
            }

            // Улучшенный прогресс-бар в хакерском стиле
            Rectangle {
                id: progressBarContainer
                x: 20
                y: 140
                width: parent.width - 40
                height: 24
                color: "transparent"
                border.color: progressBar.value >= 1.0 ? "transparent" : "#00aa00"
                border.width: 2
                radius: 3
                z: 10
                clip: true

                // Фоновый узор прогресс-бара
                Rectangle {
                    anchors.fill: parent
                    anchors.margins: 2
                    color: "transparent"
                    opacity: 0.5
                    Canvas {
                        anchors.fill: parent
                        onPaint: {
                            var ctx = getContext("2d");
                            ctx.strokeStyle = progressBar.value >= 1.0 ? "#ff0000" : "#00aa00";
                            ctx.lineWidth = 1;

                            // Рисуем диагональные линии
                            var step = 8;
                            for (var x = -height; x < width; x += step) {
                                ctx.beginPath();
                                ctx.moveTo(x, height);
                                ctx.lineTo(x + height, 0);
                                ctx.stroke();
                            }
                        }
                    }
                }

                // Основная полоска прогресса
                Rectangle {
                    id: progressBarFill
                    width: Math.min(progressBar.value * (parent.width - 4), parent.width - 4)
                    height: parent.height - 4
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: 2
                    color: progressBar.value >= 1.0 ? "#ff0000" : "#00ff77"
                    opacity: 0.9
                    z: 1
                    radius: 2

                    // Эффект сканирования
                    Rectangle {
                        width: parent.width
                        height: 2
                        color: progressBar.value >= 1.0 ? "#ff5555" : "white"
                        opacity: 0.7
                        y: 0
                        NumberAnimation on y {
                            from: 0
                            to: parent.height
                            duration: 800
                            loops: Animation.Infinite
                        }
                    }

                    // Эффект свечения
                    Rectangle {
                        anchors.fill: parent
                        color: "transparent"
                        border.color: progressBar.value >= 1.0 ? "#ff0000" : "#ffffff"
                        border.width: 0
                        opacity: 0
                        radius: parent.radius

                        SequentialAnimation on opacity {
                            running: true
                            loops: Animation.Infinite
                            NumberAnimation { to: 0.5; duration: 1000 }
                            NumberAnimation { to: 0; duration: 1000 }
                        }

                        SequentialAnimation on border.width {
                            running: true
                            loops: Animation.Infinite
                            NumberAnimation { to: 1; duration: 1000 }
                            NumberAnimation { to: 0; duration: 1000 }
                        }
                    }
                }

                // Эффект взлома при завершении
                Rectangle {
                    id: hackEffect
                    anchors.fill: parent
                    color: "transparent"
                    border.color: "#ff0000"
                    border.width: 0
                    opacity: 0
                    z: 2
                    radius: parent.radius

                    SequentialAnimation {
                        running: progressBar.value >= 1.0
                        loops: Animation.Infinite
                        ParallelAnimation {
                            NumberAnimation { target: hackEffect; property: "border.width"; to: 2; duration: 500 }
                            NumberAnimation { target: hackEffect; property: "opacity"; to: 0.8; duration: 500 }
                        }
                        ParallelAnimation {
                            NumberAnimation { target: hackEffect; property: "border.width"; to: 0; duration: 500 }
                            NumberAnimation { target: hackEffect; property: "opacity"; to: 0; duration: 500 }
                        }
                        PauseAnimation { duration: 2000 }
                    }
                }

                // Бинарный код, бегущий по прогресс-бару
                Text {
                    id: binaryCode
                    anchors.fill: parent
                    anchors.margins: 2
                    color: "#00ff00"
                    opacity: 0.7
                    font.pixelSize: 10
                    font.family: "Courier New"
                    verticalAlignment: Text.AlignVCenter
                    text: generateBinaryCode()
                    clip: true

                    function generateBinaryCode() {
                        var code = "";
                        for (var i = 0; i < 100; i++) {
                            code += Math.random() > 0.5 ? "1" : "0";
                        }
                        return code;
                    }

                    Timer {
                        interval: 100
                        running: true
                        repeat: true
                        onTriggered: parent.text = parent.generateBinaryCode()
                    }

                    NumberAnimation on x {
                        from: -parent.width
                        to: parent.width
                        duration: 2000
                        loops: Animation.Infinite
                        running: progressBar.value < 1.0
                    }
                }
            }

            Text {
                id: _text1
                x: 20
                y: 170
                width: parent.width - 40
                height: 16
                text: "INITIALIZING SYSTEM..."
                font.pixelSize: 14
                wrapMode: Text.Wrap
                color: "#00ff00"
                font.family: "Courier New"
                style: Text.Outline
                styleColor: "#002200"
            }

            Text {
                id: progressText
                x: progressBarContainer.x + progressBarContainer.width / 2 - width / 2
                y: 140
                width: 40
                height: 22
                text: Math.round(progressBar.value * 100) + "%"
                font.pixelSize: 16
                color: progressBar.value >= 1.0 ? "#ff0000" : "#ffffff"
                font.bold: true
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                z: 15
                style: Text.Outline
                styleColor: "#000000"

                SequentialAnimation on scale {
                    running: progressBar.value >= 1.0
                    loops: Animation.Infinite
                    NumberAnimation { to: 1.1; duration: 100 }
                    NumberAnimation { to: 0.9; duration: 100 }
                    NumberAnimation { to: 1.0; duration: 100 }
                    PauseAnimation { duration: 1000 }
                }

                // Эффект мерцания при 100%
                SequentialAnimation on opacity {
                    running: progressBar.value >= 1.0
                    loops: Animation.Infinite
                    NumberAnimation { to: 0.6; duration: 200 }
                    NumberAnimation { to: 1.0; duration: 200 }
                }
            }

            ProgressBar {
                id: progressBar
                visible: false
                value: 0
                onValueChanged: {
                    if (value >= 1.0) {
                        matrixVisible = true;
                        glitchActive = true;
                        virusEffectVisible = false; // Убираем вирусный эффект
                        startFinalEffects();
                        contentsLocked = true;
                        positionLocked = true;
                        mainWindow.x = originalX;
                        mainWindow.y = originalY;
                        createAggressiveDuplicates();
                    } else if (value > 0.7) {
                        aggressiveMode = true;
                        virusEffectVisible = false; // Убираем вирусный эффект при 70%
                        createDuplicateWindow();
                        contentsLocked = true;
                        positionLocked = true;
                        mainWindow.x = originalX;
                        mainWindow.y = originalY;
                    } else if (value > 0.4) {
                        windowShake = 5;
                        virusEffectVisible = true; // Показываем вирусный эффект при 40%
                        shakeTimer.start();
                    }
                }
            }

            Rectangle {
                id: lockContainer
                x: root.width - width - 20
                y: 15
                width: 45
                height: 45
                color: "#000000"
                border.color: progressBar.value >= 1.0 ? "#ff0000" : "#00ff00"
                border.width: 2
                radius: 4
                z: 20

                Image {
                    anchors.centerIn: parent
                    source: progressBar.value >= 1.0 ? "img/unlock.png" : "img/lock.png"
                    width: 24
                    height: 24
                }

                SequentialAnimation on rotation {
                    running: progressBar.value >= 1.0
                    loops: Animation.Infinite
                    NumberAnimation { from: 0; to: -5; duration: 100 }
                    NumberAnimation { from: -5; to: 5; duration: 200 }
                    NumberAnimation { from: 5; to: 0; duration: 100 }
                    PauseAnimation { duration: 2000 }
                }
            }
        }
    }

    Timeline {
        id: timeline
        animations: [
            TimelineAnimation {
                id: loadingAnimation
                running: true
                loops: 1
                duration: 12000
                to: 12000
                from: 0
                onFinished: {
                    glitchActive = true;
                    matrixVisible = true;
                }
            }
        ]
        startFrame: 0
        endFrame: 12000
        enabled: true

        KeyframeGroup {
            target: progressBar
            property: "value"
            Keyframe { value: 0; frame: 0 }
            Keyframe { value: 0.05; frame: 1000 }
            Keyframe { value: 0.12; frame: 1500 }
            Keyframe { value: 0.18; frame: 2000 }
            Keyframe { value: 0.25; frame: 2500 }
            Keyframe { value: 0.32; frame: 3000 }
            Keyframe { value: 0.4; frame: 4000 }
            Keyframe { value: 0.47; frame: 4500 }
            Keyframe { value: 0.55; frame: 5000 }
            Keyframe { value: 0.63; frame: 6000 }
            Keyframe { value: 0.7; frame: 6500 }
            Keyframe { value: 0.78; frame: 7000 }
            Keyframe { value: 0.85; frame: 7500 }
            Keyframe { value: 0.92; frame: 8500 }
            Keyframe { value: 0.96; frame: 9000 }
            Keyframe { value: 0.98; frame: 9500 }
            Keyframe { value: 0.99; frame: 10500 }
            Keyframe { value: 1; frame: 12000 }
        }

        KeyframeGroup {
            target: _text1
            property: "text"
            Keyframe { value: "DOWNLOADING: graph_algorithms.dll"; frame: 0 }
            Keyframe { value: "EXTRACTING: adjacency_list.bin"; frame: 2000 }
            Keyframe { value: "DECRYPTING: dijkstra.exe"; frame: 4000 }
            Keyframe { value: "COMPILING: topological_sort.obj"; frame: 6000 }
            Keyframe { value: "INJECTING: prims_algorithm.bat"; frame: 8000 }
            Keyframe { value: "EXECUTING: kruskal_method.7z"; frame: 10000 }
            Keyframe { value: "UPLOADING: solution_key.log"; frame: 11000 }
            Keyframe { value: "VIRUS ACTIVATED: 0x7F3A2B"; frame: 12000 }
        }

        KeyframeGroup {
            target: _text2
            property: "text"
            Keyframe { value: "STATUS: INITIALIZING..."; frame: 0 }
            Keyframe { value: "TASK 1/12: CRACKING..."; frame: 2000 }
            Keyframe { value: "TASK 4/12: BYPASSING..."; frame: 4000 }
            Keyframe { value: "TASK 7/12: COMPROMISED"; frame: 6000 }
            Keyframe { value: "TASK 10/12: EXECUTING..."; frame: 8000 }
            Keyframe { value: "TASK 12/12: SUCCESS"; frame: 10000 }
            Keyframe { value: "ALL TASKS COMPLETED"; frame: 11000 }
            Keyframe { value: "SYSTEM HACKED"; frame: 12000 }
        }
    }

    Timer {
        id: colorChangeTimer
        interval: 10
        running: true
        repeat: true
        onTriggered: {
            if (progressBar.value >= 1.0) {
                _text1.color = "#ff0000";
                _text2.color = "#ff0000";
            } else {
                _text1.color = "#00ff00";
                _text2.color = "#00ff00";
            }
        }
    }

    Timer {
        id: glitchTimer
        interval: 20
        running: glitchActive
        repeat: true
        onTriggered: {
            mainTitle.shakeX = (Math.random() * 12 - 6) * (glitchIntensity / 100)
            mainTitle.shakeY = (Math.random() * 8 - 4) * (glitchIntensity / 100)
            versionText.shakeX = (Math.random() * 8 - 4) * (glitchIntensity / 100)
            versionText.shakeY = (Math.random() * 6 - 3) * (glitchIntensity / 100)

            if (Math.random() > 0.2) {
                var colors = ["#00ff00", "#ff0000", "#0000ff", "#00ff77", "#ff00ff", "#ffff00"]
                var randomColor = colors[Math.floor(Math.random() * colors.length)]
                mainTitle.color = randomColor
                versionText.color = randomColor
            }

            if (!mainTitle.isHacked && Math.random() > 0.85) {
                mainTitle.text = "HACKED"
                versionText.text = "v0x7F3A2B"
                mainTitle.isHacked = true
                versionText.isHacked = true
                hackResetTimer.start()
            }
        }
    }

    Timer {
        id: hackResetTimer
        interval: 300
        onTriggered: {
            mainTitle.text = "PanCrack"
            versionText.text = "v2.4.1"
            mainTitle.isHacked = false
            versionText.isHacked = false
        }
    }

    // Таймер для тряски окна
    Timer {
        id: shakeTimer
        interval: 20
        repeat: true
        onTriggered: {
            if (windowShake > 0 && !positionLocked) {
                var intensity = aggressiveMode ? 2 : 1;
                var newX = mainWindow.x + (Math.random() * windowShake * 2 - windowShake) * intensity;
                var newY = mainWindow.y + (Math.random() * windowShake * 2 - windowShake) * intensity;

                newX = Math.max(0, Math.min(Screen.width - mainWindow.width, newX));
                newY = Math.max(0, Math.min(Screen.height - mainWindow.height, newY));

                mainWindow.x = newX;
                mainWindow.y = newY;

                windowShake--;

                if (windowShake <= 0) {
                    restoreWindowPosition.start();
                }
            }
        }
    }

    // Таймер для восстановления позиции окна
    Timer {
        id: restoreWindowPosition
        interval: 100
        onTriggered: {
            mainWindow.x = originalX;
            mainWindow.y = originalY;
        }
    }

    // Таймер для создания дубликатов окон (70-100%)
    Timer {
        id: duplicateTimer
        interval: 3000
        running: progressBar.value > 0.7 && progressBar.value < 1.0
        repeat: true
        onTriggered: {
            if (duplicateWindows < 3 && Math.random() > 0.5) {
                createDuplicateWindow();
            }
        }
    }

    // Функция для создания дубликата окна (70-100%)
    function createDuplicateWindow() {
        if (duplicateWindows >= 3) return;

        duplicateWindows++;
        var component = Qt.createComponent("DuplicateWindow.qml");
        if (component.status === Component.Ready) {
            // Увеличиваем расстояние между дубликатами
            var offsetX = (Math.random() * 150 - 75) * (duplicateWindows + 1);
            var offsetY = (Math.random() * 100 - 50) * (duplicateWindows + 1);

            var win = component.createObject(null, {
                "originalX": mainWindow.x + offsetX,
                "originalY": mainWindow.y + offsetY,
                "width": mainWindow.width,
                "height": mainWindow.height,
                "progressValue": progressBar.value,
                "aggressiveMode": false,
                "showContent": false,
                "showBackground": true,
                "isMainWindow": false
            });
            win.show();
        }
    }

    // В функции createAggressiveDuplicates (заменяем существующую)
    function createAggressiveDuplicates() {
        for (var i = 0; i < 5; i++) {
            var offsetX = (Math.random() * 300 - 150) * (i + 1);
            var offsetY = (Math.random() * 200 - 100) * (i + 1);

            var duplicate = Qt.createComponent("DuplicateWindow.qml").createObject(null, {
                "originalX": mainWindow.x + offsetX,
                "originalY": mainWindow.y + offsetY,
                "width": mainWindow.width,
                "height": mainWindow.height,
                "progressValue": 1.0,
                "aggressiveMode": true,
                "showContent": true,
                "showBackground": true,
                "isMainWindow": false,
                "matrixVisible": true,
                "glitchActive": true,
                "aggressionLevel": 3 + i
            });
            duplicate.show();
        }
    }

    // Функция для запуска финальных эффектов
    function startFinalEffects() {
        colorInversionTimer.interval = 300;
        colorInversionTimer.start();

        flickerTimer.interval = 50;
        flickerTimer.start();

        // Запускаем таймер для завершения анимации и перехода
        finalTransitionTimer.start();

        // Только визуальные эффекты без перемещения основного окна
        if (!contentsLocked) {
            resizeTimer.start();
        }
    }

    Timer {
        id: finalTransitionTimer
        interval: 1500//3000 // 8 секунд агрессивной анимации перед переходом
        running: false
        repeat: false
        onTriggered: {
            loadAppWindow();
        }
    }

    // Таймер для инверсии цветов
    Timer {
        id: colorInversionTimer
        interval: 1000
        running: false
        repeat: true
        onTriggered: {
            invertedColors = !invertedColors;
            if (invertedColors) {
                root.color = "#ffffff";
                _text1.color = "#000000";
                _text2.color = "#000000";
                mainTitle.color = "#000000";
                versionText.color = "#000000";
            } else {
                root.color = "#000000";
                _text1.color = "#ff0000";
                _text2.color = "#ff0000";
                mainTitle.color = "#ff0000";
                versionText.color = "#ff0000";
            }
        }
    }

    // Таймер для мигания окна
    Timer {
        id: flickerTimer
        interval: 100
        running: false
        repeat: true
        onTriggered: {
            if (!contentsLocked) {
                visible = !visible;
                if (Math.random() > 0.9) {
                    interval = 50 + Math.random() * 200;
                }
            }
        }
    }

    // Таймер для изменения размеров окна
    Timer {
        id: resizeTimer
        interval: 1200
        running: false
        repeat: true
        onTriggered: {
            if (!contentsLocked) {
                width = 420 + (Math.random() * 80 - 40);
                height = 220 + (Math.random() * 60 - 30);
            }
        }
    }

    Component.onCompleted: {
        x = originalX;
        y = originalY;
    }

    function loadAppWindow() {
        // Закрываем текущее окно
        mainWindow.close();

        // Создаем и показываем новое окно с app.qml
    //     var component = Qt.createComponent("App.qml");
    //     if (component.status === Component.Ready) {
    //         var appWindow = component.createObject(null);
    //         appWindow.show();
    //     } else {
    //         console.error("Error loading app.qml:", component.errorString());
    //     }
    }
}
