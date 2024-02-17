#include "station_node_priority_queue.h"
#include "car.h"

typedef struct data_algo_t{
    station_t* borne_depart;
    station_t* borne_arrivee;
    car_t* vehicule;
    double min_bat;
    double max_bat;
    double current_bat;
    double tps_recharge;
    bool payant;
}data_algo_t;

station_t** path_generation(station_t stations[], int nbstations, data_algo_t *params);

station_t** reconstruct_path(station_node *node);

double calculate_heuristic(station_node *node, station_t *goal);

station_node **adjacentStations(station_t stations[], station_node *node, int nbStations, station_t *last_station, double distMax, double distMin, bool only_free);

int path_size(station_t **path, station_t last_station);

void print_path(station_t **path, int nbstations);

char* path_to_string(station_t **path, int nbstations);
