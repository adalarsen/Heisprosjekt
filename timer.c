#include <time.h>
#include <stdio.h>

clock_t global_clock;

void timer_start(){
//    printf("kjører timer_start\n");
    global_clock = clock();
}

int timer_is_time_out(){
   // printf("kjører timer_is_time_out\n");
    clock_t current_time = clock();
    clock_t difftime = current_time - global_clock;
    if(difftime / CLOCKS_PER_SEC >= 3){
       return 1;
    }
   return 0;
} 
