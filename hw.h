#include "elev.h"
#include "io.h"
#include <stdio.h>



void hw_close_door();					//reset door light

void hw_open_door();                                    //set door light

int hw_get_floor();					//return 0-3 if elevator is on a floor, -1 if between floors, above 4th floor or below 1st floor

void hw_set_direction(int direction);			//set motor direction to 1 for up, -1 for down and 0 for stop

int hw_get_elev_button_status(int floor);		//return 1 if elevator button is pushed for floor between 0-3, return 0 if not 

int hw_get_floor_button_status(int floor);		//return 1 if floor button for up is pushed, -1 for down, 2 if both are pushed at the same time and 0 if none are pushed

void hw_set_elev_button_light(int floor);		//set light in elevator button if the correct button for floor is pushed

void hw_set_stop_button_light(int value);		//set stop button light to 1 for on and 0 for off

int hw_get_stop_button_status();			//return 1 if stop button is pushed

void hw_set_floor_indicator_light(int floor);		//set elevator indicator light for floor

void hw_set_floor_button_light(int floor, int button, int value);		//set light in floor buttons if pushed
