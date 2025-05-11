# директория, где хранятся данные о командах
set(COMINF_SRC_DIR ${CMAKE_SOURCE_DIR}/App/cominf)
set(COMINF_BNR_DIR ${CMAKE_BINARY_DIR}/cominf)

# директория, где хранятся данные о графах
# нужно только создать папку в директории, где будут бинарники
set(GRAPH_BNR_DIR ${CMAKE_BINARY_DIR}/graphs)

file(MAKE_DIRECTORY ${COMINF_BNR_DIR})
file(MAKE_DIRECTORY ${GRAPH_BNR_DIR})

add_custom_command(
    TARGET ${CMAKE_PROJECT_NAME}
    COMMAND ${CMAKE_COMMAND} -E copy
        "${COMINF_SRC_DIR}/clear.json"
        "${COMINF_SRC_DIR}/create.json"
        "${COMINF_SRC_DIR}/draw.json"
        "${COMINF_SRC_DIR}/show.json"
        "${COMINF_BNR_DIR}/"
    COMMENT "Копирование данных команд в json-файлах"
)
