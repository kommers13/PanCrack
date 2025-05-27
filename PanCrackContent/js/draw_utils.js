.pragma library


// эта переменная зависит от переменной в области имен graphdraw
let RADIUS = 15;

// толщина ребер
let EDGE_WIDTH = 2.0;

// цвет ребер
const EDGE_COLOR = "#00FF00";

// глобальная переменная с координатами графа
// граф рисуется, и тогда, он находится на экране, его можно МАСШТАБИРОВАТЬ, ПЕРЕМЕЩАТЬ, ДВИГАТЬ ВЕРШИНЫ,
// т. е. тогда, когда GRAPH != null
// когда canvas очищается, то GRAPH становится равным null
// Т. Е. точкой входа в canvas является draw_graph
// Таким образом, пока GRAPH != null, он находится на экране, иначе, когда он исчезает с экрана, получаем
// GRAPH = null
let GRAPH = null            // НЕ ИСПОЛЬЗУЙТЕ ГЛОБАЛЬНЫЕ ПЕРЕМЕННЫЕ, ДА ЛАДНО, ВЫ ЧТО, ИЗДЕВАЕТЕСЬ


// коэффициент масштабирования canvas-а
let k_scale = 1;

// Тридцать цветов для вершин
// первый цвет - цвет фона вершины
// второй цвет - цвет текста вершины
const distinctColors = [
  ["#FF0000", "#FFFFFF"], // Красный → Белый
  ["#00FF00", "#000000"], // Ярко-зелёный → Чёрный
  ["#0000FF", "#FFFFFF"], // Синий → Белый
  ["#FFFF00", "#000000"], // Жёлтый → Чёрный
  ["#FF00FF", "#000000"], // Пурпурный → Чёрный
  ["#00FFFF", "#000000"], // Голубой → Чёрный
  ["#FF8000", "#000000"], // Оранжевый → Чёрный
  ["#8000FF", "#FFFFFF"], // Фиолетовый → Белый
  ["#008000", "#FFFFFF"], // Тёмно-зелёный → Белый
  ["#FF0080", "#FFFFFF"], // Розово-малиновый → Белый
  ["#00FF80", "#000000"], // Изумрудный → Чёрный
  ["#800000", "#FFFFFF"], // Тёмно-красный → Белый
  ["#008080", "#FFFFFF"], // Бирюзовый → Белый
  ["#808000", "#FFFFFF"], // Оливковый → Белый
  ["#000080", "#FFFFFF"], // Тёмно-синий → Белый
  ["#FF6347", "#000000"], // Томатный → Чёрный
  ["#7CFC00", "#000000"], // Травяной → Чёрный
  ["#9400D3", "#FFFFFF"], // Тёмно-фиолетовый → Белый
  ["#FFD700", "#000000"], // Золотой → Чёрный
  ["#4B0082", "#FFFFFF"], // Индиго → Белый
  ["#FF69B4", "#000000"], // Ярко-розовый → Чёрный
  ["#00CED1", "#000000"], // Бирюзово-голубой → Чёрный
  ["#32CD32", "#000000"], // Лаймовый → Чёрный
  ["#8A2BE2", "#FFFFFF"], // Сине-фиолетовый → Белый
  ["#DC143C", "#FFFFFF"], // Малиновый → Белый
  ["#20B2AA", "#000000"], // Светло-морской → Чёрный
  ["#FF4500", "#FFFFFF"], // Красно-оранжевый → Белый
  ["#6A5ACD", "#FFFFFF"], // Сланцевый → Белый
  ["#FFA500", "#000000"], // Классический оранжевый → Чёрный
  ["#2E8B57", "#FFFFFF"]  // Морской зелёный → Белый
];


// функция для очистки Canvas-а
function clean_canvas(canvas_gd, ctx, clean_graph) {    // clean_graph - 1 - очистка, 0 - оставляем как есть
    // CLEANING
    ctx.fillStyle = Qt.rgba(0.007, 0.03, 0.03, 1);
    console.log("WIDTH, HEIGHT", canvas_gd.width, canvas_gd.height)
    ctx.setTransform(1, 0, 0, 1, 0, 0);     // сбрасываем масштаб до изначального
    ctx.fillRect(0, 0, canvas_gd.width, canvas_gd.height);  // очищаем canvas
    ctx.scale(k_scale, k_scale);    // возвращаем масштаб
    GRAPH = (clean_graph ? null : GRAPH);       // очищаем граф
    canvas_gd.requestPaint();  // Важно для обновления
}


// граф в переменной graph всегда ПРАВИЛЬНЫЙ
// canvas_gd - объект Canvas для рисования графа
function draw_graph(graph, canvas_gd, ctx) {

    // очищаем Canvas
    clean_canvas(canvas_gd, ctx, 1)

    GRAPH = graph;  // обозначаем, что на экране сейчас находится граф

    // DRAWING
    // рисуем graph

    ctx.strokeStyle = EDGE_COLOR;            // set the color for the circle to 'green'
    ctx.lineWidth = EDGE_WIDTH;              // set the lineWidth for the circle to 5.0


    // рисуем ребра
    for (let e in graph["edges"]) {
        let edge = graph["edges"][e]
        let v1 = edge[0];
        let v2 = edge[1];
        let w = edge[2];
        let x1 = graph["vertices"][v1][0];
        let y1 = graph["vertices"][v1][1];
        let x2 = graph["vertices"][v2][0];
        let y2 = graph["vertices"][v2][1]

        // рисуем ребро
        ctx.beginPath();
        ctx.moveTo(x1, y1);
        ctx.lineTo(x2, y2);
        ctx.stroke();
        ctx.closePath();
    }

    // рисуем вершины
    for (let v in graph["vertices"]) {
        let x = graph["vertices"][v][0];
        let y = graph["vertices"][v][1];
        let color = graph["colors"][v];      // номер цвета вершины

        // рисуем круг
        ctx.beginPath();
        ctx.fillStyle = distinctColors[color][0];
        ctx.strokeStyle = 'green';
        ctx.arc(x, y, RADIUS, 0, 2 * Math.PI);  // a circle with center point (100,100) and radius RADIUS
        ctx.stroke();                           // draw the path; in this case only the circle
        ctx.fill();
        ctx.closePath();

        // рисуем имя вершины
        ctx.beginPath();
        ctx.font = "19pt serif";
        ctx.fillStyle = distinctColors[color][1];
        let text_m = ctx.measureText(v);
        ctx.fillText(v, x - text_m.width / 2, y + text_m.width / 2);
        ctx.closePath();
    }


    // рисуем веса
    for (let e1 in graph["edges"]) {
        let edge = graph["edges"][e1]
        let v1 = edge[0];
        let v2 = edge[1];
        let w = edge[2];
        let x1 = graph["vertices"][v1][0];
        let y1 = graph["vertices"][v1][1];
        let x2 = graph["vertices"][v2][0];
        let y2 = graph["vertices"][v2][1];
        let text_m = ctx.measureText(w);

        // рисование веса
        ctx.beginPath();
        ctx.font = "19pt serif";
        ctx.fillStyle = 'red';
        ctx.fillText(w,
                     (x1 + x2 - text_m.width) / 2,
                     (y1 + y2) / 2,
                     );
        ctx.closePath();
    }


    ctx.strokeStyle = 'white'
    ctx.strokeRect(0, 0, canvas_gd.width, canvas_gd.height)
    ctx.closePath()

    // UPDATING
    canvas_gd.requestPaint();  // Важно для обновления
}

// изменение масштаба графа
// при это нужно делать так, чтобы Canvas всегда находится по центру своей области
function scale_canvas(scale, canvas_gd, ctx) {
    if (GRAPH != null) {
        // EDGE_WIDTH = EDGE_WIDTH * scale;
        // RADIUS = RADIUS * scale;
        k_scale *= scale;        // домножаем на множитель scale коэффициент масштабирования
        clean_canvas(canvas_gd, ctx, 0) // просто очищаем Canvas, но оставляем GRAPH
        draw_graph(GRAPH, canvas_gd, ctx);
        console.log("HELLO I AM SCALED CANVAS, my scale equals", scale)
    }
}

