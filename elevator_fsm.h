#include "elev.h"
#include "queue.h"



typedef enum {FIRST, SECOND, THIRD, FORTH, FIRST_UP, SECOND_UP, THIRD_UP, SECOND_DOWN, THRID_DOWN, FORTH_DOWN} ELEV_BUTTONS;	//enum stating the elev button constants
typedef enum {UP = 1, DOWN = -1, STOP = 0} DIRECTIONS;																			//enum stating the elevator directions
typedef enum {NO_FLOOR, FIRST_FLOOR, SECOND_FLOOR, THIRD_FLOOR, FOURTH_FLOOR} FLOOR;											//enum stating the names of the elevator floors
typedef enum {IDLE, RUN, DOOROPEN, STOPBUTTON, INIT} STATE;																		//enum stating the next state of the elevator


void fsm_elev_on(); 					//initializes the queue
int fsm_update_floor(int floor);		//updates the queue when a new floor is passed
void fsm_stop_button_pressed();			//deletes all entries in the queue when the stop button is pushed
int fsm_get_order();					//returns the next order from queue


//Forslag til oppsett

/*
fsm_order_exists 
fsm_correct_floor_reached (samme som updatE_floor i grunn)
fsm_button_pressed (
fsm_timer (tar seg av all tid i main) 
fsm_stop_button_pressed (samme som den me har fra før)
fsm_stop_button_released (for å skru av lyset, og gå til ny etasje osv) 
fsm_set_indicator (for å oppdatere hver gang heisen når en ny etasje)

Dersom me faktisk ska bruke fsm som en faktisk state machine så foreslår eg at me sette opp alle funksjonene slik at de inneholde en switch 
slik at for eksempel:

fsm_button_pressed() {
	switch(current_state) {
		case idle:
		case stop:
		case run: osv
}}
*/