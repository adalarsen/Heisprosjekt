#include <stdio.h>
#include "elevator_fsm.h"
#include "hw.h"
#include "timer.h"
#include "queue.h"



int main() {
	
	
        int order_buttons[10] = {0};            //0-3 elev buttons, 4-6 button up, 7-9 button down
          
        // Initialize hardware
   
        int sweet_deal =  fsm_init();
        printf("fnutt %d", sweet_deal);
        while (1) {


            //save orders
       //     int order_buttons[10] = {0};            //0-3 elev buttons, 4-6 button up, 7-9 button down
            for (int i=0; i<4; i++) {
                order_buttons[i] = hw_get_elev_button_status(i);
                if (order_buttons[i]==1) {
                  fsm_button_pressed(i);
                }
                int button = hw_get_floor_button_status(i);
                if (button==2) {
                  order_buttons[i+4]=1;
                  order_buttons[i+6]=1;
                  fsm_button_pressed(i+4);
                  fsm_button_pressed(i+6);
                } else if (button) {
                  order_buttons[i+4]=1;
                  fsm_button_pressed(i+4);
                } else if (button==-1) {
                  order_buttons[i+6]=1;
                  fsm_button_pressed(i+6);
                }
            }
            

            //check if order exists
            int previous_order = NO_FLOOR;
            int next_order = fsm_get_order();
            if ((next_order != previous_order) && next_order!=NO_FLOOR) {
              fsm_order_exists();
            }
            previous_order = next_order;



            //check if previous correct floor is reached
            int previous_correct_floor = NO_FLOOR;
            int floor = hw_get_floor();
            if ((floor!=NO_FLOOR) && (floor!=previous_correct_floor)) {
              fsm_floor_reached(floor);
            }
            previous_correct_floor = floor;


            //check time
            int previous_time_out = 0;
            int time = timer_is_time_out();
            if (time != previous_time_out){
              if (time) {
                fsm_time_out();
              }
            }
            previous_time_out = time;



            //check stop button
            int previous_stop_button = 0;
            int stop = fsm_is_stop_button_pressed();
            if (stop!=previous_stop_button) {
              if (stop) {
                fsm_stop_button_pressed();
              } else {
                fsm_stop_button_released();
              }
            }
            previous_stop_button = stop;

	}
	return 0;
}







