

void main() {
	int lights[15] = {0};
        int order_buttons[10] = {0};
        int floor_indicators[4] = {0};

        // Initialize hardware
        if (!elev_init()) {
                printf("Unable to initialize elevator hardware!\n");
                return 1;
         }

        // initialiserer heis (koen)
        fsm_elev_on();
	

	return 0;
}
