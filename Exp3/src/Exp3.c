#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/* Total size of the shared array */
#define SIZE 1000

/* Number of threads to be created */
#define THREADS 4

/* Mutex to synchronize access to the shared array */
pthread_mutex_t mutex;

/* Each thread will update an equal portion of the array */
int chunk = SIZE / THREADS;

/* Shared array of size 1000 */
int arr[SIZE];

/* Structure to pass data to each thread */
typedef struct {
    int thread_id;      // Unique ID for each thread (0–3)
    int start_index;    // Starting index of array portion
    int end_index;      // Ending index of array portion
} ThreadData;

/*
 * Thread function
 * Each thread updates its assigned portion of the shared array.
 * Mutex is used to prevent simultaneous access to the array.
 */
void* arr_operation(void* arg) {

    /* Typecast the argument to ThreadData structure */
    const ThreadData *p = (const ThreadData *)arg;

    /* Values to be written by each thread */
    int values[THREADS] = {'A', 'B', 'C', 'D'};

    /* Select value based on thread ID */
    int value = values[p->thread_id];

    /* Lock mutex before entering critical section */
    pthread_mutex_lock(&mutex);

    /* Indicate thread execution start */
    printf("Thread %d is running...\n", p->thread_id);

    /* Update the assigned portion of the shared array */
    for (int i = p->start_index; i < p->end_index; i++) {
        arr[i] = value;
    }

    /* Indicate thread execution end */
    printf("Thread %d is stopping...\n", p->thread_id);

    /* Unlock mutex after completing critical section */
    pthread_mutex_unlock(&mutex);

    return NULL;
}

int main(void) {

    /* Array to store thread identifiers */
    pthread_t threads[THREADS];

    /* Array of structures to hold data for each thread */
    ThreadData threadsdata[THREADS];

    /* Create THREADS number of threads */
    for (int i = 0; i < THREADS; i++) {

        /* Initialize thread-specific data */
        threadsdata[i].thread_id = i;
        threadsdata[i].start_index = i * chunk;
        threadsdata[i].end_index = (i + 1) * chunk;

        /* Create thread and pass its data */
        pthread_create(&threads[i], NULL, arr_operation, &threadsdata[i]);
    }

    /* Main thread waits for all worker threads to finish */
    for (int i = 0; i < THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    /* Program completed successfully */
    return EXIT_SUCCESS;
}
