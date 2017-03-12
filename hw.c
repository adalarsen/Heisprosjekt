#include <stdio.h>
#include "elev.h"



//DOOR FUNCTIONS
/*******************************
*resets the door light.
*******************************/
void hw_close_door() {
   // printf("kjører hw_close_door\n");
    elev_set_door_open_lamp(0);
}


/*******************************
*opens door by setting the door lamp if the elevator is at a floor and standing still. 
*******************************/
void hw_open_door() {
        printf("kjører hw_open_door\n");
        if (elev_get_floor_sensor_signal() != -1) {     //catches possible glitch in case open door is called and the elevator is running or inbetween floors
            elev_set_door_open_lamp(1);
		}
		else {
			elev_set_door_open_lamp(0);
		}
}




//STOP BUTTON FUNCTIONS
/*******************************
*turns the stop button light on if value 1 and off if value 0.
*******************************/
void hw_set_stop_button_light(int value) {
    // printf("kjører hw_set_stop_button_light\n");
     elev_set_stop_lamp(value);
}


/*******************************
*returns 1 if the stop button is pushed and 0 if not.
*******************************/
int hw_get_stop_button_status() {
 //	printf("kjører hw_get_stop_button_status\n");
    return elev_get_stop_signal();
}






//GET FUNCTIONS
/******************************
*returns 1-4 if on a floor, 0 if between floors.
******************************/
int hw_get_floor(){
  //	printf("kjører hw_get_floor\n");
	return elev_get_floor_sensor_signal();
}


/******************************
*checks all the buttons on a given floor and returns up (1), down (-1), both (2) or none (0).
*the returned value will be stored in the global variable 'direction'
******************************/
int hw_get_floor_button_status(int floor) {
 // printf("kjører hw_get_floor_button_status\n");
    if (floor != 3 && floor != 0) {
        if (elev_get_button_signal(BUTTON_CALL_DOWN,floor) == 1  &&
            elev_get_button_signal(BUTTON_CALL_UP,floor)== 1) return 2;    
    }if (floor != 3) {
        if (elev_get_button_signal(BUTTON_CALL_UP,floor) == 1) return 1;
    }if (floor != 0) {
        if (elev_get_button_signal(BUTTON_CALL_DOWN, floor) == 1) return -1;        
    }
    return 0;								      
}


/*******************************
*checks if an ordering button inside the elevator is pushed at a given floor.
*returns 1 if ordered and 0 if not. 
*******************************/
int hw_get_elev_button_status(int floor) {
 // printf("kjører hw_get_elev_button_status\n");
	return elev_get_button_signal(BUTTON_COMMAND, floor);
}







//SET FUNCTIONS
/*******************************
*sets the direction of the motor to up (1), down (-1) or stop (0). 
*******************************/
elev_motor_direction_t hw_set_direction(elev_motor_direction_t direction) {							
//	printf("kjører hw_set_direction\n");
        switch(direction) {
		case DIRN_UP:
		elev_set_motor_direction(DIRN_UP);
		printf("kjører opp %d \n",DIRN_UP);
		return DIRN_UP;
		case DIRN_STOP:
		elev_set_motor_direction(DIRN_STOP);
		return DIRN_STOP;
		case DIRN_DOWN:
		elev_set_motor_direction(DIRN_DOWN);
		return DIRN_DOWN;
		default:
		elev_set_motor_direction(DIRN_STOP);
		return DIRN_STOP;
}
}


/*******************************
*sets the floor indicator light. this function automatically turns off all other light if another is set.
*******************************/
void hw_set_floor_indicator_light(int floor) {
 // printf("kjører hw_set_floor_indicator_light\n");
    if (floor != -1)  elev_set_floor_indicator(floor);
   }


/*******************************
*sets the light inside the elevator to off if the elevator has arrived at the ordered floor.
*turns the light on if a order has been placed in the floor. 
*******************************/
void hw_set_elev_button_light(int floor) {
 // printf("kjører hw_set_elev_button_light\n");
  if (hw_get_stop_button_status()) {
    elev_set_button_lamp(BUTTON_COMMAND, floor, 0);
  } else if (elev_get_floor_sensor_signal() == floor) {					
    elev_set_button_lamp(BUTTON_COMMAND,floor,0);				
  } else {
    elev_set_button_lamp(BUTTON_COMMAND,floor,1);
  }
}


/*******************************
*sets the floor button lights depending on which button is pushed and on and off depending on value.
*******************************/
void hw_set_floor_button_light(int floor, int buttons_pressed, int value) {              			
 // printf("kjører hw_set_floor_button_light\n");
 // printf("button = %d", button);
  if (buttons_pressed == 0) {        //if the up button is pushed
    if (floor != 3) {
      elev_set_button_lamp(BUTTON_CALL_UP, floor, value);
    }
  } else if (buttons_pressed == 1) {			 
        if (floor != 0) {
        elev_set_button_lamp(BUTTON_CALL_DOWN, floor, value);
    }
  } else if (buttons_pressed == 2) {
      if (floor!=0 && floor!=3) {
            elev_set_button_lamp(BUTTON_CALL_DOWN, floor, value);
            elev_set_button_lamp(BUTTON_CALL_UP, floor, value);
      }
}
}







