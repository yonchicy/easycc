cmake_minimum_required(VERSION 3.22)

PROJECT(easycc)


MESSAGE("cmake source dir is ${CMAKE_SOURCE_DIR}")

FIND_PACKAGE(BISON REQUIRED)
SET(BISONOUTPUT ${CMAKE_SOURCE_DIR}/src/frontend/parser.cpp)

IF(BISON_FOUND)
    ADD_CUSTOM_COMMAND(
      OUTPUT ${BISONOUTPUT}
      COMMAND ${BISON_EXECUTABLE}
              --defines=${CMAKE_SOURCE_DIR}/src/frontend/parser.h
              --output=${BISONOUTPUT}
              ${CMAKE_SOURCE_DIR}/src/frontend/parser.y
      COMMENT "Generating parser.cpp"
    )
ENDIF()

FIND_PACKAGE(FLEX REQUIRED)
SET(FLEXOUTPUT ${CMAKE_SOURCE_DIR}/src/frontend/token.cpp)
IF(FLEX_FOUND)
    ADD_CUSTOM_COMMAND(
      OUTPUT ${FLEXOUTPUT}
      COMMAND ${FLEX_EXECUTABLE}
              --outfile=${FLEXOUTPUT}
              ${CMAKE_SOURCE_DIR}/src/frontend/token.l
      COMMENT "Generating scanner.cpp"
    )
ENDIF()

file(GLOB_RECURSE source_files ${CMAKE_SOURCE_DIR} "src/*.cpp")

message("source is ${source_files}")
include_directories(${PROJECT_SOURCE_DIR}/include)


add_executable(${PROJECT_NAME} ${source_files} ${BISONOUTPUT} ${FLEXOUTPUT})

