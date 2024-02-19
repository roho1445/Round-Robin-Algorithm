# You Spin Me Round Robin

The program models the 'Round Robin' Scheduling algorithm used by operating systems to ensure that all proceses get a fair share of the CPU. The Round Robin algorithm works by cylcing between all the processes and running each for a fixed time slice (called a quantum length).

A queue of processes is created, and when a process finihses its time cycle, it is put at the back of the queue and the next program at the beginning of the queue is run.

The program aims to compromise between waiting time and response time tradeoffs. Information about processes (PID, burst time, arrival time) is inputted into a file named "processes.txt" and the program takes the data and 'runs' the processes, calculating and outputting the average wait and response time for running all the processes.

## Building

The program was programmed in C and made use of the TAILQ structure defined in sys/queue.h. A queue was implemented with TAILQ to line the processses up and run them in a "First Come First Out" order. A quantum length is specified and the programs are run for the duration of the quanum length before the CPU cycles to the next process on the queue. The program runs all the input processes until all the processes are completed.

## Running
```shell
make
./rr INPUT_FILE_NAME QUANTUM_LENGTH

EXAMPLE RUN COMMAND: ./rr processes.txt 3
```

The "make" command should be run in the same directory as the rr.c file and an object file is created. Then run './rr INPUT_FILE_NAME QUANTUM_LENGTH". For example, if my input file is named "processes.txt" and I want to use a quantum length of 3, I would run "./rr processes.txt 3" in the terminal.

## Results
```shell
python -m unittest

```
The terminal should output the average waiting time and average response time that the Round Robin scheduling algorithm will yield. In the case of "./rr processes.txt 3", the average waiting time is 7.00 seconds and the average response time is 2.75 seconds.

The command "python -m unittest" can also be run which will run the program on a set of test cases (specified in test_lab2.py) and output whether or not the test cases were passed.

## Cleaning up

```shell
make clean
```

The "make clean" command should be used to clean up the object executable after use.
