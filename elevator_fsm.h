#include "elev.h"
#include "queue.h"


void fsm_elev_on(); 					//initializes the queue
int fsm_update_floor(int floor);		//updates the queue when a new floor is passed
void fsm_stop_button_pressed();			//deletes all entries in the queue when the stop button is pushed
