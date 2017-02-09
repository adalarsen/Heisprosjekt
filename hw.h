#include "elev.h"
#include "io.h"
#include "elevator_fsm.h"
#include <stdio.h>



int hw_close_door();

int hw_get_floor();

int hw_set_direction(int direction);

int hw_open_door();

int hw_get_elev_button_status(int floor);

int hw_get_floor_button_status(int floor);

int hw_set_elev_light(int floor);

int hw_set_stop_button_light(int value);

int hw_get_stop_button_status();


