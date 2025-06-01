.pragma library



const cyberColors = [
    ["#00FF41", "#001F0D"],  // Неоново-зеленый с темно-зеленым текстом
    ["#FF0033", "#1F000A"],  // Ярко-красный с темно-бордовым текстом
    ["#FF6600", "#1F0A00"],  // Оранжевый с темно-коричневым текстом
    ["#00CCFF", "#00101F"],  // Голубой с темно-синим текстом
    ["#9900FF", "#0F001F"],  // Фиолетовый с темно-фиолетовым текстом
    ["#FF00FF", "#1F001F"],  // Розовый с темно-пурпурным текстом
    ["#00FF99", "#001F10"],  // Аквамарин с темно-бирюзовым текстом
    ["#00FFCC", "#001F14"],  // Бирюзовый с темно-бирюзовым текстом
    ["#FF3399", "#1F000A"],  // Малиновый с темно-бордовым текстом
    ["#33FF00", "#0A1F00"]   // Лаймовый с темно-зеленым текстом
];

const GLOW_COLOR = "#00FF41";
const ERROR_COLOR = "#FF0033";

// эта переменная зависит от переменной в области имен graphdraw
// при увеличении масштаба радиус будет уменьшаться
// при уменьшении - наоборот
let RADIUS = 15;

// толщина ребер
// при увеличении масштаба толщина будет изменяться
// при уменьшении - наоборот
let EDGE_WIDTH = 2.0;

// размер шрифта
let FONT_PX = 20;

// цвет ребер
const EDGE_COLOR = "#00FF00";

// глобальная переменная с координатами графа
// граф рисуется, и тогда, он находится на экране, его можно МАСШТАБИРОВАТЬ, ПЕРЕМЕЩАТЬ, ДВИГАТЬ ВЕРШИНЫ,
// т. е. тогда, когда GRAPH != null
// когда canvas очищается, то GRAPH становится равным null
// Т. Е. точкой входа в canvas является draw_graph
// Таким образом, пока GRAPH != null, он находится на экране, иначе, когда он исчезает с экрана,
// получаем GRAPH = null
let GRAPH = null            // НЕ ИСПОЛЬЗУЙТЕ ГЛОБАЛЬНЫЕ ПЕРЕМЕННЫЕ, ДА ЛАДНО, ВЫ ЧТО, ИЗДЕВАЕТЕСЬ


// коэффициент масштабирования canvas-а
let k_scale = 1;
// сдвиг canvas-а
let OFFSETX = 0;
let OFFSETY = 0;

const edgeStyles = [
    {color: "#00FF41", width: EDGE_WIDTH}, // Основной хакерский
    {color: "#FF0033", width: EDGE_WIDTH}, // Вирусный
    {color: "#FF6600", width: EDGE_WIDTH}, // Оранжевый угроза
    {color: "#9900FF", width: EDGE_WIDTH}, // Фиолетовый взлом
    {color: "#00CCFF", width: EDGE_WIDTH}  // Голубой сигнал
];


// функция для очистки Canvas-а
function clean_canvas(canvas_gd, ctx, clean_graph) {
    // очищаем холст
    ctx.setTransform(1, 0, 0, 1, 0, 0);
    ctx.fillStyle = Qt.rgba(0.007, 0.03, 0.03, 1);
    ctx.fillRect(0, 0, canvas_gd.width, canvas_gd.height);

    // применяем текущие трансформации
    ctx.translate(OFFSETX, OFFSETY);
    ctx.scale(k_scale, k_scale);

    GRAPH = (clean_graph ? null : GRAPH);
    canvas_gd.requestPaint();
}


// граф в переменной graph всегда ПРАВИЛЬНЫЙ
// canvas_gd - объект Canvas для рисования графа
function draw_graph(graph, canvas_gd, ctx) {

    GRAPH = graph;  // обозначаем, что на экране сейчас находится граф

    // DRAWING
    // рисуем graph
    ctx.strokeStyle = EDGE_COLOR;            // set the color for the circle to 'green'
    ctx.lineWidth = EDGE_WIDTH;              // set the lineWidth for the circle to 5.0


    // Сброс всех эффектов
    ctx.shadowBlur = 0;
    ctx.setLineDash([]);
    ctx.globalAlpha = 1.0;

    // Рисуем ребра
    for (let e in graph["edges"]) {
        let edge = graph["edges"][e];
        let v1 = edge[0];
        let v2 = edge[1];
        let w = edge[2];
        let x1 = graph["vertices"][v1][0];
        let y1 = graph["vertices"][v1][1];
        let x2 = graph["vertices"][v2][0];
        let y2 = graph["vertices"][v2][1];

        let style = edgeStyles[e % edgeStyles.length];

        ctx.beginPath();
        ctx.moveTo(x1, y1);
        ctx.lineTo(x2, y2);
        ctx.strokeStyle = style.color;
        ctx.lineWidth = EDGE_WIDTH;
        ctx.stroke();
        ctx.closePath();
    }

    // Рисуем вершины с обводкой того же цвета
    for (let v in graph["vertices"]) {
        let x = graph["vertices"][v][0];
        let y = graph["vertices"][v][1];
        let colorIndex = graph["colors"][v] % cyberColors.length;
        let [fillColor, textColor] = cyberColors[colorIndex];

        // Основной круг с обводкой цвета вершины
        ctx.beginPath();
        ctx.arc(x, y, RADIUS, 0, 2 * Math.PI);
        ctx.fillStyle = fillColor;
        // ctx.strokeStyle = fillColor; // Обводка того же цвета, что и заливка
        // ctx.lineWidth = EDGE_WIDTH;
        ctx.fill();
        // ctx.stroke();
        ctx.closePath();

        // Внутренняя темная обводка (цвет текста)
        ctx.beginPath();
        ctx.arc(x, y, RADIUS * 0.9, 0, 2 * Math.PI);
        ctx.strokeStyle = textColor;
        ctx.lineWidth = EDGE_WIDTH / 1.5;
        ctx.stroke();
        ctx.closePath();

        // Текст вершины
        ctx.beginPath();
        ctx.font = `bold ${FONT_PX}px "Courier New", monospace`;
        ctx.fillStyle = textColor;
        ctx.textAlign = "center";
        ctx.textBaseline = "middle";
        ctx.fillText(v, x, y);
        ctx.closePath();
    }

    // Рисуем веса
    for (let e in graph["edges"]) {
        let edge = graph["edges"][e];
        let v1 = edge[0];
        let v2 = edge[1];
        let w = edge[2];
        let x1 = graph["vertices"][v1][0];
        let y1 = graph["vertices"][v1][1];
        let x2 = graph["vertices"][v2][0];
        let y2 = graph["vertices"][v2][1];

        let midX = (x1 + x2) / 2;
        let midY = (y1 + y2) / 2;

        // Фон для текста веса
        ctx.beginPath();
        ctx.font = `bold ${FONT_PX}px 'Courier New', monospace`;
        let textWidth = ctx.measureText(w).width;

        // console.log("metrics:", ctx.measureText(w));
        ctx.fillStyle = "#000000";
        ctx.fillRect(midX - textWidth / 2, midY - FONT_PX / 2, textWidth * 1.1, FONT_PX * 1.1);
        ctx.closePath();

        // Текст веса цветом ребра
        ctx.beginPath();
        ctx.fillStyle = edgeStyles[e % edgeStyles.length].color;
        ctx.textAlign = "center";
        ctx.textBaseline = "middle";
        ctx.fillText(w, midX, midY);
        ctx.closePath();
    }

    // квадрат для отладки
    // ctx.beginPath();
    // ctx.strokeStyle = "white";
    // ctx.strokeWidth = 2.5;
    // ctx.strokeRect(0, 0, canvas_gd.width, canvas_gd.height);
    // ctx.closePath();

    canvas_gd.requestPaint();
}

// изменение масштаба графа
// при это нужно делать так, чтобы Canvas всегда находился по центру своей области
function scale_canvas(scale, cx, cy, canvas_gd, ctx) {
    if (GRAPH != null) {
        // console.log("K_scale: ", k_scale * scale);

        if (0.312 < k_scale * scale && k_scale * scale < 6) {

            k_scale *= scale;

            // вычисляем новые координаты
            let [nx, ny] = transform_mouse_coords(cx, cy, ctx);

            // вычисляем расстояние от координаты мыши до новых координат после масштабирования
            OFFSETX = cx - nx * scale;
            OFFSETY = cy - ny * scale;

            FONT_PX /= scale;
            EDGE_WIDTH /= scale;
            RADIUS /= scale;

            clean_canvas(canvas_gd, ctx, 0);
            draw_graph(GRAPH, canvas_gd, ctx);
        }
    }
}

// смещение Canvas-а по оси X или оси Y
function translate_canvas(offset_axis, axis, canvas_gd, ctx) {
    if (GRAPH != null) {
        if (axis === 'X') {
            OFFSETX += offset_axis;
        }
        else {
            OFFSETY += offset_axis;
        }

        // очищаем Canvas
        clean_canvas(canvas_gd, ctx, 0);
        draw_graph(GRAPH, canvas_gd, ctx);
    }
}

// координаты мыши трансформировались в координаты Canvas-а
function transform_mouse_coords(cx, cy, ctx) {
    let nx, ny;
    nx = cx - OFFSETX;
    ny = cy - OFFSETY;

    // console.log("CX, CY: ", cx, cy);
    // console.log("NX, NY: ", nx, ny);

    return [nx, ny];
}
