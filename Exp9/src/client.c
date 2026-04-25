#include <stdio.h>
#include <stdlib.h>
#include <sys/dispatch.h>
#include <sys/iofunc.h>

#define PULSE_CODE_ONE (_PULSE_CODE_MINAVAIL + 1)
#define PULSE_CODE_TWO (_PULSE_CODE_MINAVAIL + 2)
#define PULSE_CODE_THREE (_PULSE_CODE_MINAVAIL + 3)

int main(void){
	int coid, pulse_status,pulse;

	coid = name_open("pulse_server", 0);

	if(coid == -1){
		perror("coid");
		return EXIT_FAILURE;
	}

	while(1){
	    printf("Enter Which Pulse to send(1-3): ");
	    fflush(stdout);
	    if(scanf("%d", &pulse) != 1){
	        // flush non-numeric garbage (e.g. letters)
	        while(getchar() != '\n');
	        printf("Invalid input\n");
	        continue;
	    }

	    switch(pulse){
	    case 1:
	        pulse_status = MsgSendPulse(coid, -1, PULSE_CODE_ONE, 0xDEADBEEF);
	        if(pulse_status == -1){ perror("MsgSendPulse"); name_close(coid); exit(1); }
	        sleep(1);
	        break;
	    case 2:
	        pulse_status = MsgSendPulse(coid, -1, PULSE_CODE_TWO, 0x0BADC0DE);
	        if(pulse_status == -1){ perror("MsgSendPulse"); name_close(coid); exit(1); }
	        sleep(1);
	        break;
	    case 3:
	        pulse_status = MsgSendPulse(coid, -1, PULSE_CODE_THREE, 0xC0DEBEEF);
	        if(pulse_status == -1){ perror("MsgSendPulse"); name_close(coid); exit(1); }
	        sleep(1);
	        break;
	    default:
	        printf("Invalid Pulse Code. Enter 1, 2, or 3.\n");
	        break;  // loop continues naturally
	    }
	}

	name_close(coid);
	return EXIT_SUCCESS;
}
