#include <stdio.h>
#include "elevator_fsm.h"
#include "hw.h"
#include "timer.h"
#include "queue.h"



void main() {
	int lights[15] = {0};                       //0-3 elev light, 4-6 button up light, 7-9 button down light, 10-13 indicator light, 14 stop button light
        int order_buttons[10] = {0};            //0-3 elev buttons, 4-6 button up, 7-9 button down
        int floor_indicators[4] = {0};          //0-3 floor indicator sensors
	int direction = 0;
	int current floor = hw_get_floor();
	

        // Initialize hardware
        if (!elev_init()) {
                printf("Unable to initialize elevator hardware!\n");
                return 1;
         }

        // initialiserer heis (koen)
        fsm_elev_on();
        
	while (1) {
		int floor_ordered = fsm_get_order();
		if (floor_ordered>current_floor) {
			direction = hw_set_direction(1);
		} else if (floor_ordered<current_floor) {
			direction = hw_set_direction(-1);
		}
		current_floor = hw_get_floor();
		while (current_floor != floor_ordered) {
		
	        }

		while (floor_ordered == 0) {
		
		}

	
        }
	return 0;
}







        while(1) {

        while(!timer_is_time_out()){
                ....

        while(hw_get_stop_button_status()){
                hw_set_direction(0);
                fsm_stop_button_pressed();
                hw_set_stop_button_light(1);
                if (hw_get_floor() != -1) {
                    hw_open_door();
                }

        }

        while (!hw_get_stop_button_status() &&  ) {
            hw_set_stop_button_light(0);

        hw_set_direction(1);


