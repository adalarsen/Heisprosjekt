#ifndef ELEVATOR_FSM
#define ELEVATOR_FSM
#include <stdio.h>
#include "elev.h"
#include "queue.h"





//INITIALIZE
int fsm_init();								//initialize elevator


//ORDER AND FLOOR FUNCTIONS
void fsm_floor_reached(floor_t floor);						//updates the queue when a new floor is passed
int fsm_get_order();								//returns the next order from queue
void fsm_order_exists();
void fsm_button_pressed(int button_pressed); 		//


//INDICATOR LIGHTS
void fsm_set_indicator(int floor);						//set floor indicator light when elevator reaches a new floor


//STOP BUTTON FUNCTIONS
void fsm_stop_button_pressed();							//deletes all entries in the queue when the stop button is pushed
void fsm_stop_button_released();						//to turn off light, go to a new floor etc.
int fsm_is_stop_button_pressed();			  			//checks if stop button is pushed. Returns 1 if yes, 0 if no.	


//TIMER
void fsm_time_out();                                                            //close door if time is out (after three seconds)


//DOOR
int fsm_is_door_open();


//DIRECTION
elev_motor_direction_t fsm_get_direction();

#endif
