/**
 * @file stopwatch.hpp
 * @brief This source file contains code for the stopwatch.
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

#include "utils.hpp"

/**
 * @brief Reset the clock.
 */
void StopWatch::reset()
{
    stopPoint = startPoint;
}

/**
 * @brief Start the clock.
 */
void StopWatch::start()
{
    if(running) //do not start the clock for the second time
        return;

    startPoint = std::chrono::high_resolution_clock::now();
    stopPoint  = std::chrono::high_resolution_clock::now();
    running = true;
}

/**
 * @brief Stop the clock.
 */
void StopWatch::stop()
{
    if(!running) //do not stop the clock for the second time
        return;
    
    stopPoint = std::chrono::high_resolution_clock::now();
    running = false;
}

/**
 * @brief Get the value of the clock.
 * @return Reading of a stopwatch.
 */
long double StopWatch::getTime() const
{
    return (std::chrono::duration_cast<std::chrono::duration<double>>(stopPoint - startPoint)).count();
}

/**
 * @brief Check if clock is running.
 * @return True if clock is running.
 */
bool StopWatch::isRunning() const
{
    return running;
}
