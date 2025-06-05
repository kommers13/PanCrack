# директория, где хранятся данные о командах
set(COMINF_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/App/cominf)
set(COMINF_BNR_DIR ${CMAKE_CURRENT_BINARY_DIR}/cominf)

# директория, где хранятся данные о графах
# нужно только создать папку в директории, где будут бинарники
set(GRAPH_BNR_DIR ${CMAKE_CURRENT_BINARY_DIR}/graphs)

file(MAKE_DIRECTORY ${COMINF_BNR_DIR})
file(MAKE_DIRECTORY ${GRAPH_BNR_DIR})


add_custom_target(copy_jsons ALL
    # COMMAND "D:/PanCrack/utils/constrcom.exe" ${COMINF_SRC_DIR}
    COMMAND ${CMAKE_COMMAND} -E make_directory ${COMINF_BNR_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy
        "${COMINF_SRC_DIR}/clear.json"
        "${COMINF_SRC_DIR}/create.json"
        "${COMINF_SRC_DIR}/draw.json"
        "${COMINF_SRC_DIR}/show.json"
        "${COMINF_SRC_DIR}/view.json"
        "${COMINF_SRC_DIR}/algorithm.json"
        "${COMINF_SRC_DIR}/check.json"
        "${COMINF_SRC_DIR}/help.json"
        "${COMINF_SRC_DIR}/prufer.json"
        "${COMINF_SRC_DIR}/view.json"
        "${COMINF_SRC_DIR}/color.json"
        "${COMINF_BNR_DIR}/"
    DEPENDS ${CMAKE_PROJECT_NAME}
)
