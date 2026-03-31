#include <stdio.h>
#include <stdlib.h>
#include <sys/neutrino.h>
#include <sys/dispatch.h>
#include <string.h>
#include "msg_type.h"

int main(){
    int coid, msg_status, pulse_status, checksum;
    message_t msg;

    // Prepare message data
    strlcpy(msg.data, "Mohan Sai", sizeof(msg.data));

    // Connect to server using NAME (no PID/CHID needed)
    coid = name_open("server", 0);
    if(coid == -1){
        perror("coid");
        exit(1);
    }

    // 🔹 Send pulse (non-blocking notification)
    // code = 3, value = 0xC0DEBEEF
    pulse_status = MsgSendPulse(coid, -1, 3, 0xC0DEBEEF);
    if(pulse_status == -1){
        perror("MsgPulseSend");
        exit(1);
    }

    // 🔹 Send message (blocking until reply)
    msg_status = MsgSend(coid, &msg, sizeof(msg), &checksum, sizeof(checksum));
    if(msg_status == -1){
        perror("MsgSend");
        exit(1);
    }

    // Print received checksum
    printf("Checksum: %d\n", checksum);

    // Close connection
    name_close(coid);

    return EXIT_SUCCESS;
}
