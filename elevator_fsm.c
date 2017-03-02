#include "elev.h"
#include "queue.h"
#include "elevator_fsm.h"

/*********************
*Enum som navngir konstantene etasjeknapper, heisretning, etasje og  
*om heisen skal stoppe eller fortsette i etasjen den er i. 
*********************/

int current_floor = -1;				//constant keeping track of what floor the elevator is at
int last_floor_passed = -1;			//constant keeping track of what floor the elevator most recently passed

void fsm_elev_on(){ 				//initializing the queue
	q_delete_all();
}

int fsm_update_floor(int floor){ 	//checks to see if the current floor is in the queue. if so delete from queue.
	last_floor_passed = current_floor;
	current_floor = floor;	//
	if (q_check_floor(current_floor)) {
		q_delete_order(current_floor);
		return STOP;
	}
	return CONTINUE;
}

void fsm_stop_button_pressed(){		//if the stop button is pushed, delete queue. 
	q_delete_all();
}
