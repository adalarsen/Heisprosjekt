#include "elev.h"

void hw_close_door() {                                                                  //resetter dorlyset
                if ((elev_get_floor_sensor_signal() != -1) && (DIRN_STOP == 0)) {
                elev_set_door_open_lamp(0);
}
}


int hw_open_door() {                                                                    //set door light
        if ((elev_get_floor_signal() != -1)
		elev_set_door_open_lamp(1);
}	else {
                elev_set_door_open_lamp(0);
}
}


int hw_get_floor(){									//return 0-3 if on a floor, ...
	return elev_get_floor_sensor_signal();
}


int hw_get_floor_button_status(int floor) { 						//sjekker bestillingsknapp opp og ned utenfor heisen i en gitt etasje (floor)
	if (elev_get_button_signal(BUTTON_CALL_DOWN, floor) == 1 && elev_get_button_signal(BUTTON_CALL_UP, floor) == 1) {			
		return 2;								//dersom baade opp og ned er trykket i samme etasje, skjer prioriteringen av hvilken retning heisen skal
}												//fortsette i utenfor hw_funksjonene (altså i main)
	else if (elev_get_button_signal(BUTTON_CALL_UP, floor) == 1) {			//sjekker opp-bestilling paa floor
                return 1;
}
	else if (elev_get_button_signal(BUTTON_CALL_DOWN, floor) == 1) {		//sjekker ned_bestilling paa floor
		return -1;
}	
	else {
		return 0;								//dersom verken ned eller opp er bestilt på floor
}
}

int hw_get_elev_button_status(int floor) {						//sjekker om bestillingsknapp inne i heisen er trykket for floor
	return elev_get_button_signal(BUTTON_COMMAND, floor);
}



void hw_set_direction(int direction) {							//setter retning på motoren til opp, ned eller stopp
	switch(direction) {
		case 1:
		elev_set_motor_direction(DIRN_UP);
		break;
		case 0:
		elev_set_motor_direction(DIRN_STOP);
		break;
		case -1:
		elev_set_motor_direction(DIRN_DOWN);
		break;
		default:
		elev_set_motor_direction(DIRN_STOP);
}
}


void hw_set_floor_indicator_light(int floor) {						//setter lyset i etasjeindikatorene
    elev_set_floor_indicator(floor);
	return 0;
}


void hw_set_elev_button_light(int floor) {						//setter lyset i bestillingsknappene inne i heisen
	if (elev_get_floor_sensor_signal() == floor) {					//returnerer 0-3 for etasjer og -1 for ingen etasje
		elev_set_button_lamp(BUTTON_COMMAND,floor,1);				
}	else {
		elev_set_button_lamp(BUTTON_COMMAND,floor,value)
}


void hw_set_stop_button_light(int value) {               				//set stop button light to 1 for on and 0 for off
          elev_set_stop_lamp(value);
}


int hw_get_stop_button_status() {				                        //return 1 if stop button is pushed
        return elev_get_stop_signal();
}


void hw_set_floor_button_light(int floor, int button, int value) {              				//set light if floor buttons are pushed
	if (button == 2) {
		elev_set_button_lamp(BUTTON_CALL_UP, floor, value);
		elev_set_button_lamp(BUTTON_CALL_DOWN, floor, value);
}
	else if (button == 1) {
		elev_set_button_lamp(BUTTON_CALL_UP, floor, value);
}
	else if (button == -1) {
		elev_set_button_lamp(BUTTON_CALL_DOWN, floor, value);
}



 if (elev_get_button_signal(BUTTON_CALL_DOWN, floor) == 1 && elev_get_button_signal(BUTTON_CALL_UP, floor) == 1) {
                return 2;                                                               //dersom baade opp og ned er trykket i samme etasje, skjer prioriteringen av hvilken retning heisen skal
}                                                                                               //fortsette i utenfor hw_funksjonene (altså i main)
        else if (elev_get_button_signal(BUTTON_CALL_UP, floor) == 1) {                  //sjekker opp-bestilling paa floor
                return 1;
}
        else if (elev_get_button_signal(BUTTON_CALL_DOWN, floor) == 1) {                //sjekker ned_bestilling paa floor
                return -1;
}
        else {
                return 0;                                                               //dersom verken ned eller opp er bestilt på floor
}








