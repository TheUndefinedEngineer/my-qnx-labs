#include <stdio.h>
#include <stdlib.h>
#include <sys/neutrino.h>
#include <unistd.h>
#include <string.h>

// Message structure (for normal MsgSend)
typedef struct {
    char data[256];
} mymsg_t;

// Union to handle BOTH pulse and message in same buffer
typedef union {
    struct _pulse pulse;   // used when rcvid == 0 (pulse)
    mymsg_t       msg;     // used when rcvid > 0 (message)
} recv_buf_t;

// Checksum calculation function
int calculate_checksum(char *str) {
    int sum = 0;

    while (*str != '\0') {
        sum += (unsigned char)*str;  // ensure consistent behavior
        str++;
    }

    return sum;
}

int main(void) {
    int chid;              // channel ID
    rcvid_t rcvid;         // receive ID
    int checksum = -1;     // result to send back
    pid_t pid;
    recv_buf_t buf;        // shared buffer for pulse + message

    pid = getpid();

    // Create channel for communication
    chid = ChannelCreate(0);
    if (chid == -1) {
        perror("ChannelCreate");
        exit(1);
    }

    printf("Process ID: %d\nChid: %d\n", pid, chid);

    // Write PID + CHID to file for client
    FILE *f = fopen("/tmp/server_chid.txt", "w");
    if (f == NULL) {
        perror("fopen");
        exit(1);
    }
    fprintf(f, "%d %d", pid, chid);
    fclose(f);

    // Infinite loop → server always ready
    while (1) {

        // Wait for either pulse OR message
        rcvid = MsgReceive(chid, &buf, sizeof(buf), NULL);

        if (rcvid == 0) {
            // 🔹 This is a PULSE (non-blocking event)

            printf("Client active...\n");

            // Access pulse fields
            printf("Pulse code: %d\n", buf.pulse.code);
            printf("Pulse value: %x\n", buf.pulse.value.sival_int);

        } else if (rcvid == -1) {
            // Error case
            perror("rcvid");
            exit(1);

        } else {
            // 🔹 This is a NORMAL MESSAGE (requires reply)

            checksum = calculate_checksum(buf.msg.data);

            printf("Calculating checksum...\nDone -> Sending Msg\n");

            // Reply back to specific client
            MsgReply(rcvid, 0, &checksum, sizeof(checksum));
        }
    }

    return EXIT_SUCCESS;
}
