aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/parser PARSER_TEST)
add_executable(parserTest ${PARSER_TEST})
target_link_libraries(parserTest scanner parser)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/scanner SCANNER_TEST)
add_executable(scannerTest ${SCANNER_TEST})
target_link_libraries(scannerTest scanner parser)