cmake_minimum_required(VERSION 3.8)
project(BattleForOlympia)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c Map.h Unit.h boolean.h Point/Point.c Point/Point.h User.h)
add_executable(BattleForOlympia ${SOURCE_FILES})