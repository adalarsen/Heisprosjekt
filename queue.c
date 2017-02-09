#include "queue.c"
#include "io.h"
#include "hw.h"
#include "elev.h"
#include "fsm.h"
#include "queue.c"


int q_check_floor(order_description current_order, int current_floor){
	if (current_order.order[0]==current_floor) {
		return 1;
	else {
		return 0;
}

void q_delete_order(){
	for (int i=0; i<19; i++) {
		orders[i]=orders[i+1];
	}
	orders[19]=0;
}

void q_delete_all(){
	order_queue_init();
}

order_description q_get_order(){
	return orders[0];
}

void q_store_order(order_description new_order){ //lagrer en ny bestilling i koen

}
