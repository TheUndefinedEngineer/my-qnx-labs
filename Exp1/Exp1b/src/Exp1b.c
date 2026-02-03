#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

int main() {
    int n = 3;   // number of child processes to create
    pid_t pid;

    for (int i = 0; i < n; i++) {
        pid = fork();

        if (pid < 0) {
            printf("Fork failed!\n");
            exit(1);
        }

        if (pid == 0) {
            // CHILD PROCESS
            printf("Child %d: My PID = %d, Parent PID = %d\n",
                   i, getpid(), getppid());

            // Sleep to allow parent to terminate
            sleep(7);

            printf("Child %d after parent exit: My PID = %d, New Parent PID = %d\n",
                   i, getpid(), getppid());

            exit(0); // Child exits
        }
        // PARENT continues to fork next child
    }

    // PARENT PROCESS
    printf("Parent Process: PID = %d. Created %d children. Sleeping 5 seconds...\n",
           getpid(), n);

    sleep(5);
    printf("Parent exiting now.\n");

    return 0;
}
