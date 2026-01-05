cmake_minimum_required(VERSION 3.10)
project(Podciag_P02_MD)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

set(SOURCES src/main.cpp)

add_executable(P02_Mateusz_Dzialowski ${SOURCES})

find_package(Threads REQUIRED)
target_link_libraries(P02_Mateusz_Dzialowski PRIVATE Threads::Threads)