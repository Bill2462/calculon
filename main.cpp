/**
 * @file main.cpp
 * @brief This source file contains main function.
 * @author Krzysztof Adamkiewicz
 * @date 2/10/2019
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

#include <iostream>
#include <string>
#include "utils.hpp"
#include "filters.hpp"
#include "cxxopts/cxxopts.hpp"

int main(int argc, char* argv[])
{
    cxxopts::Options options("Calculon", "Program for applying filters to a signal.");
    options.add_options()
    ("t,thread-count", "Thread count.", cxxopts::value<unsigned int>())
    ("f,filter-type", "Filter type.", cxxopts::value<std::string>())
    ("i,input-file", "Input file name.", cxxopts::value<std::string>())
    ("o,output-file", "Output file name.", cxxopts::value<std::string>())
    ("a,alpha", "Damping coeffiients for exponential filter.", cxxopts::value<double>())
    ("s,block-size", "Block size for mobing average and median filter.", cxxopts::value<unsigned int>());

    //parse argumentss
    auto args = options.parse(argc, argv);
    if(args.count("input-file") == 0)
    {   
        std::cout<<"ERR: Input file not specified!"<<std::endl;
        return 1;
    }
    if(args.count("output-file") == 0)
    {   
        std::cout<<"ERR: Output file not specified!"<<std::endl;
        return 1;
    }
    if(args.count("thread-count") == 0)
    {   
        std::cout<<"ERR: Thread not specified!"<<std::endl;
        return 1;
    }
    if(args.count("filter-type") == 0)
    {   
        std::cout<<"ERR: Filter type not specified!"<<std::endl;
        return 1;
    }
    //general
    const std::string inputFile = args["input-file"].as<std::string>();
    const std::string outputFile = args["output-file"].as<std::string>();
    const std::string filterType = args["filter-type"].as<std::string>();
    const unsigned int threadCount = args["thread-count"].as<unsigned int>();
    //filter specific
    double a;
    unsigned int blockSize;
    
    if(filterType == "ma-filter")
    {
        if(args.count("block-size") == 0)
        {
            std::cout<<"ERR: Block size not specified!"<<std::endl;
            return 1;
        }
        blockSize = args["block-size"].as<unsigned int>();
    }
    
    else if(filterType == "exp-filter")
    {
        if(args.count("alpha") == 0)
        {
            std::cout<<"ERR: Damping coeffiient not specified!"<<std::endl;
            return 1;
        }
        a = args["alpha"].as<double>();
    }
    
    else if(filterType == "med-filter")
    {
        if(args.count("block-size") == 0)
        {
            std::cout<<"ERR: Block size not specified!"<<std::endl;
            return 1;
        }
        blockSize = args["block-size"].as<unsigned int>();
    }
    
    else
    {
        std::cout<<"ERR: Invalid filter type! (ma-filter, exp-filter, med-filter)"<<std::endl;
        return 1;
    }
    
    //dump settings
    std::cout<<"####### Settings summary #######"<<std::endl;
    std::cout<<"Input file: "<<inputFile<<std::endl;
    std::cout<<"Output file: "<<outputFile<<std::endl;
    std::cout<<"Thread count: "<<threadCount<<std::endl;
    if(filterType == "ma-filter")
    {
        std::cout<<"Filter type: Moving average filter"<<std::endl;
        std::cout<<"Block size: "<<blockSize<<std::endl;
    }
    if(filterType == "exp-filter")
    {
        std::cout<<"Filter type: Exponential averaging filter"<<std::endl;
        std::cout<<"Damping coeffiient: "<<a<<std::endl;
    }
    if(filterType == "med-filter")
    {
        std::cout<<"Filter type: Median filter"<<std::endl;
        std::cout<<"Block size: "<<blockSize<<std::endl;
    }
    std::cout<<std::endl;
    
    //load signal
    std::cout<<"Loading signal....";
    std::vector<double> signal = loadSignal(inputFile);
    std::cout<<"Done!"<<std::endl;
    std::cout<<"Signal lenght: "<<signal.size()<<" samples"<<std::endl;
    
    //run filer
    std::vector<double> output;
    std::cout<<"Running filter....";
    StopWatch watch;
    watch.start();
    if(filterType == "ma-filter")
        output = applyFilter(signal, threadCount, movingAverage_filter, {{"block-size", static_cast<double>(blockSize)}});
    
    if(filterType == "exp-filter")
        output = applyFilter(signal, threadCount, exponential_filter, {{"damping-coeff", a}});
    
    if(filterType == "med-filter")
        output = applyFilter(signal, threadCount, median_filter, {{"block-size", static_cast<double>(blockSize)}});
    watch.stop();
    std::cout<<"Done!"<<std::endl;
    
    //show performance
    std::cout<<"Filtering took: "<<watch.getTime()<<"s"<<std::endl;
    std::cout<<"Average speed: "<<signal.size()/watch.getTime()<<" Sa/s"<<std::endl<<std::endl;

    //save output file
    std::cout<<"Saving signal....";
    saveSignal(output, outputFile);
    std::cout<<"Done!"<<std::endl;

    return 0;
}
