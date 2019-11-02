/**
 * @file filters.cpp
 * @brief This source file contains code for filter functions.
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
#include <algorithm>
#include <numeric>
#include <iterator>
#include <functional>

class NotFound final : public std::exception{};

/**
 * @brief Find the parameter in the parameter name.
 * @param paramName Parameter name.
 * @param params Parameters array.
 * @return Parameter value.
 * @throw NotFound If parameter is not on the list.
 */
inline double findParameter(const std::string& paramName, const std::vector<FilterParameter>& params)
{
    auto found = std::find_if(params.begin(), params.end(), [paramName](const FilterParameter& x) -> bool { return x.name == paramName; });
    
    if(found == params.end())
        throw(NotFound());
    
    return (*found).value;
}

/**
 * @brief Moving average filter. Will apply filter between < rangeStart, rangeEnd ),
 * @param rangeStart Start the signal.
 * @param rangeEnd End of the signal.
 * @param params Parameters.
 * @throw MissingParameter If required parameters are not provided.
 */
void movingAverage_filter(std::vector<double>::iterator rangeStart, std::vector<double>::iterator rangeEnd, const std::vector<FilterParameter>& params)
{
    size_t blockSize;
    try
    {
        blockSize = findParameter("block-size", params);
    }
    catch(NotFound& err)
    {
        throw(MissingParameter("Missing block-size parameter!"));
    }

    for(auto it=std::next(rangeStart, blockSize-1); it<rangeEnd; std::advance(it, 1))
    {
        *it = std::accumulate(std::prev(it, blockSize-1), it+1, 0.0)/blockSize;
    }
}

/**
 * @brief Moving average filter. Will apply filter between < rangeStart, rangeEnd),
 * @param rangeStart Start the signal.
 * @param rangeEnd End of the signal.
 * @param params Parameters.
 * @throw MissingParameter If required parameters are not provided.
 */
void exponential_filter(std::vector<double>::iterator rangeStart, std::vector<double>::iterator rangeEnd, const std::vector<FilterParameter>& params)
{
    double a;
    try
    {
        a = findParameter("damping-coeff", params);
    }
    catch(NotFound& err)
    {
        throw(MissingParameter("Missing damping-coeff parameter!"));
    }
    
    double memory = (1-a)*(*rangeStart);
    for(auto it = std::next(rangeStart, 1); it<rangeEnd; std::advance(it, 1))
    {
        *it = (a*(*it)) + memory;
        memory = (1-a)*(*it);
    }
}

/**
 * @brief Moving average filter. Will apply filter between < rangeStart, rangeEnd),
 * @param rangeStart Start the signal.
 * @param rangeEnd End of the signal.
 * @param params Parameters.
 * @throw MissingParameter If required parameters are not provided.
 */
void median_filter(std::vector<double>::iterator rangeStart, std::vector<double>::iterator rangeEnd, const std::vector<FilterParameter>& params)
{
    size_t blockSize;
    try
    {
        blockSize = findParameter("block-size", params);
    }
    catch(NotFound& err)
    {
        throw(MissingParameter("Missing block-size parameter!"));
    }
    
    std::vector<double> sortBuffer(blockSize);
    bool isOdd = blockSize%2;
    for(auto it = rangeStart; it<std::prev(rangeEnd, blockSize); std::advance(it, 1))
    {
        std::copy(it, std::next(it, blockSize-1), std::begin(sortBuffer));
        std::sort(std::begin(sortBuffer), std::end(sortBuffer));
        if(isOdd)
           *it = sortBuffer[(blockSize/2)+1];
        else
            *it = ((sortBuffer[(blockSize/2)]) + (sortBuffer[(blockSize/2)+1]))/2;
    }
}
