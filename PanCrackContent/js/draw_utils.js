.pragma library



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

    ctx.strokeStyle = 'green';        // set the color for the circle to 'green'
    ctx.fillStyle = 'red';
    ctx.lineWidth = 5.0;              // set the lineWidth for the circle to 5.0


    // ДУБЛИРУЮТСЯ РЕБРА
    for (let e in graph["edges"]) {
        let edge = graph["edges"][e]
        let v1 = edge[0];
        let v2 = edge[1];
        let w = edge[2];
        // рисуем ребро
        ctx.beginPath();
        ctx.moveTo(graph["vertices"][v1][0], graph["vertices"][v1][1]);
        ctx.lineTo(graph["vertices"][v2][0], graph["vertices"][v2][1]);
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
                     (graph["vertices"][v1][0] + graph["vertices"][v2][0] - text_m.width) / 2,
                     (graph["vertices"][v1][1] + graph["vertices"][v2][1]) / 2,
                     );
        ctx.closePath();
    }

    for (let v in graph["vertices"]) {
        let x = graph["vertices"][v][0];
        let y = graph["vertices"][v][1];
        ctx.beginPath();
        ctx.arc(x, y, 25, 0, 2 * Math.PI);  // a circle with center point (100,100) and radius 80
        ctx.stroke();                     // draw the path; in this case only the circle
        ctx.fill();
        ctx.closePath();
    }

    // UPDATING
    canvas_gd.requestPaint();  // Важно для обновления
}

