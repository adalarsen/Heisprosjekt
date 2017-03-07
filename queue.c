#include "queue.h"
#include "elevator_fsm.h"

int orders[10] = {0} //order queue. 0-3: order buttons inside the elevator, 4-6: up buttons,7-9: down buttons



/************************************
*returns 1 if there is an order on current_floor
************************************/
int q_check_floor(FLOOR current_floor) {
	switch(current_floor) {
		case 1:
			if (orders[0]==1 || orders[4]==1) {			//check orders on first floor
				return 1;
			}
			return 0;
		case 2:
			if (orders[1]==1 || orders[5]==1 || orders[7]==1) {	//check second floor
				return 1;
			}
			return 0;
		case 3:
			if (orders[2]==1 || orders[6]==1 || orders[8]==1) {	//check third floor
				return 1;
			}
			return 0;
		case 4:
			if (orders[3]==1 || orders[9]) {			//check fourth floor
				return 1;
			}
		
		default:
			return 0;
	}
}









//DELETE FUNCTIONS
/************************************
*deletes all orders on current_floor
************************************/
void q_delete_order(FLOOR current_floor){					
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





/************************************
*delete all orders in the order queue
************************************/
void q_delete_all(){														
	for (int i=0;i<10;i++) {
		orders[i]=0;
	}
}







//GET AND STORE FUNCTIONS
/***********************************
*return the floor where the next order to be executed is
*function will loop in main when the elevator reaches a floor, therefore it cannot be used if elevator is on NO_FLOOR (0) 
***********************************/
FLOOR q_get_order(FLOOR current_floor, elev_motor_direction_t current_direction){    
	if (q_check_floor(current_floor)) {					//check if there is an order on the elevator's current floor
        	if (orders[current_floor-1]) {					//returns the current floor if there is an order from inside the elevator to stop on that floor
            		return current_floor; 
        } else if (current_direction == DIRN_UP && (current_floor != FOURTH_FLOOR)) {	//stop if there is an order from outside the elevator in the same direction as the current direction (up) 
            	if (orders[current_floor + 3]) {
                	return current_floor;
            	}
        } else if ((current_direction == DIRN_DOWN) && (current_floor !=FIRST_FLOOR)) {	//stop if there is an order from outside the elevator in the same direction as the current direction (down) 
            	if (orders[current_floor + 6]) {
                	return current_floor;
                }
        } else if (current_direction == DIRN_STOP) {					//stop if the elevator is in idle and on a floor, and there is a new order on that floor 
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

    	if (current_direction == DIRN_STOP) {						//search for a new order if the elevator is in idle and the order queue is empty
            	for (int i=0;i<10;i++) {
            		if(orders[i]==1){
                		switch(i) {
                    			case 0:
                                        case 4:
                                                return FIRST_FLOOR;
					case 1:
                    			case 5:
                    			case 7:
                        			return SECOND_FLOOR;
                   			case 2:
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
    	
	if (current_direction == DIRN_UP) {						//check up buttons
		for (int i=4; i<7; i++) {
			if (orders[i]==1) {
				return i-3;					//return the floor where the up button is pushed
			}
		}	
	}
	
	if (current_direction == DIRN_DOWN) {						//check down buttons
		for (int i=7; i<10; i++) {
			if (orders[i]==1) {
				return i-5;					//return the floor where the down button is pushed
			}
		}
	}
	return NO_FLOOR;
}




/************************************
*stores a new order in the order queue at index button_pressed
************************************/
void q_store_order(int new_order){ 	
	orders[new_order-1] = 1;							//button_pressed is the index of an order button in the order_buttons array in main
}











