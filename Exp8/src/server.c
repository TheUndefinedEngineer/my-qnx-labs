#include <stdio.h>
#include <stdlib.h>
#include <sys/neutrino.h>
#include <sys/dispatch.h>
#include "msg_type.h"

#define EOK 0

// Buffer to handle BOTH pulse and message
typedef union{
    message_t msg;        // normal message
    struct _pulse pulse;  // pulse
} message_buffer_t;

// Function prototype
int calculate_checksum(char *str);

int main(void) {
    rcvid_t rcvid;               // receive ID
    message_buffer_t bf;         // receive buffer
    name_attach_t *attach;       // name attachment structure

    // Register server with name "server"
    attach = name_attach(NULL, "server", 0);
    if(attach == NULL){
        perror("Name attach failed");
        exit(1);
    }

    // Infinite loop → always ready to receive
    while(1){

        // Wait for pulse or message
        rcvid = MsgReceive(attach->chid, &bf, sizeof(bf), NULL);

        if(rcvid == 0){
            // 🔹 Pulse received (no reply needed)

            if (bf.pulse.code == _PULSE_CODE_DISCONNECT) {
                // Special system pulse → client disconnected
                printf("Client disconnected\n");

            } else {
                // Custom pulse
                printf("Pulse Received, Client active!\n");
                printf("Pulse code: %d\n", bf.pulse.code);
                printf("Pulse value: %x\n", bf.pulse.value.sival_int);
            }

        } else if(rcvid == -1){
            // Error case
            perror("rcvid");

        } else {
            // 🔹 Normal message received (requires reply)

            int checksum = calculate_checksum(bf.msg.data);

            printf("Checksum = %d\n", checksum);

            // Reply back to client
            MsgReply(rcvid, EOK, &checksum, sizeof(checksum));
        }
    }

    // Cleanup (won’t reach here normally)
    name_detach(attach, 0);
    return EXIT_SUCCESS;
}

// Function to compute checksum
int calculate_checksum(char *str) {
    int sum = 0;

    while (*str != '\0') {
        sum += (unsigned char)*str;
        str++;
    }

    return sum;
}
