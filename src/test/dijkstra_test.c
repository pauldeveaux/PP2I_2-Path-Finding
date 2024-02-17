#include "../dijkstra.h"
#include <time.h>
#include <assert.h>
#include "../utils/parser_csv.h"

#include <stdio.h>
#include "stdlib.h"

#define dmax 250

int main() {
    int depart = 6;
    int arrivee = 1550;

    csv_reader_t reader = create_reader_default(DATASET_PATH_STATIONS);
    station_t stations[DATASET_STATIONS_LINES];
    assert(parse_to_station(&reader, stations) == 0);

    int* predecessors = calloc(DATASET_STATIONS_LINES, sizeof(int));
    int* path = malloc(sizeof(int) * DATASET_STATIONS_LINES);
    int* newPath = malloc(sizeof(int) * DATASET_STATIONS_LINES);

    clock_t t=0;
    int distMin = dijkstra(stations[depart], stations[arrivee], stations, DATASET_STATIONS_LINES, predecessors);
    t = clock() - t;

    printf("\nMinimum distance between station %d and %d: %d km\n",depart, arrivee, distMin);

    int length = predecessorsToPath(predecessors,path,arrivee);

    // 'path' is the shortest path (in reverse order)
    displayPath(path, length);

    int newLength = decreaseNumberStations(stations, path, newPath, length, dmax);

    // 'newPath' is the path to display in order (with less stations)
    displayPath(newPath, newLength);

    printf("\nTime: %fs\n", ((double)t)/CLOCKS_PER_SEC);

    free(newPath);
    free(path);
    free(predecessors);
    free_parsed_station(stations);

    return 0;
}
