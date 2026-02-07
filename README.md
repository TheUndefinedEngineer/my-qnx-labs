# Hands-on QNX RTOS experiments and system-level programming

## Experiment 1
A. Aim : To write a program that creates multiple child processes using fork() and print different messages in parent and child process. Terminate the parent after 5 seconds and print the pid from the child.

[Experiment 1A – Process Creation Using fork()](Exp1/Exp1a/EXP1A.md)

B. Aim : Program that terminates the parent after 5 seconds and print the pid from the child.

[Experiment 1B – Parent Process Termination and Child PID Display](Exp1/Exp1b/EXP1B.md)


## Experiment 2
Aim : To implement a multithreaded application using POSIX threads in which multiple threads process different segments of an array concurrently, and to synchronize the execution of threads using the pthread_join() function.

[Experiment 2 – Multithreaded using POSIX Threads](Exp2/EXP2.md)


## Experiment 3
Aim: To write a program to create a process with 4 threads that update the portion of array of size 1000 bytes by updating 250 bytes each. Make the main thread to join on the 4 threads and print the completion. Use mutex to prevent data corruption while each thread is updating the array.
