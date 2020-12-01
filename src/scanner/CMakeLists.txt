aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SCANNER_SRC_LIST)
add_library(scanner SHARED ${SCANNER_SRC_LIST})