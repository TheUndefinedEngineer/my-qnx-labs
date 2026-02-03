#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid1, pid2;

    pid1 = fork();   // First child

    if (pid1 == 0) {
        // Child 1
        printf("Child 1 Process\n");
        printf("PID = %d, Parent PID = %d\n", getpid(), getppid());
    }
    else {
        pid2 = fork();   // Second child

        if (pid2 == 0) {
            // Child 2
            printf("Child 2 Process\n");
            printf("PID = %d, Parent PID = %d\n", getpid(), getppid());
        }
        else {
            // Parent process
            printf("Parent Process\n");
            printf("PID = %d\n", getpid());
        }
    }

    return 0;
}
