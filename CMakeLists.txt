cmake_minimum_required(VERSION 3.29)
project(BattleC)

set(CMAKE_CXX_STANDARD 20)

add_executable(BattleC main.cpp
        Board.cpp
        Board.h
        Ship.h
        Player.cpp
        Player.h
        GridSpace.h
        global.h
        Strategy.cpp
        Strategy.h)
