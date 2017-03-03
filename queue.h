#include "elevator_fsm.h"
#include <stdio.h>


int q_check_floor(int current_floor);						//returns 1 if there is an order on current_floor

void q_delete_order(int floor);							//deletes all orders on floor (set to 0)

void q_delete_all();								//deletes every order (set to 0) in orders 

int q_get_order(int current_floor, int current_direction);			//returns which floor the next order is on

void q_store_order(int new_order); 						//stores a new order in orders 


