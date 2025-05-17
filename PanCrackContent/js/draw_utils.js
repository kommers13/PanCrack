.pragma library



// в функцию передается число
// она вычисляет RGB цвет для этого числа
function get_color(color_number) {

}

// граф в переменной graph всегда ПРАВИЛЬНЫЙ
// canvas_gd - объект Canvas для рисования графа
function draw_graph(graph, canvas_gd) {

    let ctx = canvas_gd.getContext("2d");

    // CLEANING
    // перед тем как рисовать, мы должны очистить Canvas
    ctx.fillStyle = Qt.rgba(0.007, 0.03, 0.03, 1);
    ctx.fillRect(0, 0, canvas_gd.width, canvas_gd.height);

    // DRAWING
    // рисуем graph
    // ...

    ctx.strokeStyle = '#00FF00';        // set the color for the circle to 'green'
    ctx.fillStyle = '#FF0000';
    ctx.lineWidth = 5.0;              // set the lineWidth for the circle to 5.0


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

        // рисуем вес
        ctx.beginPath();
        ctx.font = "19pt serif";
        let text_m = ctx.measureText(w);
        ctx.fillStyle = 'blue';
        //ctx.fillRect(10, 10, 20, 20);       // ДОДЕЛАТЬ
        ctx.fillStyle = 'red';
        ctx.fillText(w,
                     (x1 + x2 - text_m.width) / 2,
                     (y1 + y2) / 2,
                     );
        ctx.closePath();
    }

    // рисуем вершины
    for (let v in graph["vertices"]) {
        let x = graph["vertices"][v][0];
        let y = graph["vertices"][v][1];
        // рисуем круг
        ctx.beginPath();
        ctx.fillStyle = 'red';
        ctx.strokeStyle = 'green';
        ctx.arc(x, y, 25, 0, 2 * Math.PI);  // a circle with center point (100,100) and radius 80
        ctx.stroke();                     // draw the path; in this case only the circle
        ctx.fill();
        ctx.closePath();

        // рисуем имя вершины
        ctx.beginPath();
        ctx.fillStyle = 'blue';
        let text_m = ctx.measureText(v);
        console.log("text_m: ", text_m.width / 2);
        ctx.fillText(v, x - text_m.width / 2, y + text_m.width / 2);
        ctx.closePath();
    }

    // UPDATING
    canvas_gd.requestPaint();  // Важно для обновления
}

