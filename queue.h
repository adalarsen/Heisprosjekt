#ifndef QUEUE
#define QUEUE
#include "elev.h"
#include <stdio.h>

typedef enum {FIRST, SECOND, THIRD, FOURTH, FIRST_UP, SECOND_UP, THIRD_UP, SECOND_DOWN, THIRD_DOWN, FOURTH_DOWN} elev_buttons_t;	//enum stating the elev button constants
typedef enum {NO_FLOOR, FIRST_FLOOR, SECOND_FLOOR, THIRD_FLOOR, FOURTH_FLOOR} floor_t;				//enum stating the names of the elevator floors
typedef enum {IDLE, RUN, DOOROPEN, STOPBUTTON, INIT} state_t;							//enum stating the next state of the elevator

int q_check_floor(floor_t current_floor);							//returns 1 if there is an order on current_floor

//DELETE FUNCTIONS
void q_delete_order(floor_t floor);							//deletes all orders on floor (set to 0)
void q_delete_all();									//deletes every order (set to 0) in orders 

//GET AND STORE FUNCTIONS
floor_t q_get_order(floor_t current_floor, elev_motor_direction_t current_direction);	//returns which floor the next order is on
void q_store_order(int new_order); 							//stores a new order in orders 



#endif
