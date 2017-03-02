#include "queue.h"
#include "elevator_fsm.h"

int orders[10] = {0} //0-3: ordering buttons inside the elevator, 4-6: up buttons,7-9: down buttons

int q_check_floor(int current_floor) {				 //tar inn etasjen den er i, sjekker i orders om gjeldende etasje er bestilt
	switch(current_floor) {
		case 0:
			if (orders[0]==1 || orders[4]==1) {
				return 1;
			}
			return 0;
		case 1:
			if (orders[1]==1 || orders[5]==1 || orders[7]==1) {
				return 1;
			}
			return 0;
		case 2:
			if (orders[2]==1 || orders[6]==1 || orders[8]==1) {
				return 1;
			}
			return 0;
		case 3:
			if (orders[3]==1 || orders[9]) {
				return 1;
			}
			return 0;
	}
}

void q_delete_order(int current_floor){				//deletes all orders in a given floor
	switch(current_floor) {
		case 0:
                        orders[0]=0;
			orders[4]=0;
			break;
                case 1:
			orders[1]=0;
			orders[5]=0;
			orders[7]=0;
			break;
                       
                case 2:
			orders[2]=0;
			orders[6]=0;
			orders[8]=0;
                    	break;

                case 3:
			orders[3]=0;
			orders[9]=0;
                        break;
	}
}

void q_delete_all(){
	for (int i=0;i<10;i++) {
		orders[i]=-1;
	}
}

int q_get_order(){
	if (q_check_floor(0)==1) {
		if (orders[0]==1 || orders[4]==1) {
			return 0;
		else if (orders[2]=
		
		}
	}
}

void q_store_order(int button_pressed){ //lagrer en ny bestilling i koen
	orders[button_pressed] = 1;
}
