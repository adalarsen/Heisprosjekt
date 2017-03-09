#include "elevator_fsm.h"
#include <stdio.h>



int q_check_floor(FLOOR current_floor);							//returns 1 if there is an order on current_floor

//DELETE FUNCTIONS
void q_delete_order(FLOOR floor);							//deletes all orders on floor (set to 0)
void q_delete_all();									//deletes every order (set to 0) in orders 

//GET AND STORE FUNCTIONS
FLOOR q_get_order(FLOOR current_floor, elev_motor_direction_t current_direction);	//returns which floor the next order is on
void q_store_order(int new_order); 							//stores a new order in orders 


