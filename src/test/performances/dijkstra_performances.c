#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../../station.h"
#include "../../dijkstra.h"
#include "../../utils/parser_csv.h"

int main(){
    FILE *f;
    f = fopen("./src/test/performances/perf_dijkstra", "w");
    if(f == NULL)
   {
      printf("Error!");   
      exit(1);             
   }

    // creation data
    csv_reader_t reader = create_reader_default(DATASET_PATH_STATIONS);
    station_t stations[DATASET_STATIONS_LINES];
    assert(parse_to_station(&reader, stations) == 0);

    for(int i = 0; i < 10; i++){
        int depart = rand() % DATASET_STATIONS_LINES;
        int arrivee = rand() % DATASET_STATIONS_LINES;

        int* predecessors = calloc(DATASET_STATIONS_LINES, sizeof(int));
        int* path = malloc(sizeof(int) * DATASET_STATIONS_LINES);
       
        clock_t start = clock(); // start time
        int distMin = dijkstra(stations[depart], stations[arrivee], stations, DATASET_STATIONS_LINES, predecessors);
        clock_t end = clock(); // end time

        free(path);
        free(predecessors);

        fprintf(f, "%d --> %d : %d km, %fs\n",depart,arrivee,distMin,((double)(end - start))/CLOCKS_PER_SEC);
    }    
    free_parsed_station(stations);
    fclose(f);
}
