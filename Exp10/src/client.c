#include <stdio.h>
#include <stdlib.h>
#include <sys/dispatch.h>
#include <sys/iofunc.h>
#include <sys/neutrino.h>

typedef struct {
    int type;
    int length;
} msg_header_t;

int main(void){
	msg_header_t header;
	int payload[N];
	header.type   = MSG_TYPE_CHECKSUM;
	header.length = sizeof(payload);


	name_close("iov_server",0);
	return EXIT_SUCCESS;
}
