#include <stdio.h>
#include "elevator_fsm.h"
#include "hw.h"
#include "timer.h"
#include "queue.h"



int main() {
//noe	
	
        int order_buttons[10] = {0};            //0-3 elev buttons, 4-6 button up, 7-9 button down
          
        // Initialize hardware
   
        int sweet_deal =  fsm_init();
        printf("sweet deal %d", sweet_deal);


		//Initialize constants
		int previous_order = NO_FLOOR;
		int previous_correct_floor = NO_FLOOR;
		int previous_time_out = 0;
		int previous_stop_button = 0;
//		int floor = NO_FLOOR;
//		int new_floor = NO_FLOOR;

        while (1) {
/*
		floor = hw_get_floor();
		printf("floor %d \n",floor);
		new_floor = hw_get_elev_button_status(floor);
		q_store_order(new_floor);
		int direction = hw_set_direction(1);
		int tentative_direction = 1;
		int ordered_floor = q_get_order(floor,tentative_direction);
		printf("Ordered floors: %d \n",ordered_floor);		
*/
            //save orders
       //     int order_buttons[10] = {0};            //0-3 elev buttons, 4-6 button up, 7-9 button down
            for (int i=0; i<4; i++) {
                int button_status = hw_get_elev_button_status(i);
				
               // printf("1. Oppdaterte queue.\n");
                if (button_status==1) {//	printf("2. Ser at etasjen er trykket");							//JENNY: Ser at når denne er 1 vil ikke heisen fullføre den fort nok slik at i=1 vil gå i all evighet. 
                    order_buttons[i] = 1;
					fsm_button_pressed(i);
                }
			}
			for (int i=0; i<4;i++) {
  //              printf("hello\n");
               int button = hw_get_floor_button_status(i);
    //            printf("hey hello %d \n",button);
//                  printf("check check\n");
               // if (button==1) {
				if (button == 1 || button == 2){
                  order_buttons[i+4]=1;
                  fsm_button_pressed(i+4); 
                }if (button==-1 || button == 2) {
                  order_buttons[i+6]=1;
                  fsm_button_pressed(i+6);
                }
            }
  //         printf("ferdig med å lagre bestillinger\n"); 
			
			
			//check time
            int time = timer_is_time_out();
            if (time != previous_time_out){
              if (time) {
                fsm_time_out();
				
              } 
            } 
        //    printf("ferdig med å sjekke om det har gått 3 sekunder\n");
            previous_time_out = time;

			
			// if door is open we will do NOTHING
			if (fsm_is_door_open()) { continue; }
			
            //check if order exists
            int next_order = fsm_get_order();
            if ((next_order != previous_order) && (next_order!=NO_FLOOR)) {
              fsm_order_exists();
            }
            previous_order = next_order;
    //        printf("ferdig med å få bestillinger\n");


            //check if previous correct floor is reached
            int floor = hw_get_floor();
            if (((floor!=NO_FLOOR) && (floor!=previous_correct_floor))/* || ((floor==previous_correct_floor) && (fsm_get_direction()==DIRN_STOP))*/) {
              fsm_floor_reached(floor);
            }
      //      printf("ferdig med fsm_floor_reached\n");
            previous_correct_floor = floor;


            //check stop button
            int stop = hw_get_stop_button_status();
            if (stop!=previous_stop_button) {
              if (stop) {
                fsm_stop_button_pressed();
				previous_stop_button = stop;
                fsm_stop_button_released();
				previous_stop_button = 0;
              }
            }
//            printf("ferdig med å sjekke om stoppknapp er trykket\n");

	}
	return 0;
}







