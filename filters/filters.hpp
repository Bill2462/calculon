/**
 * @file filters.hpp
 * @brief This header file contains declarations of filer class.
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

#ifndef FILTERS_HPP_INCLUDED
#define FILTERS_HPP_INCLUDED 

#include <functional>
#include <vector>
#include <exception>

/** 
 * @brief Missing parameter. Thrown
 * when filter has missing parameters.
 */ 
class MissingParameter final : public std::exception
{
public:
    explicit MissingParameter(const char* message_) noexcept: 
    message(message_){}

    const char* what() const noexcept override
    {
        return message; 
    }

private:
    const char* message;
};

/**
 * @brief Filter parameter.
 */
struct FilterParameter final
{
    std::string name; /** @brief Name of the filter parameter. */
    double value; /** @brief Value of the parameter. */
};

/** @brief Filter function. */
typedef std::function<void(std::vector<double>::iterator, std::vector<double>::iterator, std::vector<FilterParameter>)> Filter;

void applyFilter(std::vector<double>& signal, unsigned int threadCount, Filter filter, const std::vector<FilterParameter>& params);

//filters
void movingAverage_filter(std::vector<double>::iterator rangeStart, std::vector<double>::iterator rangeEnd, const std::vector<FilterParameter>& params);
void exponential_filter(std::vector<double>::iterator rangeStart, std::vector<double>::iterator rangeEnd, const std::vector<FilterParameter>& params);
void median_filter(std::vector<double>::iterator rangeStart, std::vector<double>::iterator rangeEnd, const std::vector<FilterParameter>& params);

#endif
