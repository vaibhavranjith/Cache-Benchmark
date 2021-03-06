# Cache-Benchmark
This is a program to simulate a cache memory and run the SPEC 95 benchmark on them. 

# How to run and see the benchmark data?

There are two bash files in this directory

- Simulate
- Simulate2

Run them using the bash command after navigating to this directory.

```
$ bash simulate
$ bash simulate2
```
Running the command simulate runs the whole simulation on every .dat files in the Spec-95 benchmark. After the simulation a text file will open with the entire benchmark data. (You can find this in the Simout file which I have added to this repository ,expect it to be huge). <br />


## How to read the output ``Simout`` file?


This is a fragment of the output I have pasted to explain the output of the file. I have added some text tags starting with ``~`` for explaining what each of them are they do 

```
                          2048 	8 	2                        ~ 2048 is the size of cache in KB, 8 is the Line size and 2 is the word size. 
                          
                          
TEST FILE:: ***IJPEG.DAT***                                        ~ File used for the benchmark 
##########################################################################

Cache creation SUCCESSFUL.                
@@@@@@@@@@@@@@@@ 	CONVENTIONAL CACHE	@@@@@@@@@@@@@@@@@@@@@@@@@@   ~ This data is for the conventional cache
Number of misses:: 2130
Number of hits:: 5825
Number of instructions:: 7955
==========================================================================

Cache creation SUCCESSFUL.
@@@@@@@@@@@@@@@@ 	WAY-PREDICTION CACHE	@@@@@@@@@@@@@@@@@@@@@@@@@@  ~ This data is for the Way-prediction cache
Prediction hit rate::  0.675676
Prediction hit :: 5375.000000
Number of ways opened on average :: 1.324324
prediction miss (cache hit):: 450
Number of misses::  2130
Number of hits::   5825
Number of instructions:: 7955
==========================================================================

Cache creation SUCCESSFUL.
@@@@@@@@@@@@@@@@ 	WAY-HALTING CACHE	@@@@@@@@@@@@@@@@@@@@@@@@@@      ~ This data is for the Way-Halting cache.
Number of ways opened on average:: 0.783407
Number of misses:: 1907
Number of hits:: 6048
Number of instructions:: 7955
##########################################################################
```

## "I have another benchmark file I want to simulate on other configurations of the cache"

Clearly with the advancment of software the standards for the benchmarks are changing. If you have another file to simulate on different cache configuration (size, Line size, word size). This is the way to do it. First navigate to this directory and enter the following commands.

```
$ make
$ ./sim.out ${cache_size[$i]} ${cache_line_size[$j]} ${cache_assoc[$k]} ${File Name}
```

## Where to see the results.

If you just want to see the results of the simulation and don't wanna go through the pain of downloading and running this program, I have created the data output into CSV files and drawn the graphs of these data and added it the folder ./Statistics/Graphs. Please have a look :)
