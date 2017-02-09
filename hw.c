#include "elev.h"

int hw_get_floor_button_status(int floor) {
	if (elev_get_button_signal(BUTTON_CALL_UP, floor) == 1) {
		return 1;
}
	else if (elev_get_button_signal(BUTTON_CALL_DOWN, floor) == 1) {
		return -1;
}	
	else {
		return 0;
}
}

int hw_get_elev_button_status(int floor) {
	if (elev_get_button_signal(BUTTON_COMMAND, floor) == 1) {
		return 1;
}
	else {
		return 0;
}
}

int hw_open_door() {
	if ((elev_get_floor_sensor_signal(void) != -1) && (DIRN_STOP == 0)) {
		elev_set_door_open_lamp(1);
		return 1;
}
	else {
		return -1;
}
}

int hw_close_door() {
		if ((elev_get_floor_sensor_signal(void) != -1) && (DIRN_STOP == 0)) {
		elev_set_door_open_lamp(0);
		return 1;
}
	else {
		return -1;
}

int hw_set_direction(int direction) {
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
	return -1;
}

int hw_set_floor_light() {

}

