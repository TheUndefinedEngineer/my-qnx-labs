//Libraries
#include <stdio.h>
#include <stdlib.h>
#include <sys/dispatch.h>
#include <errno.h>
#include <sys/neutrino.h>
#include <sys/iofunc.h>

// Pulse code define
#define TIMER_PULSE_CODE (_PULSE_CODE_MINAVAIL + 1)

//function definition
void periodic_pulse(int value);

int main(void) {
	rcvid_t rcvid; //Receive ID
	name_attach_t *attach; //Pointer for server name
	struct _pulse pulse; //Pulse

	//Creating channel
	if((attach = name_attach(NULL, "timer_pulse", 0)) == NULL){
		perror("Channel!");
		exit(1);
	}

	//Loop to receive pulse
	while(1){
		//Receiving the pulse
		rcvid = MsgReceive(attach->chid, &pulse, sizeof(pulse), NULL);

		//Error handling
		if(rcvid == -1){
			perror("rcvid");
		}
		//Message
		else if(rcvid > 0){
			printf("This is a message.\n");
		}
		//Pulse
		else{
			switch(pulse.code){
			//pulse code for disconnection
			case _PULSE_CODE_DISCONNECT:
				printf("Connection disconnected!\n");
				ConnectDetach(pulse.scoid);
				break;
			//pulse code for timer based pulse
			case TIMER_PULSE_CODE:
				periodic_pulse(pulse.value.sival_int); //Function call
				break;
			default:
				printf("Pulse code unknown by server.\n");
				break;
			}
		}

	}
	return EXIT_SUCCESS;
}

//Function to print pulse value
void periodic_pulse(int value){
	printf("Sigevent received: %x\n", value);
}
