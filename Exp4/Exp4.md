# Experiment 4 Detail

## Aim
To implement a thread-safe bounded buffer (circular queue) using POSIX threads where one producer thread inserts data and one consumer thread removes data, ensuring safe inter-thread communication using mutexes and condition variables.


## My Thought Process

- In a producer-consumer system, both threads share the same buffer.
- Since both threads access shared memory, race conditions can occur without proper synchronization.
- A circular buffer is suitable because it allows fixed-size, deterministic memory usage.
- The buffer must prevent overflow (producer inserting when full).
- The buffer must prevent underflow (consumer removing when empty).
- A mutex is required to protect the critical section where the shared buffer is accessed.
- Condition variables are required to allow threads to wait efficiently instead of busy waiting.
- The producer should wait when the buffer is full.
- The consumer should wait when the buffer is empty.
- pthread_join() ensures that the main thread waits for both threads before terminating.
- This setup demonstrates safe communication between two concurrent threads.

This approach helped in understanding:

- Inter-thread communication using shared memory
- The concept of bounded buffer
- Proper use of condition variables
- Blocking synchronization instead of busy waiting
- Safe design of concurrent systems


## Algorithm

Step 1: Start the program.

Step 2: Declare a fixed-size buffer (circular queue).

Step 3: Initialize front, rear, and count variables.

Step 4: Initialize mutex and condition variables (not_empty and not_full).

Step 5: Create producer thread.

Step 6: Create consumer thread.

Producer Thread:
- Lock the mutex.
- While buffer is full, wait on not_full.
- Insert item into buffer.
- Update rear circularly.
- Increment count.
- Signal not_empty.
- Unlock the mutex.

Consumer Thread:
- Lock the mutex.
- While buffer is empty, wait on not_empty.
- Remove item from buffer.
- Update front circularly.
- Decrement count.
- Signal not_full.
- Unlock the mutex.

Step 7: Wait for both threads using pthread_join().

Step 8: End the program.


## Result

The bounded buffer was successfully implemented using one producer and one consumer thread. Synchronization using mutex and condition variables ensured that no data corruption occurred and that threads waited appropriately when the buffer was full or empty.


## Key Learning Outcomes

- Understanding producer-consumer synchronization
- Practical implementation of condition variables
- Importance of while loop in condition checking
- Safe circular buffer implementation
- Avoidance of race conditions and busy waiting