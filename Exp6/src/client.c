#include <stdlib.h>
#include <stdio.h>
#include <sys/neutrino.h>
#include <string.h>

// Same message structure as server (MUST match exactly)
typedef struct {
    char data[256];   // buffer to send string to server
} mymsg_t;

int main(void) {
    int coid;                  // Connection ID (client-side handle to server)
    int server_pid, server_chid; // Server identification
    mymsg_t msg;              // message to send
    int incoming_checksum;    // reply buffer from server

    // Copy string safely into message buffer
    strlcpy(msg.data, "Client and Server", sizeof(msg.data));

    // Read server PID and CHID from file (written by server)
    FILE *f = fopen("/tmp/server_chid.txt", "r");
    if (f == NULL) {
        perror("fopen");
        exit(1);
    }

    fscanf(f, "%d %d", &server_pid, &server_chid);
    fclose(f);

    // Attach to server channel → creates connection
    coid = ConnectAttach(0, server_pid, server_chid, _NTO_SIDE_CHANNEL, 0);
    if (coid == -1) {
        perror("ConnectAttach");
        exit(1);
    }

    // Send message to server and block until reply is received
    int status = MsgSend(
        coid,                   // connection to server
        &msg, sizeof(msg),     // send buffer
        &incoming_checksum, sizeof(incoming_checksum) // receive buffer
    );

    if (status == -1) {
        perror("MsgSend");
        exit(1);
    }

    // Print result received from server
    printf("Checksum value: %d", incoming_checksum);

    return EXIT_SUCCESS;
}
