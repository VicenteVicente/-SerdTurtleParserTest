cmake_minimum_required(VERSION 3.10)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(EXECUTABLE_OUTPUT_PATH bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY bin)

# set the project name and version
project(Serd VERSION 0.1)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wextra -pedantic -O0 -g3 -pthread -march=native -funroll-loops -fsanitize=undefined -fno-omit-frame-pointer -fsanitize=address")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -Wextra -pedantic -O3 -g0 -pthread -march=native -funroll-loops")

include_directories(${CMAKE_SOURCE_DIR}/src)

file(GLOB_RECURSE SRCS src/*.cc)

set(sources ${SRCS})
list(REMOVE_ITEM sources ${CMAKE_CURRENT_SOURCE_DIR}/src/bin/*)
add_library(serd STATIC ${sources})

set(BUILD_TARGETS main)

foreach(target ${BUILD_TARGETS})
    add_executable(${target} ${CMAKE_SOURCE_DIR}/src/bin/${target}.cc)
    target_link_libraries(${target} serd)
endforeach(target)

# cmake -Bbuild/Release -DCMAKE_BUILD_TYPE=Release && cmake --build build/Release/