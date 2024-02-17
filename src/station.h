#ifndef STATION_H
#define STATION_H

#include <stdbool.h>
#include "car.h"

#define RADIAN 0.01745329251994329576923690768489

typedef struct list_car_t{
    car_t *car;
    struct list_car_t *next;
} list_car_t;

typedef struct station_t {
    int id; // id of the station
    char *name; // name of the station
    double latitude, longitude; // coordinate with longitude and latitude converted in radian for calculation
    int capacity; // capacity maximum of the station
    int power; // power of the station in kW
    bool is_free; // is the station free
    int num_cars_charging; // number of cars at station
    list_car_t *car_queue; // queue of cars waiting to charge
} station_t ;

// return the distance between two station in km
double distance(station_t *station1, station_t *station2);

#endif
