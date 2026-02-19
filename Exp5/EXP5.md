# Experiment 5 Detail

## Aim
To implement a thread-safe bounded buffer shared between multiple producer threads and multiple consumer threads, ensuring safe concurrent access using mutexes and condition variables.


## My Thought Process

- When multiple producers and consumers access the same buffer, concurrency increases significantly.
- The same synchronization logic from single producer-consumer can scale to multiple threads.
- All threads share the same buffer, so a single mutex must protect the shared resource.
- Producers must wait when the buffer is full.
- Consumers must wait when the buffer is empty.
- Proper signaling ensures only required threads wake up.
- Lock ordering must remain consistent to avoid deadlock.
- pthread_join() ensures that all threads complete before termination.
- The system must balance total produced and consumed items to avoid indefinite waiting.

This experiment helped in understanding:

- Multi-producer multi-consumer synchronization
- Scalability of synchronization logic
- Deadlock prevention concepts
- Thread coordination using condition variables
- Real-time deterministic buffer design


## Algorithm

Step 1: Start the program.

Step 2: Declare fixed-size circular buffer.

Step 3: Initialize front, rear, and count variables.

Step 4: Initialize mutex and condition variables.

Step 5: Create multiple producer threads using a loop.

Step 6: Create multiple consumer threads using a loop.

Producer Thread:
- Lock mutex.
- While buffer is full, wait on not_full.
- Insert item into buffer.
- Update rear circularly.
- Increment count.
- Signal not_empty.
- Unlock mutex.

Consumer Thread:
- Lock mutex.
- While buffer is empty, wait on not_empty.
- Remove item from buffer.
- Update front circularly.
- Decrement count.
- Signal not_full.
- Unlock mutex.

Step 7: Wait for all threads using pthread_join().
Step 8: End the program.


## Result

The bounded buffer was successfully shared among multiple producers and multiple consumers. Synchronization ensured safe concurrent access, prevented race conditions, and maintained data integrity even under higher concurrency.


## Key Learning Outcomes

- Advanced thread synchronization
- Handling multiple producers and consumers safely
- Deadlock awareness and lock ordering discipline
- Efficient use of condition variables with signal
- Deeper understanding of concurrent system design