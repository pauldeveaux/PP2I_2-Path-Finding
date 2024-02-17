#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "car.h"
#include "station.h"

// return the minimum distance between two station in km
int dijkstra(station_t depart, station_t arrivee, station_t *stations, int nbStations, int *predecessors);

// returns the index of the station with the minimum distance in the array of distances
int min_distance_index(int *distances, int *visited, int n);

// returns all the stations that are at a distance of distanceMax from the station
int *adjacentStations(station_t* station, int* visited, int distanceMax, station_t *stations, int nbStations);

// free the array of station returned by stationVoisines
void freeVoisines(int *voisines);

// update the distances of the neighbors of the station
void updateNeighbors(station_t* station, int* voisines, int* distances, station_t* stations, int* predecessors);

// returns the path from the depart to the arrivee
int predecessorsToPath(int* predecessors, int* path, int arrivee);

// display the path
void displayPath(int* path, int length);

// keep only the stations that are at a distance of at most 'autonomy' from the previous station
int decreaseNumberStations(station_t* stations ,int*path, int*newPath, int length, int autonomy);


#endif
