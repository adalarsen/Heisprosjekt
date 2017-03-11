#include <stdio.h>
#include "queue.h"
#include "elevator_fsm.h"

int orders[10] = {0}; //order queue. 0-3: order buttons inside the elevator, 4-6: up buttons,7-9: down buttons



/************************************
*returns 1 if there is an order on current_floor
************************************/
int q_check_floor(floor_t current_floor) {
//	printf("kjører q_check_floor\n");
	printf("\n");
	for (int i=0; i<10; i++) {
		printf("%d, ", orders[i]);
	}
	printf("\n");
	printf("%d\n", current_floor);
        switch(current_floor) {
		case NO_FLOOR:
            printf("no floor\n");
				break;
        case FIRST_FLOOR:
			printf("floor 1\n");
			if (orders[0]==1 || orders[4]==1) {
				return 1;
			} break;
		case SECOND_FLOOR:
			printf("floor 2\n");
			if (orders[1]==1 || orders[5]==1 || orders[7]==1) {
				return 1;
			} break;
		case THIRD_FLOOR:
			printf("floor 3\n");
			if (orders[2]==1 || orders[6]==1 || orders[8]==1) {
				return 1;
			} break;
		case FOURTH_FLOOR:
			if (orders[3]==1 || orders[9]==1) {	 
                          return 1;
			} break;

		default:
			return 0;
        }
        return 0;
}









//DELETE FUNCTIONS
/************************************
*deletes all orders on current_floor
************************************/
void q_delete_order(floor_t current_floor){
  //printf("kjører q_delete_order\n");
	switch(current_floor) {
        case NO_FLOOR:
            break;
        case FIRST_FLOOR: 
            orders[0]=0;
			orders[4]=0;
			break;
        case SECOND_FLOOR:
			orders[1]=0;
			orders[5]=0;
			orders[7]=0;
			break;
        case THIRD_FLOOR:
			orders[2]=0;
			orders[6]=0;
			orders[8]=0;
            break;
        case FOURTH_FLOOR:
			orders[3]=0;
			orders[9]=0;
            break;
	}
}





/************************************
*delete all orders in the order queue
************************************/
void q_delete_all(){
//  printf("kjører q_delete_all\n");
	for (int i=0;i<10;i++) {
		orders[i]=0;
	}
}







//GET AND STORE FUNCTIONS
/***********************************
*return the floor where the next order to be executed is
*function will loop in main when the elevator reaches a floor, therefore it cannot be used if elevator is on NO_FLOOR (0) 
***********************************/
floor_t q_get_order(floor_t current_floor, elev_motor_direction_t current_direction){    
//NY FUNKSJON126     
if (current_floor == -1) printf("MAYDAY MAYDAY, NO FLOOR\n");

// is there even a floor?
//if (current_floor == -1) {
//    for (int i=0; i<10; i++)
//        if (orders[i] == 1)
//			return i;
//	return -1;
//}


// does anyone want to get off
if (orders[current_floor]) { 
	return current_floor; 
}

if (current_direction == DIRN_UP) {
	// are there any requests above current floor or at current floor going up
	for (int i=current_floor; i<3; i++) {
		if (orders[i] || orders[i+4]) {
			return i;
		}
	}
	// does anyone want to go to the forth floor
	if (orders[3]) {return 3;}

	// are there any requests for going down
	for (int i = 3; i>=current_floor; i--) {
		if (orders[i+6]) { return i; }
	}
}
if (current_direction == DIRN_DOWN) {
	// are there any requests below current floor or at current floor going down
	for (int i=current_floor; i>0; i--) {
		if (orders[i] || orders[i+6]) {
			return i;
		}
	}
	// does anyone want to go to the first floor
	if (orders[0]) {return 0;}

	// are there any requests for going up
	for (int i=0; i<=current_floor; i++) {
		if (orders[i+4]) { return i; }
	}
}
if (current_direction == DIRN_STOP) {
	for (int i=0;i<10;i++) {
		if (orders[i]==1) {
			switch(i) {
				case 0:
				case 4:
					return FIRST_FLOOR;
				case 1:
				case 5:
				case 7:
					return SECOND_FLOOR;
				case 2:
				case 6:
				case 8:
					return THIRD_FLOOR;
				case 3:
				case 9:
					return FOURTH_FLOOR;
			}
		}
	}
//	printf("HALELUJA\n");
}
//GAMMEL FUNKSJON
/*
	//printf("kjører q_get_order\n");
        if (q_check_floor(current_floor)) {					//check if there is an order on the elevator's current floor
      //  	printf("sjekker bestillinger i etasje %d", current_floor, "\n");
                if (orders[current_floor]) {					//returns the current floor if there is an order from inside the elevator to stop on that floor
            		return current_floor; 
       			}else if (current_direction == DIRN_UP && (current_floor != FOURTH_FLOOR)) {	//stop if there is an order from outside the elevator in the same direction as the current direction (up) 
            		if (orders[current_floor + 4]) {
                		return current_floor;
            		}
        		}else if ((current_direction == DIRN_DOWN) && (current_floor !=FIRST_FLOOR)) {	//stop if there is an order from outside the elevator in the same direction as the current direction (down) 
            		if (orders[current_floor + 6]) {
                	return current_floor;
                	}
				}else if (current_direction == DIRN_STOP) {					//stop if the elevator is in idle and on a floor, and there is a new order on that floor 
            		switch (current_floor) {
                    	case NO_FLOOR:
                        	return NO_FLOOR;
                    	case FIRST_FLOOR:
                    		if (orders[0] || orders[4]) {
                        		return FIRST_FLOOR;
                    		}
                		case SECOND_FLOOR:
                		case THIRD_FLOOR:
                    		if (orders[current_floor + 3] || orders[current_floor + 6]) {
                        		return current_floor;
                    		}
                		case FOURTH_FLOOR:
                    		if (orders[3] || orders[9]) {
                        		return FOURTH_FLOOR;
                    		}
                	}
         	}
    	}

    	if (current_direction == DIRN_STOP) {						//search for a new order if the elevator is in idle and the order queue is empty
      //      	printf("heisen er i ro og det er ingen bestillinger på %d", current_floor, "sjekker resten av køen\n");
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
	//	printf("sjekker alle opp-bestillingsknapper\n");
                for (int i=4; i<7; i++) {
			if (orders[i]==1) {
				return i-4;					//return the floor where the up button is pushed
			}
		}	
	}
	
	if (current_direction == DIRN_DOWN) {						//check down buttons
	//	printf("sjekker alle ned-bestillingsknapper\n");
                for (int i=7; i<10; i++) {
			if (orders[i]==1) {
				return i-6;					//return the floor where the down button is pushed
			}
		}
	}
  //      printf("finner ingen bestillinger\n");
	return NO_FLOOR; */
return NO_FLOOR;
}




/************************************
*stores a new order in the order queue at index button_pressed
************************************/
void q_store_order(int new_order){
//  printf("kjører q_store_order\n");
	orders[new_order] = 1;							//button_pressed is the index of an order button in the order_buttons array in main
}











