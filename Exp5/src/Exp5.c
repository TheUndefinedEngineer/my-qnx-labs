#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/* Size of circular buffer */
#define BUFFER_SIZE 5

/* Number of producer and consumer threads */
#define PRODUCERS 3
#define CONSUMERS 3

/* Circular queue control variables */
int front = 0;   // Points to the next item to be removed
int rear = 0;    // Points to the next free slot for insertion
int count = 0;   // Current number of elements in buffer

/* Shared buffer */
int buffer[BUFFER_SIZE];

/* Mutex to protect shared buffer */
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

/* Condition variables */
pthread_cond_t not_empty = PTHREAD_COND_INITIALIZER; // Wait if buffer empty
pthread_cond_t not_full  = PTHREAD_COND_INITIALIZER; // Wait if buffer full

/* Structure to pass producer thread ID */
typedef struct {
    int thread_id;
} producer_id;

/* Structure to pass consumer thread ID */
typedef struct {
    int thread_id;
} consumer_id;

/* Thread function declarations */
void* producer(void* arg);
void* consumer(void* arg);

int main(void) {

    /* Thread arrays */
    pthread_t producer_thread[PRODUCERS];
    pthread_t consumer_thread[CONSUMERS];

    /* ID arrays */
    producer_id p_id[PRODUCERS];
    consumer_id c_id[CONSUMERS];

    /* Create producer threads */
    for(int i = 0; i < PRODUCERS; i++){
        p_id[i].thread_id = i;
        pthread_create(&producer_thread[i], NULL, producer, &p_id[i]);
    }

    /* Create consumer threads */
    for (int i = 0; i < CONSUMERS; i++){
        c_id[i].thread_id = i;
        pthread_create(&consumer_thread[i], NULL, consumer, &c_id[i]);
    }

    /* Wait for all producers to finish */
    for(int i = 0; i < PRODUCERS; i++)
        pthread_join(producer_thread[i], NULL);

    /* Wait for all consumers to finish */
    for(int i = 0; i < CONSUMERS; i++)
        pthread_join(consumer_thread[i], NULL);

    return EXIT_SUCCESS;
}

/* Producer Thread Function */
void* producer(void* arg){

    const producer_id *p = (const producer_id *)arg;

    /* Each producer produces 10 items */
    for(int i = 1; i <= 10; i++){

        pthread_mutex_lock(&mutex);   // Enter critical section

        /* Wait if buffer is full */
        while(count == BUFFER_SIZE)
            pthread_cond_wait(&not_full, &mutex);

        /* Insert item into buffer */
        buffer[rear] = i;
        rear = (rear + 1) % BUFFER_SIZE;
        count++;

        printf("Producer %d produced item: %d\n", p->thread_id, i);

        /* Signal that buffer is not empty */
        pthread_cond_signal(&not_empty);

        pthread_mutex_unlock(&mutex); // Exit critical section
    }

    return NULL;
}

/* Consumer Thread Function */
void* consumer(void* arg){

    const consumer_id *p = (const consumer_id *)arg;

    /* Each consumer consumes 10 items */
    for(int i = 1; i <= 10; i++){

        pthread_mutex_lock(&mutex);   // Enter critical section

        /* Wait if buffer is empty */
        while(count == 0)
            pthread_cond_wait(&not_empty, &mutex);

        /* Remove item from buffer */
        int item = buffer[front];
        front = (front + 1) % BUFFER_SIZE;
        count--;

        printf("Consumer %d consumed item: %d\n", p->thread_id, item);

        /* Signal that buffer has free space */
        pthread_cond_signal(&not_full);

        pthread_mutex_unlock(&mutex); // Exit critical section
    }

    return NULL;
}
