#
#
#

int q_check_floor(order_description current_order, int current_floor);

void q_delete_order();

void q_delete_all();

order_description q_get_order();

void q_store_order(order_description new_order); //lagrer en ny bestilling i koen 

struct order_description{ //informerer om etasjen heisen skal til, hvilken etasje den sist passerte, og hvilken retning den hadde da den passerte.
	int direction;
	int last_floor_passed;
	int next_floor_ordered;
	int direction_ordered;
	int order_origin_floor;
	int elev_button_order[3] = [next_floor_ordered, last_floor_passed, direction];
	int floor_button_ordered[4]=[direction_ordered, order_origin_floor, last_floor_passed, direction];
};

struct order_queue {
	order_description orders[20];
	void order_queue_init();
};
