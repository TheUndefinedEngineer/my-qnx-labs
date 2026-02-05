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

------------------------

### Result

The program was successfully executed such that the parent process terminated after 5 seconds, while the child process continued execution and printed its process ID (PID).
After the termination of the parent, the child process was observed to be adopted by the init/systemd process, confirming the behavior of an orphan process.

------------------------

### Key Outcomes

1.	Understood the use of fork() to create a parent and child process.
	
2.	Learned how a parent process can be terminated using sleep() followed by exit().
	
3.	Observed that the child process continues execution even after the parent terminates.
	
4.	Verified the creation of an orphan process when the parent process exits before the child.
	
5.	Understood how the child process PID remains unchanged, while the PPID changes after parent termination.
	
6.	Gained practical understanding of process life cycle management in UNIX/Linux systems.

------------------------
*When a parent process terminates before its child, the child becomes an orphan and is adopted by the init/system process.*