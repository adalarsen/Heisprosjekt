#include <stdio.h>
#include "elev.h"
#include "queue.h"
#include "elevator_fsm.h"
#include "hw.h"
#include "timer.h"



/*******************************
*constants keeping track of what floor the elevator is at or last passed, and which state it is currently in
*******************************/
floor_t current_floor = NO_FLOOR;
state_t current_state = INIT;
elev_motor_direction_t direction;




//INITIALIZE
/*******************************
*initizaling the elevator by moving the elevator to floor 1. 
*******************************/
int fsm_init() {
	printf("kjører fsm_init\n");
        if (!elev_init()) { 									//initialize hardware
                printf("Unable to initialize elevator hardware!\n");
                return 1;   
    }
	floor_t floor = hw_get_floor(); 
	while(floor != FIRST_FLOOR) {								//move elevator to 1st floor
		direction = hw_set_direction(DIRN_DOWN);
		floor = hw_get_floor();
                hw_set_floor_indicator_light(floor);
                
	}
	direction = hw_set_direction(DIRN_STOP);
        current_floor = floor;
        hw_set_floor_indicator_light(current_floor);
        q_delete_all();										//delete all orders in the order queue
	current_state = IDLE;    //when elevator har reached the 1st floor it is in idle and ready to take orders
    return 0;
}


/*******************************
*returns next order to main
*******************************/
int fsm_get_order() {
  //      printf("kjører fsm_get_order\n");
        return q_get_order(current_floor, direction);
}








//ORDER AND FLOOR FUNCTIONS
/*******************************
*checks to see if the current floor is in the queue. if so delete from queue.
*updates current_floor
*******************************/
void fsm_floor_reached(floor_t floor){
//	printf("kjører fsm_floor_reached\n");
        current_floor = floor;
        hw_set_floor_indicator_light(current_floor);
	if (q_check_floor(current_floor)) {     					//check if there are any orders on current_floor
		int button = hw_get_floor_button_status(current_floor);
        if ((direction) == button || button==2 || (direction==0)){
            switch (current_state) {
				case RUN:
					direction = hw_set_direction(DIRN_STOP);
                    hw_set_elev_button_light(current_floor);
                    hw_set_floor_button_light(current_floor, button, 0);
                    q_delete_order(current_floor);
                    hw_open_door();
                    timer_start();
					current_state = DOOROPEN;
                                break;
			case IDLE:
				direction = hw_set_direction(DIRN_STOP);
				hw_set_elev_button_light(current_floor);
                                hw_set_floor_button_light(current_floor, button, 0);
                                q_delete_order(current_floor);
                                hw_open_door();
				timer_start();
				current_state = DOOROPEN;
                                break;
			case INIT:
				hw_set_elev_button_light(current_floor);
                                hw_set_floor_button_light(current_floor, button, 0);
                                q_delete_order(current_floor);
                                hw_open_door();
				timer_start();
				current_state = DOOROPEN;
                                break;
			case STOPBUTTON:
                                break;
			case DOOROPEN:
                                hw_set_elev_button_light(current_floor);
                                hw_set_floor_button_light(current_floor, button, 0);
				break;
		}
                }
	}
}

		
/*******************************
*setter retningen mot etasjen hvor den neste bestillingen er
*******************************/
void fsm_order_exists() {
  //      printf("kjører fsm_order_exists\n");
	floor_t new_order = q_get_order(current_floor, direction);
        int button = hw_get_floor_button_status(new_order);
	int to_floor = current_floor - new_order;				//check if elevator is below or above the ordered floor
		if (to_floor<0) {						//if elevator is below 
			switch(current_state) {
				case RUN:
				case IDLE:
				case INIT:
					direction = hw_set_direction(DIRN_UP);
					hw_set_elev_button_light(new_order);
                                        if (button!=0) {
                                            hw_set_floor_button_light(new_order, button, 1);
                                        }
                                        current_state = RUN;
					break;
				case DOOROPEN:
					hw_close_door();
					direction = hw_set_direction(DIRN_UP);
					hw_set_elev_button_light(new_order);
                                        if (button!=0) {
                                            hw_set_floor_button_light(new_order, button, 1);
                                        }
                                        current_state = RUN;
					break;
				case STOPBUTTON:
					break;
			}
		} else if (to_floor>0) {					//if elevator is above
			switch(current_state) {
                                case RUN:
                                case IDLE:
                                case INIT:
                                        direction = hw_set_direction(DIRN_DOWN);
                                        hw_set_elev_button_light(new_order);
                                        if (button!=0) {
                                            hw_set_floor_button_light(new_order, button, 1);
                                        }
                                        current_state = RUN;
                                        break;
                                case DOOROPEN:
                                        hw_close_door();
                                        direction = hw_set_direction(DIRN_DOWN);
                                        hw_set_elev_button_light(new_order);
                                        if (button!=0) {
                                            hw_set_floor_button_light(new_order, button, 1);
                                        }
                                        current_state = RUN;
                                        break;
                                case STOPBUTTON:
                                        break;
                        }
		} else if (to_floor == 0) {
			switch(current_state) {
                                case IDLE:
                                        direction = hw_set_direction(DIRN_STOP);
					break;
                                case RUN:
                                case INIT:
                                case DOOROPEN:
                                        direction = hw_set_direction(DIRN_STOP);
                                        current_state = IDLE;
                                        break;
                                case STOPBUTTON:
                                        break;
                        }
		}
	
}


/*******************************
*stores a new order when button is pressed
*******************************/
void fsm_button_pressed(int button_pressed) {                                                     //convert to 1-4 index
//	printf("kjører fsm_button_pressed\n");
        switch(current_state) {
		case IDLE:
		case RUN:
		case DOOROPEN:
		case INIT:
			q_store_order(button_pressed);
                        switch (button_pressed) {
                            case 0:
                            case 1:
                            case 2:
                            case 3:
                                hw_set_elev_button_light(button_pressed);
                                break;
                            case 4:
                            case 5:
                            case 6:
                                hw_set_floor_button_light(button_pressed-4, BUTTON_CALL_UP, 1);
                                break;
                            case 7:
                            case 8:
                            case 9:
                                hw_set_floor_button_light(button_pressed-6, BUTTON_CALL_DOWN, 1);
                                break;
                            }
			break;
		case STOPBUTTON:
			break;
}
}










//STOP BUTTON FUNCTIONS
/********************************
*deletes all orders in the queue if the stop button is pushed.
*******************************/
void fsm_stop_button_pressed(){		
//  printf("kjører fsm_stop_button_pressed\n");
  q_delete_all();
  hw_set_stop_button_light(1);
  for (int i=0;i<4;i++) {
    hw_set_elev_button_light(i);
    hw_set_floor_button_light(i,2,0);
  }
	switch(current_state) {
		case RUN:
		case IDLE:
                case INIT:
			direction = hw_set_direction(DIRN_STOP);
                        if (hw_get_floor() != NO_FLOOR) {
                                hw_open_door();
                        } else {
				hw_close_door();
			}
			while(hw_get_stop_button_status()) {};
                        current_state = STOPBUTTON;
			break;
                case DOOROPEN:
			direction = hw_set_direction(DIRN_STOP);
			hw_open_door();
                        current_state = STOPBUTTON;
			break;
                case STOPBUTTON:
			current_state = STOPBUTTON;
			break;
	}
}


/*******************************
*deletes all orders in the queue if the stop button is pushed.
*******************************/
void fsm_stop_button_released() {
       // printf("kjører fsm_stop_button_released\n");
	hw_set_stop_button_light(0);
	switch(current_state) {
		case STOPBUTTON:
			hw_close_door();
			current_state = IDLE;
			break;
		case IDLE:
		case INIT:
		case RUN:
		case DOOROPEN:
			hw_close_door();
			direction = hw_set_direction(DIRN_STOP);
			current_state = IDLE;
			break;
	}
}


/*******************************
*checks if the stop button is pressed. Returns  1 if yes, 0 if no.
*******************************/
int fsm_is_stop_button_pressed() {
     //   printf("kjører fsm_is_stop_button_pressed\n");
	return hw_get_stop_button_status();
}






//INDICATOR LIGHTS
/*******************************
*sets a new indicator light every time a floor is reached.
*******************************/
void fsm_set_indicator(int floor) {
   //     printf("kjører fsm_set_indicator\n");
	hw_set_floor_indicator_light(floor);
}





//TIMER FUNCTION
/*******************************
*checks if 3 seconds has passed
*******************************/
void fsm_time_out() {
 // printf("kjører fsm_time_out\n");
  switch (current_state) {
    case DOOROPEN:
      hw_close_door();
      break;
    case RUN:
    case IDLE:
    case STOPBUTTON:
    case INIT:
      break;
    }
}

