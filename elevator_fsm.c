#include "elev.h"
#include "queue.h"
#include "elevator_fsm.h"

/*******************************
*constants keeping track of what floor the elevator is at and what floor the elevator most recently passed.
*******************************/
int current_floor = -1;				
int last_floor_passed = -1;			

/*******************************
*initializing the queue to empty.
*******************************/
void fsm_elev_on(){ 				
	q_delete_all();
}

/*******************************
*checks to see if the current floor is in the queue. if so delete from queue.
*updates current_floor and last_floor_passed.
*******************************/
int fsm_update_floor(int floor){
	last_floor_passed = current_floor;
	current_floor = floor;	//
	if (q_check_floor(current_floor)) { 			//stops the elevator if there is an order at this floor.
		q_delete_order(current_floor);
		return IDLE;
	}
	return RUN;										//if not, continue.
}


/*******************************
*deletes all orders in the queue if the stop button is pushed.
*******************************/
void fsm_stop_button_pressed(){		
	q_delete_all();
}

