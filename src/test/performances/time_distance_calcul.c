#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../../station.h"
#include "../../utils/parser_csv.h"

int main(){

    // Creation file
    FILE *f;
    f = fopen("./src/test/performances/perf_time_dist", "w");
    if(f == NULL)
   {
      printf("Error!\n");
      exit(1);             
   }

    // creation data
    csv_reader_t reader = create_reader_default(DATASET_PATH_STATIONS);
    station_t stations[DATASET_STATIONS_LINES];
    assert(parse_to_station(&reader, stations) == 0);
    
    
    for(int n = 1000; n <= 17000; n+= 1000){
        clock_t start = clock(); // start time
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                if(j != i)
                    distance(&stations[i], &stations[j]);
            }
        }
        printf("Progression en cours\n");
        clock_t end = clock(); // end time
        double time_spent = (double)(end - start) / CLOCKS_PER_SEC; // time spent
        
        // write the time in the file
        fprintf(f, "%d;%f\n", n, time_spent);
    }

    free_parsed_station(stations);
    fclose(f);
}
