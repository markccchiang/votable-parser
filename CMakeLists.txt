cmake_minimum_required(VERSION 3.5)
project(votable-parser)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_INCLUDE_DIRECTORIES_BEFORE ON)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

# Needed by clang-tidy and other clang tools
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

FIND_PACKAGE(libxml2 REQUIRED)

#INCLUDE_DIRECTORIES(/usr/local/include)
#LINK_DIRECTORIES(/usr/local/lib)
INCLUDE_DIRECTORIES(/usr/local/opt/libxml2/include/libxml2)
#LINK_DIRECTORIES(/usr/local/opt/libxml2/lib)

set(LINK_LIBS ${LINK_LIBS} xml2)

set(SOURCE_FILES ${SOURCE_FILES}
        VOTableParser.cc
        VOTableCarrier.cc
        VOTableController.cc)

add_executable(votable-tester VOTableTester.cc ${SOURCE_FILES})
target_link_libraries(votable-tester ${LINK_LIBS})

add_executable(catalog-tester CatalogTester.cc ${SOURCE_FILES})
target_link_libraries(catalog-tester ${LINK_LIBS})
