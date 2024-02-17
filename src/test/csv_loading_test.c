#include <time.h>
#include <stdio.h>
#include <assert.h>

#include "../utils/parser_csv.c"
#include "utils.c"

void parsing_cars_test() {
    printf("Test of 'cars.csv' parsing\n");

    clock_t start_time = clock();
    csv_reader_t reader = create_reader_default(DATASET_PATH_CARS);
    car_t cars[DATASET_CARS_LINES];

    assert (parse_to_car(&reader, cars) == 0);
    printf("Parsing of 'cars.csv' into car_t[] done successfully\n");

    clock_t end_time = clock();
    double time_taken_parse_cars = print_time_taken(start_time, end_time);
    printf("Time taken to parse cars: %f seconds\n", time_taken_parse_cars);

    for (int i = 0; i < DATASET_CARS_LINES; i++) {
        assert(cars[i].range != 0);
        assert(cars[i].consumption != 0);
        assert(cars[i].battery != 0.0);
    }
    printf("Asserts of car_t[] done successfully\n");

    assert(free_parsed_car(cars) == 0);
    printf("Freeing of car_t[] done successfully\n");

    printf("End of test of 'cars.csv' parsing\n");
}

void parsing_stations_test() {
    printf("Test of 'stations.csv' parsing\n");

    clock_t start_time = clock();
    csv_reader_t reader = create_reader_default(DATASET_PATH_STATIONS);
    station_t stations[DATASET_STATIONS_LINES];

    assert (parse_to_station(&reader, stations) == 0);
    printf("Parsing of 'stations.csv' into station_t[] done successfully\n");

    clock_t end_time = clock();
    double time_taken_parse_stations = print_time_taken(start_time, end_time);
    printf("Time taken to parse stations: %f seconds\n", time_taken_parse_stations);

    for (int i = 0; i < DATASET_STATIONS_LINES; i++) {
        /* printf("ligne: %d - %s, capacité = %d, puissance=%d kW, longitude/latitude [%f,%f]\n",
               stations[i].id + 2, stations[i].name, stations[i].capacity, stations[i].power, stations[i].longitude, stations[i].latitude);
        */
        assert(stations[i].capacity > 0);
        assert(stations[i].power > 0 && stations[i].power < 1000);
        assert(stations[i].longitude != 0.0 || stations[i].latitude != 0.0);
    }
    printf("Asserts of station_t[] done successfully\n");

    assert(free_parsed_station(stations) == 0);
    printf("Freeing of station_t[] done successfully\n");

    printf("End of test of 'stations.csv' parsing\n");
}

int main() {
    parsing_cars_test();
    printf("\n");
    parsing_stations_test();
}
