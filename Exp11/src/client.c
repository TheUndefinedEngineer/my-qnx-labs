//Libraries
#include <stdio.h>
#include <stdlib.h>
#include <sys/dispatch.h>
#include <errno.h>
#include <sys/neutrino.h>
#include <sys/iofunc.h>

// Pulse code define
#define TIMER_PULSE_CODE (_PULSE_CODE_MINAVAIL + 1)

int main(void){
	struct sigevent sigevent; // Defines how the timer notifies the process (pulse)
	struct itimerspec itime;  // Defines when the timer fires and repeat interval
	timer_t timerID;          // Timer handle returned by timer_create
	int coid; //Connection ID

	//Connecting channel
	if((coid = name_open("timer_pulse", 0)) == -1){
		perror("coid");
		exit(1);
	}

	//Initialize the sigevent to deliver a pulse on that channel
	SIGEV_PULSE_INIT(&sigevent, coid, SIGEV_PULSE_PRIO_INHERIT, TIMER_PULSE_CODE, 0xDEAFC0DE);

	//Create a timer that uses this sigevent
	if(timer_create(CLOCK_MONOTONIC, &sigevent, &timerID) == -1){
		perror("timer_create");
		name_close(coid); //Clean up
		exit(1);
	}

	//First pulse at 1.5sec
	itime.it_value.tv_sec = 1;
	itime.it_value.tv_nsec = 500000000;

	//Repeat every 5sec
	itime.it_interval.tv_sec = 5;
	itime.it_interval.tv_nsec = 0;

	//Start timer countdown
	if(timer_settime(timerID, 0, &itime, NULL) == -1){
		perror("timer_settime");
		timer_delete(timerID);
		name_close(coid);
		exit(1);
	}

	while(1){
		pause(); //keeps process alive, burns no CPU
	}

	return EXIT_SUCCESS;
}
