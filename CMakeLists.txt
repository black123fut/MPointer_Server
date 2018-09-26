cmake_minimum_required(VERSION 3.12)
project(MPointer_Server)

include_directories(${MY_SOURCE_DIR} /home/isaac/Downloads/rapidjson-master/include)
set(CMAKE_CXX_STANDARD 11)
SET(CMAKE_CXX_FLAGS -pthread)

add_executable(MPointer_Server main.cpp DataStructures/LinkedList.cpp MPointer.cpp MPointer.h MPointerGC.h Mapa_Memoria.cpp Mapa_Memoria.h Server/Server.cpp Server/Server.h)