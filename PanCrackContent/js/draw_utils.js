.pragma library

// граф в переменной graph всегда ПРАВИЛЬНЫЙ
// canvas_gd - объект Canvas для рисования графа
function draw_graph(graph, canvas_gd) {
    // CLEANING
    // перед тем как рисовать, мы должны очистить Canvas
    // ...
    // DRAWING
    // рисуем graph
    // ...

    for (let v1 in graph["graph"]) {
        let v2 = graph["graph"][v1][0];
        let w = graph["graph"][v1][1];
        console.log(v1, v2, w)
    }

    for (let v in graph["namevs"]) {
        console.log(v)
    }

    let ctx = canvas_gd.getContext("2d");
    ctx.fillStyle = Qt.rgba(1, 0, 0, 1);
    ctx.fillRect(0, 0, canvas_gd.width, canvas_gd.height);

    // UPDATING
    canvas_gd.requestPaint();  // Важно для обновления
}

