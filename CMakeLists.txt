cmake_minimum_required(VERSION 4.0)
#Student CMakeLists
project(Student)

file(GLOB SRC ${PROJECT_SOURCE_DIR}/src/*.cpp)

include_directories(${PROJECT_SOURCE_DIR}/include)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# 完全静态链接
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libgcc -static-libstdc++")

link_directories(${PROJECT_SOURCE_DIR}/sqlite/bin ${PROJECT_SOURCE_DIR}/lib)

add_executable(Student ${SRC})

target_link_libraries(Student SQLite3Cpp_lib sqlite3_lib)