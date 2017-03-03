#include <stdio.h>
#include "elev.h"
#include "queue.h"
#include "elevator_fsm.h"
#include "hw.h"
#include "timer.h"



/*******************************
*constants keeping track of what floor the elevator is at or last passed, and which state it is currently in
*******************************/
FLOOR current_floor = NO_FLOOR;
STATE current_state = INIT;
elev_motor_direction_t direction;


//ORDER AND FLOOR FUNCTIONS
/*******************************
*initizaling the elevator by moving the elevator to floor 1. 
*******************************/
void fsm_init() {
	if (!elev_init()) { 									//initialise hardware
                printf("Unable to initialize elevator hardware!\n");
                return 1;
        }
	FLOOR floor = elev_get_floor_sensor_signal() + 1;					//elev-function returns 0-3 as floor numbers, we use 1-4 in our enum FLOOR
	while(floor != FIRST_FLOOR) {								//move elevator to 1st floor
		elev_set_motor_direction(DIRN_DOWN);
		floor = elev_get_floor_sensor_signal() + 1;
		if (floor == FIRST_FLOOR) {
			current_floor = floor;
			elev_set_motor_direction(DIRN_STOP);
		}
	}
	current_state = IDLE;
	q_delete_all();
}



/*******************************
*returns next order to main
*******************************/
int fsm_get_order() {
        return q_get_order();
}



/*******************************
*checks to see if the current floor is in the queue. if so delete from queue.
*updates current_floor
*******************************/
int fsm_floor_reached(FLOOR floor){
	current_floor = floor;
	if (q_check_floor(current_floor)) {						//check if there are any orders on current_floor
		switch (current_state) {
			case RUN:
				direction = hw_set_direction(DIRN_STOP);
				q_delete_order(current_floor);
				hw_door_open();
				current_state = DOOROPEN;
				timer_start();
				break;
			case IDLE:
				hw_set_direction(DIRN_STOP);
				q_delete_order(current_floor);
				hw_open_door();
				current_state = DOOROPEN;
				timer_start();
				break;
			case INIT:
				q_delete_order(current_floor);
				hw_open_door();
				current_state = DOOROPEN;
				timer_start();
				break;
			case STOPBUTTON:
			case DOOROPEN:
				break;
		}
	}
}


		
/*******************************
*setter retningen mot den neste bestillingen
*******************************/
void fsm_order_exists() {
	FLOOR new_order = q_get_order();
	int to_floor = new_order-current_floor;
	while (to_floor != 0) {
		if (to_floor<0) {
			switch(current_state) {
				case RUN:
				case IDLE:
				case INIT:
					direction hw_set_direction(DIRN_UP);
					current_state = RUN;
					break;
				case DOOROPEN:
					hw_close_door();
					direction = hw_set_direction(DIRN_UP);
					current_state = RUN;
					break;
				case STOPBUTTON:
					break;
			}
		} else if (to_floor>0) {
			switch(current_state) {
                                case RUN:	//handlingene for disse er de samme, så jeg skrev det bare 1 gang
                                case IDLE:
                                case INIT:
                                        direction hw_set_direction(DIRN_DOWN);
                                        current_state = RUN;
                                        break;
                                case DOOROPEN:
                                        hw_close_door();
                                        direction = hw_set_direction(DIRN_DOWN);
                                        current_state = RUN;
                                        break;
                                case STOPBUTTON:
                                        break;
                        }
		} else if (to_floor == 0) {
			switch(current_state) {
                                case IDLE:
                                        direction = hw_set_direction(DIRN_STOP);
					break;
                                case RUN:
                                case INIT:
                                case DOOROPEN:
                                        direction = hw_set_direction(DIRN_STOP);
                                        current_state = IDLE;
                                        break;
                                case STOPBUTTON:
                                        break;
                        }
		}
	}
}



/*******************************
*
*******************************/
void fsm_button_pressed(elev_type_button_t button_pressed, FLOOR floor) {
	
} 






//STOP BUTTON FUNCTIONS
*******************************
*deletes all orders in the queue if the stop button is pushed.
*******************************/
void fsm_stop_button_pressed(){		
	q_delete_all();
	hw_set_stop_button_light(1);
	switch(current_state) {
		case RUN:
		case IDLE:
                case INIT:
			direction = hw_set_direction(DIRN_STOP);
                        if (hw_get_floor != 0) {
                                hw_open_door();
                        } else {
				hw_close_door();
			}
                        current_state = STOPBUTTON;
			break;
                case DOOROPEN:
			direction = hw_set_direction(DIRN_STOP);
			hw_open_door();
                        current_state = STOPBUTTON;
			break;
                case STOPBUTTON:
			current_state = STOPBUTTON;
			break;
	}
}



/*******************************
*deletes all orders in the queue if the stop button is pushed.
*******************************/
void fsm_stop_button_released() {
	hw_set_stop_button_light(0);
	switch(current_state) {
		case STOPBUTTON:
			timer_start();
			if (hw_get_floor != 0) {
				while (!timer_is_time_out()) {
					hw_open_door();
				}
			}
			hw_close_door();
			current_state = IDLE;
			break;
		case IDLE:
		case INIT:
		case RUN:
		case DOOROPEN:
			hw_close_door();
			direction = hw_set_direction(DIRN_STOP);
			current_state = IDLE;
			break;
	}
}



/*******************************
*checks if the stop button is pressed. Returns  1 if yes, 0 if no.
*******************************/
int fsm_is_stop_button_pressed() {
	return hw_get_stop_button_status();
}






//INDICATOR LIGHTS
/*******************************
*sets a new indicator light every time a floor is reached.
*******************************/
void fsm_set_indicator(int floor) {
	hw_set_floor_indicator_light(floor);
}





//TIMER FUNCTION
/*******************************
*checks if 3 seconds has passed
*******************************/
void fsm_is_time_out() {
	
}




~                                                                                                                                                                                                
~                                                                                                                                                                                                
~                                                                                                                                                                                                
~                                             
