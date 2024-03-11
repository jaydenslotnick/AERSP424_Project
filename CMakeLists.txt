cmake_minimum_required(VERSION 3.23)
project(Fantasy_Football_Mock_Draft_Simulator)
set(CMAKE_CXX_STANDARD 20)
add_executable(main main.cpp Ranking.h League.h Draft.h CustomLeague.h)
