# Experiment 1A Detail 

### Aim: 
Program that creates multiple child processes using fork() and print different messages in parent and child process.

### Algorithm:
1.	Start the program.

2.	Declare required variables to store process IDs (pid_t pid1, pid2, etc.).

3.	Call the fork() system call to create the first child process.
	- If fork() returns 0, the process is the child.
	- If fork() returns a positive value, the process is the parent.

4.	In the child process:
	- Print a message indicating it is a child process.
	- Print the child process ID (PID) and its parent process ID (PPID).

5.	In the parent process:
	- Call fork() again to create another child process.

6.	For the second fork() call:
	- If return value is 0, identify it as the second child and print its PID and PPID.
	- If return value is positive, identify it as the parent.

7.	In the parent process:
	- Print a message indicating it is the parent process.
	- Print its PID.

8.	Terminate all processes using exit() or by reaching the end of main().

9.	Stop the program.

------------------------------

### Result 

The program was successfully executed and multiple child processes were created using the fork() system call.
Different messages were printed by the parent process and each child process, along with their respective Process IDs (PID) and Parent Process IDs (PPID), confirming the creation and execution of multiple processes.

-----------------------

### Key Outcomes

1.	Understood the working of the fork() system call in process creation.

2.	Observed that fork() returns:
	- 0 in the child process
	- A positive value (child PID) in the parent process.
	
3.	Learned how multiple fork() calls create multiple processes.
	
4.	Verified the parent–child relationship using PID and PPID values.
	
5.	Understood that parent and child execute the same code, but follow different execution paths.
	
6.	Gained practical exposure to process management in UNIX/Linux operating systems.

-----------------------
*fork() duplicates the calling process, creating a parent–child relationship where both execute concurrently.*