# You Spin Me Round Robin

The program models the 'Round Robin' Scheduling algorithm used by operating systems to ensure that all proceses get a fair share of the CPU. The Round Robin algorithm works by cylcing between all the processes and running each for a fixed time slice (called a quantum length).

A queue of processes is created, and when a process finihses its time cycle, it is put at the back of the queue and the next program at the beginning of the queue is run.

The program aims to compromise between waiting time and response time tradeoffs. Information about processes (PID, burst time, arrival time) is inputted into a file named "processes.txt" and the program takes the data and 'runs' the processes, calculating and outputting the average wait and response time for running all the processes.

## Building

```shell
TODO
```
The program was programmed in C and made use of the TAILQ structure defined in sys/queue.h.

## Running

cmd for running TODO
```shell
TODO
```

results TODO
```shell
TODO

```

## Cleaning up

```shell
TODO
```
