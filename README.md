# Calculon
Quick demonstration of the basic signal filtering techniques on a multicore processor.

![alt text](https://raw.githubusercontent.com/Bill2462/calculon/master/calculon.png)

### Supported filters

 - Moving average filter.
 - Exponential averaging filter.
 - Median filter.
 
### Compiling

```
mkdir build
cd build
cmake ..
make -j
```
Cmake is required.

### Running program
The following console optons are available:

```
 -t -> Number of threads.
 -f -> Filter type (str).
 -i -> Path to the input file.
 -o -> Path to the output file.
 -a -> Dampng coefficient (for exponential averaging).
 -s -> Block size (for median and moving average filter).
````

Filter names:

 - Moving average filter = "ma-filter"
 - Exponential averaging filter = "exp-filter"
 - Median filter = "med-filter"
 
Have a lot of fun!
