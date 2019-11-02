/**
 * @file utils.hpp
 * @brief This header file contains declarations of support functions.
 * @author Krzysztof Adamkiewicz
 * @date 31/9/2019
 */

// This file is part of measurements laboratory excercise solution.
// Copyright (c) 2019 Krzysztof Adamkiewicz <kadamkiewicz835@gmail.com>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of
// this software and associated documentation files (the “Software”), to deal in the
// Software without restriction, including without limitation the rights to use, copy,
// modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
// and to permit persons to whom the Software is furnished to do so, subject to the
// following conditions: THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
// THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
// OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. 

#ifndef UTILS_HPP_INCLUDED
#define UTILS_HPP_INCLUDED

#include <chrono>
#include <vector>
#include <string>

/**
 * @brief Stopwatch class.
 */
class StopWatch
{
public:
    void reset();
    void start();
    void stop();
    long double getTime() const;
    bool isRunning() const;

private:
    std::chrono::high_resolution_clock::time_point startPoint;
    std::chrono::high_resolution_clock::time_point stopPoint;
    bool running = false;
};

std::vector<double> loadSignal(const std::string& fileName);
void saveSignal(const std::vector<double>& signal, const std::string& fileName);


#endif
