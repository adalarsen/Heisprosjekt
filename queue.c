#include "queue.h"
#include "elevator_fsm.h"

int orders[10] = {0} //0-3: ordering buttons inside the elevator, 4-6: up buttons,7-9: down buttons

int q_check_floor(int current_floor) {				 //tar inn etasjen den er i, sjekker i orders om gjeldende etasje er bestilt
	switch(current_floor) {
		case 1:
			if (orders[0]==1 || orders[4]==1) {
				return 1;
			}
			return 0;
		case 2:
			if (orders[1]==1 || orders[5]==1 || orders[7]==1) {
				return 1;
			}
			return 0;
		case 3:
			if (orders[2]==1 || orders[6]==1 || orders[8]==1) {
				return 1;
			}
			return 0;
		case 4:
			if (orders[3]==1 || orders[9]) {
				return 1;
			}
			return 0;
	}
}

void q_delete_order(int current_floor){				//deletes all orders in a given floor
	switch(current_floor) {
		case 1: 
            orders[0]=0;
			orders[4]=0;
			break;
                case 2:
			orders[1]=0;
			orders[5]=0;
			orders[7]=0;
			break;
                       
                case 3:
			orders[2]=0;
			orders[6]=0;
			orders[8]=0;
                    	break;

                case 4:
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

int q_get_order(int current_floor, int current_direction){
    if (hw_check_floor(current_floor)) {
        if (orders[current_floor-1]) {
            return current_floor; 
        }
        else if (current_direction && (current_floor != FOURTH_FLOOR)) {
            if (orders[current_floor + 3]) {
                return current_floor;
            }
        }
        else if ((current_direction==-1) && (current_floor !=FIRST_FLOOR)) {
            if (orders[current_floor + 6]) {
                return current_floor;
                }
        }
        else if (current_direction == 0) {
            switch (current_floor) {
                case 1:
                    if (orders[0] || orders[4]) {
                        return FIRST_FLOOR;
                    }
                case 2:
                case 3:
                    if (orders[current_floor + 3] || orders[current_floor + 6]) {
                        return current_floor;
                    }
                case 4:
                    if (orders[3] || orders[9]) {
                        return FOURTH_FLOOR;
                    }
                }
         }
    }
    

    if (current_direction == 0) {
            for (int i=0;i<10;i++) {
            if(orders[i]==1){
                switch(i) {
                    case(1):
                    case(5):
                    case (7):
                        return SECOND_FLOOR;
                    case(0):
                    case(4):
                        return FIRST_FLOOR;
                    case(2):
                    case(6):
                    case(8):
                        return THIRD_FLOOR;
                    case(3):
                    case(9):
                        return FOURTH_FLOOR;
                }
            }
        }
    return NO_FLOOR;
    }
    if (current_direction) {

}

    if (hw_check_floor(current_floor)) {
        if current_direction    

void q_store_order(int button_pressed){ //lagrer en ny bestilling i koen
	orders[button_pressed] = 1;
}
