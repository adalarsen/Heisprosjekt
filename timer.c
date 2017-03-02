#include <time.h>

clock_t global_clock;

void start_timer(){
    global_clock = clock();
}

int is_timeout(){
    clock_t current_time = clock();
    clock_t difftime = current_time - global_time;
    if(difftime / CLOCKS_PER_SEC >= 3){
       return 1;
    }
   return 0;
} 
