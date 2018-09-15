# parallelSSSP

This project compares Parallel dijkstra with the state of the art Parallel BGL's Delta Stepping aalgorithm. The graph generator used is from the Graph500 benchmarks.

+ The folder "deltaSteppingBoost" includes the boost version (MPI) of Delta Stepping
+ The folder "parallelDijkstra" includes the OpenMP version of Delta Stepping

The comparison has been made for both MPI and OpenMP. (Even though this comparison seems of apples and oranges but it has been measured on single node which makes the comparison relevant as the address space is same)
