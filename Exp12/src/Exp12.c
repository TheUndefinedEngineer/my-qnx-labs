//Libraries
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>

//Signal handler function
void signal_handler(int signo){
	static int count = 0;
	printf("Signal received: %d\n", count++); //Prints for each signal received
}

int main(void) {
	struct sigevent sigevent; // Defines how the timer notifies the process (signal)
	struct itimerspec itime; // Defines when the timer fires and repeat interval
	timer_t timerID;        // Timer handle returned by timer_create

	//Register signal
	signal(SIGUSR1, signal_handler);

	//Init signal
	SIGEV_SIGNAL_INIT(&sigevent,SIGUSR1);

	//Create timer
	if(timer_create(CLOCK_MONOTONIC, &sigevent, &timerID) == -1){
		perror("timer_create");
		exit(1);
	}

	itime.it_value.tv_sec = 1;
	itime.it_value.tv_nsec = 500000000;

	//Repeat every 5 sec
	itime.it_interval.tv_sec = 5;
	itime.it_interval.tv_nsec = 0;

	if(timer_settime(timerID, 0, &itime, NULL) == -1){
		perror("timer_settime");
		timer_delete(timerID);
		exit(1);
	}

	while(1){
		pause(); //Keep process alive without burning CPU
	}

	return EXIT_SUCCESS;
}
