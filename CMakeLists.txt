cmake_minimum_required(VERSION 3.6)
project(lmdb)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES src/domain/movie.cpp src/utils/vector.h src/controller/movie_controller.cpp)
add_executable(lmdb main.cpp ${SOURCE_FILES} src/ui/adminconsole.cpp src/ui/console.cpp src/ui/userconsole.cpp src/ui/userconsole.h)
add_executable(lmdbtests tests/mainTests.cpp ${SOURCE_FILES})