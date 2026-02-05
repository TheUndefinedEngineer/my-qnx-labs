# Experiment 1B Detail

### Aim:
Program that terminates the parent after 5 seconds and print the pid from the child.

------------------------

### Algorithm

1. Start the program.

2. Initialize the number of child processes to be created (n).

3. Initialize a loop counter from 0 to n – 1.

4. Inside the loop, call the fork() system call.

5. Check the return value of fork():
    - If return value is less than 0, print an error message and terminate the program.
    - If return value is 0, the process is a child process:
    - Print the child number.
        - Print the child’s PID using getpid().
        - Print the parent’s PID using getppid().
        - Sleep for a duration longer than the parent’s sleep time.
        - After the parent terminates, print the child’s PID again.
        - Print the new parent PID to show adoption by the process manager (procnto).
        - Terminate the child process.
    - If return value is greater than 0, the process continues as the parent and proceeds to create the next child.

6. After creating all child processes, the parent process:
    - Prints its PID and the number of children created.
    - Sleeps for 5 seconds.
    - Terminates execution.

7. Child processes continue running independently after parent termination.

8. Stop the program.

