#include "elevator_fsm.h"
#include <stdio.h>


int q_check_floor(int current_floor);

void q_delete_order();

void q_delete_all();

int q_get_order(int current_floor, int current_direction);

void q_store_order(int new_order); //lagrer en ny bestilling i koen 


