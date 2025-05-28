.pragma library

const RADIUS = 18;
const EDGE_WIDTH = 2.5;
const GLOW_COLOR = "#00FF41";
const ERROR_COLOR = "#FF0033";

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

const edgeStyles = [
    {color: "#00FF41", width: 2.5}, // Основной хакерский
    {color: "#FF0033", width: 2.5}, // Вирусный
    {color: "#FF6600", width: 2.0}, // Оранжевый угроза
    {color: "#9900FF", width: 2.0}, // Фиолетовый взлом
    {color: "#00CCFF", width: 1.8}  // Голубой сигнал
];

function draw_graph(graph, canvas_gd) {
    let ctx = canvas_gd.getContext("2d");

    // Очистка canvas - темный фон с едва заметным паттерном
    ctx.fillStyle = "#000B0B";
    ctx.fillRect(0, 0, canvas_gd.width, canvas_gd.height);

    // Добавляем едва заметный сетчатый паттерн
    ctx.strokeStyle = "#001010";
    ctx.lineWidth = 0.5;
    for (let x = 0; x < canvas_gd.width; x += 20) {
        ctx.beginPath();
        ctx.moveTo(x, 0);
        ctx.lineTo(x, canvas_gd.height);
        ctx.stroke();
    }
    for (let y = 0; y < canvas_gd.height; y += 20) {
        ctx.beginPath();
        ctx.moveTo(0, y);
        ctx.lineTo(canvas_gd.width, y);
        ctx.stroke();
    }

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
        ctx.lineWidth = style.width;
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
        ctx.strokeStyle = fillColor; // Обводка того же цвета, что и заливка
        ctx.lineWidth = 2.5;
        ctx.fill();
        ctx.stroke();
        ctx.closePath();

        // Внутренняя темная обводка (цвет текста)
        ctx.beginPath();
        ctx.arc(x, y, RADIUS-1, 0, 2 * Math.PI);
        ctx.strokeStyle = textColor;
        ctx.lineWidth = 1.5;
        ctx.stroke();
        ctx.closePath();

        // Текст вершины
        ctx.beginPath();
        ctx.font = "bold 16px 'Courier New', monospace";
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
        ctx.font = "bold 14px 'Courier New', monospace";
        let textWidth = ctx.measureText(w).width;
        ctx.fillStyle = "#000000";
        ctx.fillRect(midX - textWidth/2 - 2, midY - 10, textWidth + 4, 20);
        ctx.closePath();

        // Текст веса цветом ребра
        ctx.beginPath();
        ctx.fillStyle = edgeStyles[e % edgeStyles.length].color;
        ctx.textAlign = "center";
        ctx.textBaseline = "middle";
        ctx.fillText(w, midX, midY);
        ctx.closePath();
    }

    canvas_gd.requestPaint();
}
