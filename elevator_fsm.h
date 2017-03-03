#include "elev.h"
#include "queue.h"



typedef enum {FIRST, SECOND, THIRD, FORTH, FIRST_UP, SECOND_UP, THIRD_UP, SECOND_DOWN, THRID_DOWN, FORTH_DOWN} ELEV_BUTTONS;	//enum stating the elev button constants
typedef enum {UP = 1, DOWN = -1, STOP = 0} DIRECTIONS;																			//enum stating the elevator directions
typedef enum {NO_FLOOR, FIRST_FLOOR, SECOND_FLOOR, THIRD_FLOOR, FOURTH_FLOOR} FLOOR;											//enum stating the names of the elevator floors
typedef enum {IDLE, RUN} NEXT_STATE;																							//enum stating the next state of the elevator


void fsm_elev_on(); 					//initializes the queue
int fsm_update_floor(int floor);		//updates the queue when a new floor is passed
void fsm_stop_button_pressed();			//deletes all entries in the queue when the stop button is pushed