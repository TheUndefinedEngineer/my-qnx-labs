#include <stdlib.h>
#include <stdio.h>
#include <sys/neutrino.h>
#include <string.h>

// Message structure (same as server)
typedef struct {
    char data[256];   // string to send
} mymsg_t;

int main(void) {
    int coid;                   // connection ID to server
    int server_pid, server_chid;
    mymsg_t msg;               // message buffer
    int incoming_checksum;     // reply from server

    // Prepare message
    strlcpy(msg.data, "Client and Server", sizeof(msg.data));

    // Read server PID and CHID from file
    FILE *f = fopen("/tmp/server_chid.txt", "r");
    if (f == NULL) {
        perror("fopen");
        exit(1);
    }

    fscanf(f, "%d %d", &server_pid, &server_chid);
    fclose(f);

    // Attach to server channel
    coid = ConnectAttach(0, server_pid, server_chid, _NTO_SIDE_CHANNEL, 0);
    if (coid == -1) {
        perror("ConnectAttach");
        exit(1);
    }

    // 🔹 Send a PULSE (non-blocking notification)
    // priority = -1 → inherit priority
    // code = 1 → custom identifier (server checks this)
    // value = 0xDEADBEEF → arbitrary data payload
    int pulse_status = MsgSendPulse(coid, -1, 1, 0xDEADBEEF);

    if (pulse_status == -1) {
        perror("MsgSendPulse");
        exit(1);
    }

    // 🔹 Send normal message (blocking)
    // waits until server replies
    int msg_status = MsgSend(
        coid,
        &msg, sizeof(msg),
        &incoming_checksum, sizeof(incoming_checksum)
    );

    if (msg_status == -1) {
        perror("MsgSend");
        exit(1);
    }

    // Display checksum received from server
    printf("Checksum value: %d", incoming_checksum);

    return EXIT_SUCCESS;
}
