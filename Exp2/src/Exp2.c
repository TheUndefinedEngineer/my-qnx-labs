#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define SIZE 10
#define THREADS 2

// Number of elements each thread will process
int chunk = SIZE / THREADS;

// Shared array to be sorted
int arr[SIZE] = {10,34,45,9,5,63,98,24,12,3};

// Structure to pass start and end index to sorting threads
typedef struct{
    int start_index;
    int end_index;
} ThreadPara;

// Structure to pass parameters to merge thread
typedef struct {
    int left_start;
    int right_start;
    int end;
} MergePara;

// Thread function to perform bubble sort on a portion of the array
void* bubble_sort(void* arg){
    // Typecast void pointer to ThreadPara pointer
    const ThreadPara *p = (const ThreadPara *)arg;

    // Bubble sort only within assigned range
    for (int i = p->start_index; i < p->end_index - 1; i++) {
        int swapped = 0;

        for (int j = p->start_index;
             j < p->end_index - 1 - (i - p->start_index);
             j++) {

            // Swap if elements are in wrong order
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = 1;
            }
        }

        // If no swap occurred, portion is already sorted
        if (swapped == 0)
            break;
    }
    return NULL;
}

// Thread function to merge two sorted halves
void* merge_func(void* arg){
    // Typecast void pointer to MergePara pointer
    const MergePara *p = (const MergePara *)arg;

    int temp[SIZE];      // Temporary array to store merged result
    int i = p->left_start;   // Index for left half
    int j = p->right_start;  // Index for right half
    int k = 0;               // Index for temp array

    // Merge elements from both halves while comparing
    while(i < chunk && j < SIZE){
        if(arr[i] < arr[j]){
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
    }

    // Copy remaining elements from right half
    if(i == chunk && j < SIZE){
        while(j < SIZE){
            temp[k++] = arr[j++];
        }
    }
    // Copy remaining elements from left half
    else {
        while(i < chunk){
            temp[k++] = arr[i++];
        }
    }

    // Debug output to verify indices
    printf("The sorted array: ");

    // Print merged array
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", temp[i]);
    }
    printf("\n");

    return NULL;
}

int main(void) {
    pthread_t sort1;
    pthread_t sort2;
    pthread_t merge_thread;

    ThreadPara t1, t2;
    MergePara m;

    // Parameters for first sorting thread
    t1.start_index = 0;
    t1.end_index = chunk;

    // Parameters for second sorting thread
    t2.start_index = chunk;
    t2.end_index = SIZE;

    // Parameters for merge thread
    m.left_start = 0;
    m.right_start = chunk;
    m.end = SIZE;

    // Create sorting threads
    pthread_create(&sort1, NULL, bubble_sort, &t1);
    pthread_create(&sort2, NULL, bubble_sort, &t2);

    // Wait for sorting threads to finish
    pthread_join(sort1, NULL);
    pthread_join(sort2, NULL);

    // Create merge thread
    pthread_create(&merge_thread, NULL, merge_func, &m);
    pthread_join(merge_thread, NULL);

    return EXIT_SUCCESS;
}
