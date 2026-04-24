# Hands-on QNX RTOS experiments and system-level programming

## Experiment 1
A. Aim : To write a program that creates multiple child processes using fork() and print different messages in parent and child process. Terminate the parent after 5 seconds and print the pid from the child.

[Experiment 1A – Process Creation Using fork()](Exp1/Exp1a/EXP1A.md)

B. Aim : Program that terminates the parent after 5 seconds and print the pid from the child.

[Experiment 1B – Parent Process Termination and Child PID Display](Exp1/Exp1b/EXP1B.md)

---
## Experiment 2
Aim : To implement a multithreaded application using POSIX threads in which multiple threads process different segments of an array concurrently, and to synchronize the execution of threads using the pthread_join() function.

[Experiment 2 – Multithreaded using POSIX Threads](Exp2/EXP2.md)

---
## Experiment 3
Aim: To write a program to create a process with 4 threads that update the portion of array of size 1000 bytes by updating 250 bytes each. Make the main thread to join on the 4 threads and print the completion. Use mutex to prevent data corruption while each thread is updating the array.

[Experiment 3 - Multithread using mutex](Exp3/EXP3.md)

---
## Experiment 4
Aim: To implement and demonstrate inter-thread communication using a shared queue protected by POSIX mutexes and condition variables, where one thread produces data and another thread consumes data asynchronously in a thread-safe manner.

[Experiment 4 - Single Consumer & Producer](Exp4/EXP4.md)

---
## Experiment 5
Aim: To implement a thread-safe bounded buffer (also known as a circular queue) that is shared between multiple producer threads and multiple consumer threads. The buffer has a fixed size (N slots). Producers add items to the buffer, and consumers remove items from the buffer.

[Experiment 5 - Multiple Consumer & Producer](Exp5/EXP5.md)

---
## Experiment 6
Aim: To implement the Send–Receive–Reply communication mechanism between a client and server process in QNX Neutrino RTOS, where the client sends a string message to the server and the server calculates and returns the checksum of the received string using message passing functions such as ChannelCreate(), ConnectAttach(), MsgSend(), MsgReceive(), and MsgReply().

[Experiment 6 - IPC Messaging Passing](Exp6/EXP6.md)

---
## Experiment 7
Aim: To implement pulse-based and message-based Inter-Process Communication (IPC) between a client and server in QNX Neutrino RTOS, where the client sends a pulse and a string message to the server and the server processes the pulse and returns the checksum of the received string.

[Experiment 7 - IPC Message Passing & Pulse](Exp7/EXP7.md)

---
## Experiment 8
Aim: To implement client–server communication using the name lookup mechanism in QNX Neutrino RTOS, where the client finds the server using a registered name instead of PID and CHID, sends a pulse and message, and receives the checksum reply.

[Experiment 8 - IPC Message Passing & Pulse using Register name](Exp8/EXP8.md)
