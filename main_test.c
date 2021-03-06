#include <stdio.h>
#include "elevator_fsm.h"
#include "hw.h"
#include "timer.h"
#include "queue.h"



void main() {
	
	
        int order_buttons[10] = {0};            //0-3 elev buttons, 4-6 button up, 7-9 button down

        // Initialize hardware
    int sweet_deal =  fsm_init();
    printf('sweet: %d',sweet_deal);
	while (1) {


            //save orders
            int order_buttons[10] = {0};            //0-3 elev buttons, 4-6 button up, 7-9 button down
            for (int i=0; i<4; i++) {
                order_buttons[i] = hw_get_elev_button_status(i+1);
                if (order_buttons[i]==1) {
                  fsm_button_pressed(i);
                }
                int button = hw_get_floor_button_status(i+1);
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
            int previous_order = -1;
            int next_order = fsm_get_order();
            if ((next_order != previous_order) && next_order!=0) {
              fsm_order_exists();
            }
            previous_order = next_order;



            //check if previous correct floor is reached
            int previous_correct_floor = -1;
            int floor = hw_get_floor();
            if ((floor!=0) && (floor!=0)) {
              fsm_floor_reached(floor);
            }
            previous_correct_floor = floor;


            //check time
            int previous_time_out;
            int time = timer_is_time_out();
            if (time != previous_time_out) {
              if (time) {
                fsm_is_time_out();
              }
            }
            previous_time_out = time;



            //check stop button
            int previous_stop_button;
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







