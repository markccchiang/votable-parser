cmake_minimum_required(VERSION 3.5)
project(votable-parser)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_INCLUDE_DIRECTORIES_BEFORE ON)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

# Needed by clang-tidy and other clang tools
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(LibXml2 REQUIRED)

message(STATUS LIBXML2_FOUND = ${LIBXML2_FOUND})

include_directories(${LIBXML2_INCLUDE_DIR})

set(LINK_LIBS ${LINK_LIBS} ${LIBXML2_LIBRARIES})

set(SOURCE_FILES ${SOURCE_FILES}
        VOTableParser.cc
        VOTableCarrier.cc
        VOTableController.cc)

add_executable(test-votable-parser tests/TestVOTableParser.cc ${SOURCE_FILES})
target_link_libraries(test-votable-parser ${LINK_LIBS})

add_executable(test-votable-controller tests/TestVOTableController.cc ${SOURCE_FILES})
target_link_libraries(test-votable-controller ${LINK_LIBS})
