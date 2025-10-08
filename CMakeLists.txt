cmake_minimum_required(VERSION 3.12.4)
project(LogAnalyzer VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(LogAnalyzer 
    src/main.cpp
    src/LogAnalyzer.cpp
    src/log_line_parser.cpp
    src/LogEntry.h
    src/LogAnalyzer.h
    src/log_line_parser.h
)

target_include_directories(LogAnalyzer PUBLIC src)