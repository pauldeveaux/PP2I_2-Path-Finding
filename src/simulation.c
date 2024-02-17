#include "simulation.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <assert.h>
#include <math.h>

#define VITESSE 100 // km/h

int current_position(station_t stations[], int nbStations, car_t car[], int nb_simulations, int nb_minutes, int depart, int arrivee){

    // we can change the parameters of the simulation
    int *param_cars = (int*)malloc(sizeof(int)*nb_simulations);
    int *param_departures = (int*)malloc(sizeof(int)*nb_simulations);
    int *param_arrivals = (int*)malloc(sizeof(int)*nb_simulations);

    int *state_car = (int*)malloc(sizeof(int)*nb_simulations);

    for(int i=0; i<nb_simulations;i++){
        param_cars[i] = i;
        param_departures[i] = depart;
        param_arrivals[i] = arrivee;
        state_car[i] = -1;
    }

    // discretization of the time
    nb_minutes = nb_minutes/10;

    // we simulate the position of all the cars
    for(int i=0; i<nb_simulations;i++){

        int voiture = param_cars[i];
        int depart = param_departures[i];
        int arrivee = param_arrivals[i];

        data_algo_t* params = (data_algo_t*)malloc(sizeof(data_algo_t));
        params->borne_depart = &stations[depart];
        params->borne_arrivee = &stations[arrivee];
        params->vehicule = &car[voiture];
        params->min_bat = 0.2;
        params->max_bat = 0.8;
        params->current_bat = 0.5;
        params->tps_recharge = 0.5;
        params->payant = false;

        station_t** path = path_generation(stations,nbStations,params);
        int path_lenght = path_size(path, stations[arrivee]);
        
        int km = 10*VITESSE/60;
        int add_time = 0;

        for(int j = 0; j < path_lenght - 1; j++){
            // number of stops between two stations
            int current_distance = (int) lround(distance(path[j], path[j+1]));
            add_time += (int)current_distance/km;

            double energy_used = (car->consumption * current_distance)/1000;
            double time_to_charge = (energy_used / stations[j+1].power) * 60;

            time_to_charge = round(time_to_charge) / 10; 

            if(j==(path_lenght-2) && nb_minutes>add_time){
                state_car[i] = 1;
                break;
            }

            // case car at a station
            if(nb_minutes>add_time && nb_minutes<add_time+time_to_charge){
                if(path[j+1]->id != arrivee){
                    add_car_to_station(&stations[path[j+1]->id], &car[voiture]);
                    state_car[i] = 2;
                } else state_car[i] = 1;
                break;
            }
            // case car on the road
            else if(nb_minutes<=add_time){
                state_car[i] = 0;
                break;
            }
            add_time += time_to_charge;
        }  
        free(path);
        free(params);
    }    
    int all_arrived = 1;
    for(int i=0; i<nb_simulations;i++){
        if(state_car[i] != 1){
            all_arrived = 0;
            break;
        }
    }

    free_parameters(param_cars, param_departures, param_arrivals);
    free(state_car);

    return all_arrived;
}

void add_car_to_station(station_t* station, car_t* car){
    if(station->num_cars_charging >= station->capacity){
        if(station->car_queue == NULL){
            create_queue_car(station, car);
        } else{
            add_car_to_queue(station, car);
        }        
    }
    station->num_cars_charging += 1;
    return;
}

void free_parameters(int* param_cars, int* param_departures, int* param_arrivals){
    free(param_cars);
    free(param_departures);
    free(param_arrivals);
    return;
}

bool print_charge_stations(station_t stations[], int nbStations){
    bool display = false;
    for(int i=0; i<nbStations;i++){
        if(stations[i].num_cars_charging>stations[i].capacity){
            display = true;
            printf("\nStation n°%d surchargée : File d'attente de %d voitures", i,stations[i].num_cars_charging-stations[i].capacity);
            if(stations[i].car_queue != NULL){
                destroy_queue(stations[i].car_queue);
            }
        }else if(stations[i].num_cars_charging==stations[i].capacity){
            printf("\nStation n°%d pleine : [%d/%d]", i,stations[i].num_cars_charging,stations[i].capacity);
        }
    }
    return display;
}

int car_at_station(station_t stations[], int nbStations){
    int nb_cars = 0;
    for(int i=0; i<nbStations;i++){
        if(stations[i].num_cars_charging>0 && stations[i].num_cars_charging<=stations[i].capacity){
            nb_cars += stations[i].num_cars_charging;
        }
    }
    return nb_cars;
}

int car_at_overloaded_station(station_t stations[], int nbStations){
    int nb_cars = 0;
    for(int i=0; i<nbStations;i++){
        if(stations[i].num_cars_charging>stations[i].capacity){
            nb_cars += stations[i].num_cars_charging;
        }
    }
    return nb_cars;
}

void create_queue_car(station_t* station, car_t* car){
    station->car_queue = (list_car_t*)malloc(sizeof(list_car_t));
    station->car_queue->car = car;
    station->car_queue->next = NULL;
    return;
}

void add_car_to_queue(station_t* station, car_t* car){
    list_car_t* queue = (list_car_t*)malloc(sizeof(list_car_t));
    queue->car = car;
    queue->next = NULL;
    list_car_t* aux = station->car_queue;

    while(aux->next != NULL){
        aux = aux->next;
    }
    aux->next = queue;
}

void destroy_queue(list_car_t* queue){
    list_car_t* aux = queue;
    while(aux != NULL){
        list_car_t* next = aux->next;
        free(aux);
        aux = next;
    }
}

void display_queue(list_car_t* queue){
    list_car_t* aux = queue;
    printf(" pending cars : ");
    while(aux != NULL){
        printf("%s, ", aux->car->name);
        aux = aux->next;
    }
}
