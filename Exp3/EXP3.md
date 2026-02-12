# Experiment 3 Detail

## Aim

To create a multithreaded application using POSIX threads in which four threads update different segments of a shared array of size 1000, and to ensure safe concurrent access using a mutex while synchronizing thread completion using pthread_join().

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


## Algorithm

Step 1: Start the program.

Step 2: Declare a global integer array of size 1000.

Step 3: Define the number of threads as 4 and calculate chunk size as:

chunk = SIZE / THREADS

Step 4: Define a structure to store thread parameters:
- thread_id
- start_index
- end_index

Step 5: Initialize a mutex using pthread_mutex_init().

Step 6: Create a thread function that:
- Accepts a structure pointer as argument
- Extracts the thread ID and assigned index range
- Locks the mutex before entering the critical section
- Updates the assigned portion of the array
- Unlocks the mutex after completing the update

Step 7: Create four threads using a loop:
- Thread 0 updates index 0 to 249
- Thread 1 updates index 250 to 499
- Thread 2 updates index 500 to 749
- Thread 3 updates index 750 to 999

Step 8: Wait for all threads to complete execution using pthread_join().

Step 9: Display completion message.

Step 10: Terminate the program.

## Result

The shared array of 1000 elements was successfully updated using four concurrent threads.
With mutex protection, the critical section was accessed by only one thread at a time, ensuring safe execution.
Thread synchronization was successfully achieved using pthread_join().

## Key Learning Outcomes
- Understanding shared memory behavior in multithreaded applications
- Practical use of mutex for synchronization
- Deeper understanding of pthread_create(), pthread_join(), and mutex functions
- Clear visualization of synchronized vs unsynchronized execution
- Hands-on experience with multithreading in QNX RTOS