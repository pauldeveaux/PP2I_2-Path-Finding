#include "../../astar.h"
#include "../../utils/parser_csv.h"
#include <time.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

# define NUMBER_OF_TESTS 1000
int main()
{

    // Creation file
    FILE *f;
    f = fopen("./src/test/performances/perf_astar", "w");
    if(f == NULL)
   {
      printf("Error!\n");
      exit(1);             
   }
   FILE *f2;
   f2 = fopen("./src/test/performances/path_not_found", "w");
    if(f2 == NULL)
    {
        printf("Error!\n");
        exit(1);
    }

    csv_reader_t reader = create_reader_default(DATASET_PATH_STATIONS);
    station_t stations[DATASET_STATIONS_LINES];
    car_t cars[DATASET_CARS_LINES];
    assert(parse_to_station(&reader, stations) == 0);
    reader = create_reader_default(DATASET_PATH_CARS);
    assert(parse_to_car(&reader, cars) == 0);
    srand(time(NULL));
    
    data_algo_t *params = malloc(sizeof(data_algo_t));
    params->min_bat = 0.2;
    params->max_bat = 0.5;
    params->current_bat = 0.8;
    params->tps_recharge = 20;
    params->payant = false;

    for(int i = 0; i < NUMBER_OF_TESTS; i++){
        car_t *car = &cars[rand() % DATASET_CARS_LINES];
        int depart = rand() % DATASET_STATIONS_LINES;
        int arrivee = rand() % DATASET_STATIONS_LINES;
        printf("%d : %d -> %d\n",i, depart, arrivee);
        while(depart == arrivee){
            depart = rand() % DATASET_STATIONS_LINES;
            arrivee = rand() % DATASET_STATIONS_LINES;
        }
        
        params->borne_depart = &stations[depart];
        params->borne_arrivee = &stations[arrivee];
        params->vehicule = car;

        // Timer on
        clock_t t=clock();

        station_t** path = path_generation(stations, DATASET_STATIONS_LINES, params);

        // Timer off  
        t = clock() - t;
        double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
        /*if(time_taken > 1 && path != NULL){
            fprintf(f2, "%s :   %s (%d) ____> %s (%d)   | %f\n", car->name, stations[depart].name, depart, stations[arrivee].name, arrivee, time_taken);
        }*/
        if(path != NULL){
            fprintf(f, "%d;%d;%d;%f\n", depart, arrivee, path_size(path, stations[arrivee]), time_taken);
        }
        else{
            fprintf(f2, "No path %s  : %s (%d) ____> %s (%d)   | %f\n", car->name, stations[depart].name, depart, stations[arrivee].name, arrivee, time_taken);
        }
        
       // print_path(path, path_size(path, stations[arrivee]));
        free(path);
    }

    fclose(f);
    fclose(f2);
    free_parsed_car(cars);
    free_parsed_station(stations);
    return 0;
}
