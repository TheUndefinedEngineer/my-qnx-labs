# Experiment 1A Detail 

Aim: Program that creates multiple child processes using fork() and print different messages in parent and child process.

Algorithm:
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

