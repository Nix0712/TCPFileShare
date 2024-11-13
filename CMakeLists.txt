cmake_minimum_required(VERSION 3.30.5)
project(TCPShare
    VERSION 1.0
    DESCRIPTION "Simple TCP server and client for sharing files"
    LANGUAGES CXX)


add_executable(TCPShare-Client src/Client/client.cpp)
add_executable(TCPShare-Server src/Server/server.cpp)
target_include_directories(TCPShare-Client PRIVATE ./libs)
target_include_directories(TCPShare-Server PRIVATE ./libs)
