cmake_minimum_required(VERSION 3.27)
project(Projet_Qualite_Prog_master)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Projet_Qualite_Prog_master
        Terrain.cpp
        Terrain.h
        main.cpp)
