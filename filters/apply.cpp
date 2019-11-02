/**
 * @file apply.cpp
 * @brief This source file contains code for applying filter to the signal.
 * @author Krzysztof Adamkiewicz
 * @date 1/10/2019
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

#include "filters.hpp"
#include <thread>
#include <algorithm>

/**
 * @brief Aply filter to the signal
 * @param signal Input signal.
 * @param threadCount Number of threads on which the filter will run.
 * @param filter Filter function.
 * @param params Filter parameters.
 */
void applyFilter(std::vector<double>& signal, unsigned int threadCount, Filter filter, const std::vector<FilterParameter>& params)
{
    //validate thread count
    if(threadCount < 1)
        threadCount = 1;
    
    //choose block size
    const size_t batchSize = signal.size()/threadCount;
    
    //build worker pool
    std::vector<std::thread> workers(threadCount);//worker pool
    
    //worker
    auto worker = [&params, &filter](auto begin_it, auto end_it){ filter(begin_it, end_it, params); };
    
    //start workers
    auto it = std::begin(signal);
    for(unsigned int i=0; i<threadCount; i++)
    {
        workers[i] = std::thread(worker, it, std::next(it, batchSize));
        std::advance(it, batchSize);
    }
    
    //wait for workers to finish
    std::for_each(std::begin(workers), std::end(workers), [](std::thread& thread){ thread.join(); });
}
