#ifndef ELEVATOR_FSM.H
#define ELEVATOR_FSM.H
#include <stdio.h>
#include "elev.h"
#include "queue.h"



typedef enum {FIRST, SECOND, THIRD, FOURTH, FIRST_UP, SECOND_UP, THIRD_UP, SECOND_DOWN, THIRD_DOWN, FOURTH_DOWN} ELEV_BUTTONS;	//enum stating the elev button constants
typedef enum {NO_FLOOR, FIRST_FLOOR, SECOND_FLOOR, THIRD_FLOOR, FOURTH_FLOOR} FLOOR;				//enum stating the names of the elevator floors
typedef enum {IDLE, RUN, DOOROPEN, STOPBUTTON, INIT} STATE;							//enum stating the next state of the elevator


//INITIALIZE
void fsm_init();								//initialize elevator


//ORDER AND FLOOR FUNCTIONS
int fsm_floor_reached(FLOOR floor);						//updates the queue when a new floor is passed
int fsm_get_order();								//returns the next order from queue
void fsm_order_exists_on_floor();
void fsm_button_pressed(elev_type_button_t button_pressed, FLOOR floor); 		//


//INDICATOR LIGHTS
void fsm_set_indicator(int floor);						//set floor indicator light when elevator reaches a new floor


//STOP BUTTON FUNCTIONS
void fsm_stop_button_pressed();							//deletes all entries in the queue when the stop button is pushed
void fsm_stop_button_released();						//to turn off light, go to a new floor etc.
int fsm_is_stop_button_pressed();			  			//checks if stop button is pushed. Returns 1 if yes, 0 if no.	


//TIMER
void fsm_time_out();                                                            //close door if time is out (after three seconds)


#endif
