#ifndef PARSER_CSV_H
#define PARSER_CSV_H

#include "../car.h"
#include "../station.h"

#define DATASET_PATH_CARS "dataset/cars.csv"
#define DATASET_CARS_LINES 299
#define DATASET_PATH_STATIONS "dataset/stations.csv"
#define DATASET_STATIONS_LINES 17451

// struct to easily read a csv file
typedef struct csv_reader_t {
    const char *filename; // filename of the csv
    const char *separator; // separator of the csv
    int max_line_size; // max length of a line
} csv_reader_t ;

// create a csv reader with the default parameters
csv_reader_t create_reader_default(const char* filename);

// create a csv with custom parameters
csv_reader_t create_reader(const char* filename, const char *separator, int max_line_size);

// parse the csv in the array of car_t return 0 if done successfully
int parse_to_car(csv_reader_t* reader, car_t array[]);

// free the array of car_t from the parse_to_car return 0 if done successfully
int free_parsed_car(car_t array[]);

// parse the csv in the array of station_t return 0 if done successfully
int parse_to_station(csv_reader_t* reader, station_t array[]);

// free the array of car_t from the parse_to_station return 0 if done successfully
int free_parsed_station(station_t array[]);

#endif
