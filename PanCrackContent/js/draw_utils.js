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

    for (let v1 in graph["graph"]) {
        let v2 = graph["graph"][v1][0];
        let w = graph["graph"][v1][1];
        console.log(v1, v2, w)
    }

    for (let v in graph["namevs"]) {
        console.log(v)
    }

    ctx.strokeStyle = 'green';        // set the color for the circle to 'green'
    ctx.lineWidth = 5.0;              // set the lineWidth for the circle to 5.0
    // ctx.beginPath();                  // start a new path
    ctx.arc (100,100,80,0,2*Math.PI); // a circle with center point (100,100) and radius 80
    ctx.stroke();                     // draw the path; in this case only the circle

    // UPDATING
    canvas_gd.requestPaint();  // Важно для обновления
}

