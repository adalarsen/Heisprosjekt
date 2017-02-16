#include "fsm.h"
#include "hw.h"
#include "elev.h"
#include "queue.h"
#include "timer.h"
#include "queue.h"

void fsm_elev_on(){
	int GROUND = 0;
	elev.init();	
	int correct_floor = q_check_floor(GROUND_FLOOR);
	while (correct_floor == GROUND_FLOOR) {
		hw_set_direction(-1);
		correct_floor = q_check_floor(GROUND_FLOOR);
	}
	hw_set_direction(0);
}

void fsm_floor_button_pressed(){

}

void fsm_elev_button_pressed(){

}

void fsm_is_on_floor(int floor){
	hw_set_floor_light(floor);
	if (q_check_floor(floor) != floor) {
		break;
	}
	hw_set_direction(0);
	hw_open_door();
	timer_on();
	while (!timer_is_time_out()) {
		
	}
	hw_close_door();		
}

void fsm_stop_button_pressed(int floor){
	order_description temp_element = q_get_order(); //hent ut forste element fra queuen som trengs for at heisen skal huske hvor den er etter stoppknappen slippes
	while (hw_get_stop_button_status()!=0) {
		hw_set_direction(0);
		hw_set_stop_button_light(1);
		q_delete_all();
		for (int i=GROUND_FLOOR; i<N_FLOORS; i++) {
			hw_set_elev_light(i, 0);
			hw_set_floor_button_light(i, 0);
		}
		if (floor != NO_FLOOR) {
			hw_open_door();
		}
	}
	q_store_order(temp_element);
	hw_set_stop_button_light(0);
	hw_close_door();
}
