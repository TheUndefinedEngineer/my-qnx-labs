# Experiment 2 Detail

## Aim
To implement a multithreaded application using POSIX threads in which multiple threads process different segments of an array concurrently, and to synchronize the execution of threads using the pthread_join() function.

## My Thought Process
- Sorting an entire array using a single thread is straightforward but does not demonstrate parallelism.
- To utilize multithreading, the array can be divided into equal parts, and each part can be processed by a separate thread.
- Since threads share the same address space, each thread can directly access and modify the shared array.
- For this experiment, the array of size 10 is divided into two halves:
- First half sorted by Thread 1
- Second half sorted by Thread 2
- Each sorting thread uses Bubble Sort, restricted only to its assigned index range.
- After both threads finish execution, the array contains two sorted halves, but the overall array is still not completely sorted.
- To achieve a fully sorted array, a third thread is introduced to merge the two sorted halves.
- The merge thread compares elements from both halves and copies them into a temporary array in sorted order.
- Once merging is complete, the result represents the fully sorted array.
- Synchronization is achieved using pthread_join() to ensure correct execution order.

## This approach helped in understanding
- Parallel execution using threads
- Division of work using index ranges
- Synchronization using joins
- Practical implementation of a merge step after parallel processing

## Algorithm
Step 1:
Start the program.

Step 2:
Declare a global integer array of size 10 with unsorted elements.

Step 3:
Define the number of threads as 2 and calculate the chunk size as:
```init
chunk = SIZE / THREADS
```
Step 4:
Define a structure to store thread parameters:
```c
start_index
end_index
```
Step 5:
Create a thread function that:
  - Accepts the structure pointer as argument
  - Extracts the start and end indices
  - Performs Bubble Sort only within the assigned range

Step 6:
Create two sorting threads:
  - Thread 1 sorts index range 0 to chunk-1
  - Thread 2 sorts index range chunk to SIZE-1

Step 7:
Wait for both sorting threads to complete execution using pthread_join().

Step 8:
Define another structure to store merge parameters:
  - Starting index of left half
  - Starting index of right half
  - End index of the array

Step 9:
Create a merge thread that:
  - Compares elements from the two sorted halves
  - Copies the smaller element into a temporary array
  - Copies remaining elements once one half is exhausted

Step 10:
Wait for the merge thread to complete execution using pthread_join().

Step 11:
Display the final sorted array.

Step 12:
Terminate the program.

## Result
The given array of 10 elements was successfully sorted using multiple threads. Parallel sorting was achieved using two threads, and a third thread merged the sorted halves to obtain the final sorted output.

## Key Learning Outcomes
- Understanding POSIX thread creation and synchronization
- Practical use of pthread_create() and pthread_join()
- Importance of dividing work among threads
- Understanding why a merge step is required after parallel sorting
- Hands-on experience with multithreaded programming in QNX RTOS
