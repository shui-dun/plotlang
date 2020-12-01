aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SCANNER_TEST)
add_executable(scannerTest ${SCANNER_TEST})
target_link_libraries(scannerTest scanner)