aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/semantics SEMANTICS_SRC_LIST)

find_package(BISON)
BISON_TARGET(myParser ${CMAKE_CURRENT_SOURCE_DIR}/parser/parser.y
        ${CMAKE_CURRENT_SOURCE_DIR}/parser/parser.c
        DEFINES_FILE ${PROJECT_SOURCE_DIR}/include/parser.h
        )
add_library(parser SHARED ${BISON_myParser_OUTPUTS} ${SEMANTICS_SRC_LIST})
find_package(PNG REQUIRED)
include_directories(${PNG_INCLUDE_DIR})
target_link_libraries(parser ${PNG_LIBRARY})

find_package(FLEX)
FLEX_TARGET(myScanner ${CMAKE_CURRENT_SOURCE_DIR}/scanner/scanner.l
        ${CMAKE_CURRENT_SOURCE_DIR}/scanner/scanner.c)
add_library(scanner SHARED ${FLEX_myScanner_OUTPUTS})
target_link_libraries(parser m)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SRC_LIST)
add_executable(plotlang ${SRC_LIST})
target_link_libraries(plotlang scanner parser)
