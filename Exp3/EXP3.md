# Experiment 3 Detail

## Aim

To create a multithreaded application using POSIX threads in which four threads update different segments of a shared array of size 1000, and to ensure safe concurrent access using a mutex while synchronizing thread completion using pthread_join().

⸻

## My Thought Process 
    - When multiple threads operate on shared memory, improper synchronization can lead to race conditions.
    - Since threads share the same address space, all threads can access the same global array.
    - To demonstrate controlled parallelism, the array of size 1000 can be divided into four equal segments.
    - Each thread will be responsible for updating exactly 250 elements.
    - Even though each thread updates a different portion of the array, the array itself remains a shared resource.
    - To prevent potential data corruption and demonstrate safe design, a mutex is introduced to protect the critical section.
    - The critical section consists of the portion where the thread updates the shared array.
    - The mutex ensures that only one thread updates the array at a time.
    - pthread_join() is used to ensure that the main thread waits for all worker threads before program termination.
    - By comparing program behavior with and without mutex, the importance of synchronization becomes evident.

This approach helped in understanding:
    - Shared memory behavior in multithreaded programs
	- The concept of critical sections
	- Practical implementation of mutual exclusion
	- The difference between synchronized and unsynchronized execution
	- Proper thread lifecycle management

⸻

## Algorithm

Step 1: Start the program.

Step 2: Declare a global integer array of size 1000.

Step 3: Define the number of threads as 4 and calculate chunk size as: