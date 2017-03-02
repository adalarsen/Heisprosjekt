#include "elev.h"
#include "queue.h"


void fsm_elev_on(); 					//initializes the queue
int fsm_update_floor(int floor);		//updates the queue when a new floor is passed
void fsm_stop_button_pressed();			//deletes all entries in the queue when the stop button is pushed

enum ELEV_BUTTONS = {FIRST, SECOND, THIRD, FORTH, FIRST_UP, SECOND_UP, THIRD_UP, SECOND_DOWN, THRID_DOWN, FORTH_DOWN};
enum DIRECTIONS = {UP = 1, DOWN = -1, STOP = 0};
enum FLOOR = {NO_FLOOR, FIRST_FLOOR, SECOND_FLOOR=, THIRD_FLOOR, FOURTH_FLOOR}
enum NEXT_STATE = {STOP, CONTINUE};
