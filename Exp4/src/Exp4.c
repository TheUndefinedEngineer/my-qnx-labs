#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/* Size of the circular buffer */
#define BUFFER_SIZE 5

/* Circular queue control variables */
int front = 0;   // Index of next element to remove
int rear = 0;    // Index of next position to insert
int count = 0;   // Current number of elements in buffer

/* Shared buffer */
int buffer[BUFFER_SIZE];

/* Mutex to ensure mutual exclusion */
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

/* Condition variables */
pthread_cond_t not_empty = PTHREAD_COND_INITIALIZER; // Wait if buffer is empty
pthread_cond_t not_full  = PTHREAD_COND_INITIALIZER; // Wait if buffer is full

/* Thread function declarations */
void* producer(void* arg);
void* consumer(void* arg);

int main(void){

    pthread_t producer_thread;
    pthread_t consumer_thread;

    /* Create producer thread */
    pthread_create(&producer_thread, NULL, producer, NULL);

    /* Create consumer thread */
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    /* Wait for threads to complete */
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    return EXIT_SUCCESS;
}

/* Producer Thread */
void* producer(void* arg){

    /* Produce 10 items */
    for(int i = 1; i <= 10; i++){

        pthread_mutex_lock(&mutex);   // Enter critical section

        /* Wait while buffer is full */
        while(count == BUFFER_SIZE)
            pthread_cond_wait(&not_full, &mutex);

        /* Insert item into buffer */
        buffer[rear] = i;
        rear = (rear + 1) % BUFFER_SIZE;  // Circular increment
        count++;

        printf("Produced item: %d\n", i);

        /* Signal that buffer now has data */
        pthread_cond_signal(&not_empty);

        pthread_mutex_unlock(&mutex); // Exit critical section
    }

    return NULL;
}

/* Consumer Thread */
void* consumer(void* arg){

    /* Consume 10 items */
    for(int i = 1; i <= 10; i++){

        pthread_mutex_lock(&mutex);   // Enter critical section

        /* Wait while buffer is empty */
        while(count == 0)
            pthread_cond_wait(&not_empty, &mutex);

        /* Remove item from buffer */
        int item = buffer[front];
        front = (front + 1) % BUFFER_SIZE;  // Circular increment
        count--;

        printf("Consumed item: %d\n", item);

        /* Signal that buffer now has free space */
        pthread_cond_signal(&not_full);

        pthread_mutex_unlock(&mutex); // Exit critical section
    }

    return NULL;
}
