#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../../station.h"
#include "../../utils/parser_csv.h"

#define dmax 345
#define dmin 0

int main(){

    // Creation file
    FILE *f;
    f = fopen("./src/test/performances/degree_stations_data", "w");
    if(f == NULL)
   {
      printf("Error!");   
      exit(1);             
   }

    // creation data
    csv_reader_t reader = create_reader_default(DATASET_PATH_STATIONS);
    station_t stations[DATASET_STATIONS_LINES];
    assert(parse_to_station(&reader, stations) == 0);
    
    int degrees[DATASET_STATIONS_LINES];

    for(int i = 0; i < DATASET_STATIONS_LINES; i++){
        degrees[i] = 0;
        for(int j = 0; j < DATASET_STATIONS_LINES; j++){
            if(j != i){
                double d = distance(&stations[i], &stations[j]);
                if(dmin < d && d < dmax){
                    degrees[i]++;
                }
            }
                
        } 
        fprintf(f, "%d\n", degrees[i]);
    }

    free_parsed_station(stations);
    fclose(f);
}
