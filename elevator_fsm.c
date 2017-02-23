#include "elev.h"
#include "queue.h"
#include "elevator_fsm.h"

enum ELEV_BUTTONS = {FIRST, SECOND, THIRD, FORTH, FIRST_UP, SECOND_UP, THIRD_UP, SECOND_DOWN, THRID_DOWN, FORTH_DOWN};
enum DIRECTIONS = {UP = 1, DOWN = -1, STOP = 0};
enum FLOOR = {NO_FLOOR, FIRST_FLOOR, SECOND_FLOOR} 
enum NEXT_STATE = {STOP, CONTINUE};

int current_floor = -1;
int last_floor_passed = -1;

void fsm_elev_on(){
	q_delete_all();
}

int fsm_update_floor(int floor){ //sjekker om man er i etasjen som er bestilt, sletter i saa fall bestillingen
	last_floor_passed = current_floor;
	current_floor = floor;	//
	if (q_check_floor(current_floor)) {
		q_delete_order(current_floor);
		return STOP;
	}
	return CONTINUE;
}

void fsm_stop_button_pressed(){
	q_delete_all();
}
