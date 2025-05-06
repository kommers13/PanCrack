# директория, где хранятся данные о командах
set(COMINF_SRC_DIR ${CMAKE_SOURCE_DIR}/App/cominf)
set(COMINF_BNR_DIR ${CMAKE_BINARY_DIR}/cominf)

file(MAKE_DIRECTORY ${COMINF_BNR_DIR})

add_custom_command(
    TARGET ${CMAKE_PROJECT_NAME}
    COMMAND ${CMAKE_COMMAND} -E copy
        "${COMINF_SRC_DIR}/clear.json"
        "${COMINF_SRC_DIR}/create.json"
        "${COMINF_BNR_DIR}"
    COMMENT "Копирование данных команд в json-файлах"
)
