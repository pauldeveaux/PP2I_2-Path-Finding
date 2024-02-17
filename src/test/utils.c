#include <time.h>

// the time taken for the program to run useful to measure performance
double print_time_taken(clock_t start_time, clock_t end_time) {
    return (double) (end_time - start_time) / CLOCKS_PER_SEC;
}
