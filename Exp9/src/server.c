#include <stdio.h>
#include <stdlib.h>
#include <sys/dispatch.h>
#include <sys/iofunc.h>
#include <errno.h>
#include <sys/neutrino.h>

#define PULSE_CODE_ONE (_PULSE_CODE_MINAVAIL + 1)
#define PULSE_CODE_TWO (_PULSE_CODE_MINAVAIL + 2)
#define PULSE_CODE_THREE (_PULSE_CODE_MINAVAIL + 3)

int main(void) {
	rcvid_t rcvid;
	name_attach_t *attach;
	struct _pulse pulse;

	if((attach = name_attach(NULL, "pulse_server", 0)) == NULL){
		printf("Channel creation failed\n");
		return EXIT_FAILURE;
	}

	printf("Server Started\n");

	while(1){
		rcvid = MsgReceivePulse(attach->chid, &pulse, sizeof(pulse), NULL);

		if(rcvid == -1){
			perror("rcvid");
		}

		if(rcvid == 0){
			switch(pulse.code){
			case _PULSE_CODE_DISCONNECT:
				printf("Connection Disconnected\n");
				ConnectDetach(pulse.scoid);
				break;
			case PULSE_CODE_ONE:
				printf("Message code: %d and Message value: %x\n",pulse.code,pulse.value.sival_int);
				break;
			case PULSE_CODE_TWO:
				printf("Message code: %d and Message value: %x\n",pulse.code,pulse.value.sival_int);
				break;
			case PULSE_CODE_THREE:
				printf("Message code: %d and Message value: %x\n",pulse.code,pulse.value.sival_int);
				break;
			default:
				printf("Pulse code doesn't match");
				break;
			}
			continue;
		}
	}
	name_detach(attach, 0);

	return EXIT_SUCCESS;
}
