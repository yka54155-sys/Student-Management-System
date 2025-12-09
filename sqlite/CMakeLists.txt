cmake_minimum_required(VERSION 4.0)
project(SQLite3Cpp)
link_directories(${PROJECT_SOURCE_DIR}/sqlite_lib)

set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
add_library(SQLite3Cpp_lib STATIC ${PROJECT_SOURCE_DIR}/src/sqlite3cpp.cpp)

add_library(SQLite3Cpp_dll SHARED ${PROJECT_SOURCE_DIR}/src/sqlite3cpp.cpp)
target_link_libraries(SQLite3Cpp_dll sqlite3_lib)
target_link_libraries(SQLite3Cpp_lib sqlite3_lib)

