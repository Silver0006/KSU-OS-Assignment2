## Program Description
This program simulates the process of Banker's Alogrithm. The program parses a text file containing the data on the states of the program.
It then runs the algorithm to test whether is can find a safe sequence that the programs can execute in.

Banker's algorithm checks to see if programs vying for the same resources can be run without deadlock. 
It checks if the available resources can be given to a program to help it finish execution.
If so it logs that program and creates an ordered list of what programs need to be run to avoid deadlock.

I was tasked with determining whether a set of data could result in a safe sequence. The answer is yes, below is the output.
```
File: test.txt
Total Resources: 10 5 7 
Allocated Resources:
0 1 0 
2 0 0 
3 0 2 
2 2 1 
0 0 2 
Max Resources:
7 5 3 
3 3 2 
9 0 2 
2 2 2 
4 3 3 
Needed Resources:
7 4 3
1 3 2
6 0 0
0 0 1
4 3 1
Avalible Resources: 3 2 2 
Sequence: p3 p4 p1 p2 p0 
This sequence is safe
```

## Usage Instructions (Run in terminal)
1. g++ banker.cpp
2. ./a.out test.txt


