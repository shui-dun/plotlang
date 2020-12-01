add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/scanner)

aux_source_directory(${PROJECT_SOURCE_DIR}/src SRC_LIST)
add_executable(main ${SRC_LIST})
target_link_libraries(main scanner)