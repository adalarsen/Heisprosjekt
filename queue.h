#
#
#

bool q_check_floor(order_description current_order, int current_floor);

void q_delete_order();

void q_delete_all();

order_description q_get_order();

void q_store_order(order_description new_order); //lagrer en ny bestilling i koen 

struct order_description{ //informerer om etasjen heisen skal til, hvilken etasje den sist passerte, og hvilken retning den hadde da den passerte.
	int direction;
	int last_floor_passed;
	int next_floor_ordered;
	int direction_ordered;
	int order[4] = [next_floor_ordered, direction_ordered, last_floor_passed, direction]
};


