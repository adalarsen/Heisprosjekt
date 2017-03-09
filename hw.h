#ifndef HW.H
#define HW.H
#include "elev.h"
#include <stdio.h>


//DOOR FUNCTIONS
void hw_close_door();					//reset door light
void hw_open_door();                                    //set door light



//STOP BUTTON FUNCTIONS
int hw_get_stop_button_status();                        //return 1 if stop button is pushed
void hw_set_stop_button_light(int value);               //set stop button light to 1 for on and 0 for off



//GET FUNCTIONS
int hw_get_floor();					//return 1-4 if elevator is on a floor, -1 if between floors, above 4th floor or below 1st floor
int hw_get_floor_button_status(int floor);                              //return 1 if floor button for up is pushed, -1 for down, 2 if both are         pushed at the same time and 0 if none are pushed
int hw_get_elev_button_status(int floor);               //returns 1-4 if on a floor, 0 if between floors.



//SET FUNCTIONS
elev_motor_direction_t hw_set_direction(elev_motor_direction_t direction);		//set motor direction to one of the elev_motor_direction_t types 
void hw_set_floor_indicator_light(FLOOR floor);         //set elevator indicator light for floor
void hw_set_elev_button_light(FLOOR floor);		//set light in elevator button if the correct button for floor is pushedi
void hw_set_floor_button_light(FLOOR floor, int button, int value);		//set light in floor buttons if pushed



#endif
