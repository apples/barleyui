cmake_minimum_required (VERSION 3.0)
project(BarleyUI)

find_package(pkgconfig REQUIRED)

function(add_pkgconfig_library NAME LIBNAMES)
    pkg_search_module(${NAME} REQUIRED ${LIBNAMES})
    add_library(${NAME} INTERFACE)
    target_link_libraries(${NAME} INTERFACE ${${NAME}_LIBRARIES})
    target_include_directories(${NAME} INTERFACE ${${NAME}_INCLUDE_DIRS})
    target_compile_options(${NAME} INTERFACE ${${NAME}_CFLAGS_OTHER})
endfunction()

add_pkgconfig_library(pangomm "pangomm-1.4 pangocairo pangoft2")
add_pkgconfig_library(fconfig fontconfig)

file(GLOB_RECURSE BARLEYUI_SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp ${PROJECT_SOURCE_DIR}/src/*.hpp)
add_library(barleyui ${BARLEYUI_SOURCES})
set_property(TARGET barleyui PROPERTY CXX_STANDARD 14)
target_include_directories(barleyui INTERFACE ${PROJECT_SOURCE_DIR}/src)
target_link_libraries(barleyui pangomm fconfig raspberry sushi)
