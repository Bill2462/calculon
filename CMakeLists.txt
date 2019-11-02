#  This file is part of measurements laboratory excercise solution.
#  Copyright (c) 2019 Krzysztof Adamkiewicz <kadamkiewicz835@gmail.com>
# 
#  Permission is hereby granted, free of charge, to any person obtaining a copy of
#  this software and associated documentation files (the “Software”), to deal in the
#  Software without restriction, including without limitation the rights to use, copy,
#  modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
#  and to permit persons to whom the Software is furnished to do so, subject to the
#  following conditions: THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND,
#  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
#  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
#  THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
#  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
#  OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. 

cmake_minimum_required(VERSION 3.1)

project(me_magic)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic -pthread")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON) 

include_directories(utils)
include_directories(filters)

set(SOURCES
    main.cpp
    utils/stopwatch.cpp
    utils/files.cpp
    utils/cnpy/cnpy.cpp
    filters/apply.cpp
    filters/filters.cpp
)

add_executable(magic ${SOURCES})
target_link_libraries(magic z)
