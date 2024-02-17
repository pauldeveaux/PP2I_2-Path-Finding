#include "../astar.h"
#include "../utils/parser_csv.h"
#include <time.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>


int main()
{
    int depart = 6;
    int arrivee = 1550;
    /*// Normal path
    int depart = 20;
    int arrivee = 83;*/

    /*// Path 1 length
    int depart = 13187;
    int arrivee = 9597;*/

    /*// Path 2 length
    int depart = 1550;
    int arrivee = 94;*/
    
    
    /*// Path not found with depart in France (a lot of stations)
    int depart = 14772;
    int arrivee = 12611;*/

    /*// Path not found with only one station
    int depart = 11885;
    int arrivee = 6596;*/

    /* // Path not found that take a lot of time
    int depart = 15770;
    int arrivee = 139;*/
    
    /*// Strange path in Corsica ?
    int depart = 746;
    int arrivee = 12070;*/
    
    // Path that took a lot of time before
   // int depart = 17393;
    //int arrivee = 12752;
   
    //int depart = 9602;
    //int arrivee = 12217;

    csv_reader_t reader = create_reader_default(DATASET_PATH_STATIONS);
    station_t stations[DATASET_STATIONS_LINES];
    car_t cars[DATASET_CARS_LINES];
    assert(parse_to_station(&reader, stations) == 0);
    reader = create_reader_default(DATASET_PATH_CARS);
    assert(parse_to_car(&reader, cars) == 0);

    car_t *car = &cars[0];

    // Timer on
    clock_t t=0;
    data_algo_t *params = malloc(sizeof(data_algo_t));
    params->borne_depart = &stations[depart];
    params->borne_arrivee = &stations[arrivee];
    params->vehicule = car;
    params->min_bat = 0.2;
    params->max_bat = 0.5;
    params->current_bat = 0.8;
    params->tps_recharge = 20;
    params->payant = false;

    station_t** path = path_generation(stations, DATASET_STATIONS_LINES, params);
    if(path != NULL){
        print_path(path, path_size(path, stations[arrivee]));
    }
    else{
        printf("Path not found\n");
    }
    free(path);

    // Timer off  
    t = clock() - t;
    printf("Temps d'execution : %f secondes\n", ((float)t)/CLOCKS_PER_SEC);

    free(params);
    free_parsed_car(cars);
    free_parsed_station(stations);
    return 0;
}
