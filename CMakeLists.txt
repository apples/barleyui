cmake_minimum_required (VERSION 3.0)
project(BarleyUI)

file(GLOB_RECURSE BARLEYUI_SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp ${PROJECT_SOURCE_DIR}/src/*.hpp)
add_library(barleyui ${BARLEYUI_SOURCES})
set_property(TARGET barleyui PROPERTY CXX_STANDARD 14)
target_include_directories(barleyui INTERFACE ${PROJECT_SOURCE_DIR}/src)
target_link_libraries(barleyui pangomm fconfig raspberry sushi)
