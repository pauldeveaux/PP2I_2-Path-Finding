#ifndef SIMULATION_H
#define SIMULATION_H

#include "astar.h"
#include "time.h"

// current position of the car at the time nbMinutes
int current_position(station_t stations[], int nbStations, car_t car[], int nb_simulations, int nb_minutes, int depart, int arrivee);

// free simulation parameters
void free_parameters(int* param_cars, int* param_departures, int* param_arrivals);

// print the number of cars at each station
bool print_charge_stations(station_t stations[], int nbStations);

// add a car to a station
void add_car_to_station(station_t* station, car_t* car);

// initialize the car queue of a station
void create_queue_car(station_t* station, car_t* car);

// add a car to the car queue of a station
void add_car_to_queue(station_t* station, car_t* car);

// destroy the car queue of a station
void destroy_queue(list_car_t* queue);

// display the car queue of a station
void display_queue(list_car_t* queue);

// return the number of cars at overloaded stations
int car_at_overloaded_station(station_t stations[], int nbStations);

// return the number of cars at not overloaded stations
int car_at_station(station_t stations[], int nbStations);

#endif
