#include <stdio.h>
#include <stdlib.h>
#include <sys/neutrino.h>
#include <unistd.h>
#include <string.h>

// Message structure used for communication
typedef struct {
    char data[256];   // buffer to hold incoming string from client
} mymsg_t;

// Function to calculate checksum of a string
int calculate_checksum(char *str) {
    int sum = 0;

    // Traverse until null terminator
    while (*str != '\0') {
        // Cast to unsigned char ensures consistent behavior across platforms
        sum += (unsigned char)*str;
        str++;  // move to next character
    }

    return sum;  // return total ASCII sum
}

int main(void) {
    int chid;              // Channel ID (server endpoint)
    rcvid_t rcvid;        // Receive ID (used for replying)
    mymsg_t rmsg;         // structure to store received message
    int checksum = -1;    // result to send back
    pid_t pid;            // process ID

    pid = getpid();       // get server process ID

    // Create a communication channel
    chid = ChannelCreate(0);

    if (chid == -1) {
        perror("ChannelCreate");
        exit(1);
    }

    // Print identification info (useful for debugging / client connection)
    printf("Process ID: %d\nChid: %d\n", pid, chid);

    // Save PID and CHID to file so client can read and connect
    FILE *f = fopen("/tmp/server_chid.txt", "w");
    if (f == NULL) {
        perror("fopen");
        exit(1);
    }

    fprintf(f, "%d %d", pid, chid);
    fclose(f);

    // Server runs indefinitely waiting for messages
    while (1) {

        // Block until a message is received
        rcvid = MsgReceive(chid, &rmsg, sizeof(rmsg), NULL);

        // Print received data
        printf("Received string: [%s]\n", rmsg.data);
        printf("Length: %ld\n", strlen(rmsg.data));

        // Process data → compute checksum
        checksum = calculate_checksum(rmsg.data);

        printf("Calculating checksum... \n Done -> Sending Msg\n");

        // Reply back to the client using rcvid
        MsgReply(rcvid, 0, &checksum, sizeof(checksum));

        /*
        // Optional: exit after one request (currently disabled)
        if (checksum >= 0) {
            exit(0);
        }
        */
    }

    return EXIT_SUCCESS;
}
