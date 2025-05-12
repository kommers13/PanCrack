.pragma library

function clear(column) {
    // Команда CLEAR (только эту команду мы выполняем после всего, она РЕДАКТИРУЕТ консоль)
    // console.log("COMMAND CLEAR")
    // console.log("BEFORE COLUMN.Y", column.y)
    for (let i = column.children.length - 1; i >= 1; i--) {
        if (column.children[i] !== column) {
            column.children[i].destroy()
        }
    }
    // поднимаемся до конца наверх
    column.y = 25       // начальное значение column.y
}


