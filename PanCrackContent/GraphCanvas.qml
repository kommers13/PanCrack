import QtQuick
import PanCrack

// js
import "js/draw_utils.js" as DrawingUtils


Canvas {
    id: canvas_graphdraw
    width: 850
    height: 920
    x: Constants.width - 86 - width
    y: 80

    // области для работы курсора мыши
    MouseArea {
        id: canvas_mouse_area
        width: parent.width
        height: parent.height
        acceptedButtons: Qt.LeftButton
        hoverEnabled: true
        drag.threshold: 0
        onPositionChanged: (mouse) => {
            let [nx, ny] = DrawingUtils.transform_mouse_coords(mouse.x, mouse.y, canvas_graphdraw.getContext("2d"));
            text_coords.text = `X: ${Math.round(nx)}\nY: ${Math.round(ny)}`;

            // проверяем, что была нажата левая кнопка мыши при изменении позиции курсора
            if (canvas_mouse_area.pressedButtons == Qt.LeftButton) {
                canvas_mouse_area.focus = true; // Отдаем фокус клавиатуры для MouseArea
                // находим вершины, на которых находится курсор (мы должны перевести координаты
                // курсора в координаты холста) и передвинуть их на то место, где сейчас находится курсор,
                // затем перерисовать граф и сохранить координаты этого графа на время его редактирования
                DrawingUtils.move_vertex(mouse.x, mouse.y, canvas_graphdraw, canvas_graphdraw.getContext("2d"));

            }
            else {
                DrawingUtils.set_CURRENT_VERTEX(null);
            }

            // console.log(Qt.LeftButton);
            // if (mouse.button === Qt.LeftButton) {
            //     console.log("ЫЫЫЫЫЫ COORDS: ", mouse.x, mouse.y)
            // }
        }
    }

    WheelHandler {
        onWheel: (event) => {
            // увеличение/уменьшение масштаба      
            if (event.modifiers & Qt.ShiftModifier) {
                if (event.angleDelta.y > 0) {
                    DrawingUtils.scale_canvas(1.05, event.x, event.y, canvas_graphdraw, canvas_graphdraw.getContext("2d"));
                    // console.log("CANVAS ZOOM")
                }
                else if (event.angleDelta.y < 0) {
                    DrawingUtils.scale_canvas(0.95, event.x, event.y, canvas_graphdraw, canvas_graphdraw.getContext("2d"));
                    // console.log("CANVAS ZOOM OUT")
                }
            }
            // влево-вправо
            else if (event.modifiers & Qt.ControlModifier){
                if (event.angleDelta.y > 0) {
                    DrawingUtils.translate_canvas(50, 0, canvas_graphdraw, canvas_graphdraw.getContext("2d"));
                    // console.log("CANVAS LEFT")
                }
                else if (event.angleDelta.y < 0) {
                    DrawingUtils.translate_canvas(-50, 0, canvas_graphdraw, canvas_graphdraw.getContext("2d"));
                    // console.log("CANVAS RIGHT")
                }
            }
            // вверх-вниз
            else {
                if (event.angleDelta.y > 0) {
                    DrawingUtils.translate_canvas(0, 50, canvas_graphdraw, canvas_graphdraw.getContext("2d"));
                    // console.log("CANVAS UP")
                }
                else if (event.angleDelta.y < 0) {
                    DrawingUtils.translate_canvas(0, -50, canvas_graphdraw, canvas_graphdraw.getContext("2d"));
                    // console.log("CANVAS DOWN")
                }
            }
        }
    }

    Text {
        id: text_coords
        x: parent.width - width
        y: parent.height - height
        text: "X: none\nY: none";
        font.pixelSize: 12
        font.family: "Courier New"
        color: "#90ee90"
        padding: 10
    }

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
    onAvailableChanged: {
        if (canvas_graphdraw.available) {
            let ctx = canvas_graphdraw.getContext("2d");
            ctx.fillStyle = Qt.rgba(0.007, 0.03, 0.03, 1);
            ctx.fillRect(0, 0, canvas_graphdraw.width,
                         canvas_graphdraw.height);
            canvas_graphdraw.requestPaint();
        }
    }
}
