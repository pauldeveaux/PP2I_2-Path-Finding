#include "../utils/parser_csv.h"
#include "../simulation.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int depart = 119;
    int arrivee = 120;
    int nb_simulations = 15; // nb cars
    printf("Paramètres : ./simulation_test <nb simulations> <depart> <arrivee>\n\n");

    if(argc == 2){
        nb_simulations = atoi(argv[1]);
        printf("Nombre de simulations : %d\n", nb_simulations);
        printf("Chemins par défaut : depart = %d, arrivee = %d\n", depart, arrivee);
    }else if(argc != 4){
        printf("Nombre de simulations : %d\n", nb_simulations);
        printf("Chemins par défaut : depart = %d, arrivee = %d\n", depart, arrivee);
    }else{
        nb_simulations = atoi(argv[1]);
        depart = atoi(argv[2]);
        arrivee = atoi(argv[3]);
        printf("Nombre de simulations : %d\n", nb_simulations);
        printf("Chemin : depart = %d, arrivee = %d\n", depart, arrivee);
    }

    clock_t t=0;

    int nb_minutes = 1000; // each 10 minutes until nb_minutes

    printf("\nTaux de chargement des stations pour %d voitures (par pas de 10 minutes)",nb_simulations);

    for(int i=1; i<nb_minutes/10;i++){
        csv_reader_t reader = create_reader_default(DATASET_PATH_STATIONS);
        station_t stations[DATASET_STATIONS_LINES];
        car_t cars[DATASET_CARS_LINES];
        assert(parse_to_station(&reader, stations) == 0);
        reader = create_reader_default(DATASET_PATH_CARS);
        assert(parse_to_car(&reader, cars) == 0);
        
        printf("\n\nA %d minutes :", i*10);
        
        int state = current_position(stations, DATASET_STATIONS_LINES, cars, nb_simulations, i*10, depart, arrivee);
        
        int nb_at_station = car_at_station(stations, DATASET_STATIONS_LINES);
        int nb_at_overloaded_station = car_at_overloaded_station(stations, DATASET_STATIONS_LINES);
        int nb_on_road = nb_simulations - nb_at_station - nb_at_overloaded_station;

        printf("\nVoitures sur la route %d/%d", nb_on_road, nb_simulations);
        print_charge_stations(stations, DATASET_STATIONS_LINES);
        
        if(state == 1){
            printf("\n\nToutes les voitures sont arrivées à destination\n");
            free_parsed_car(cars);
            free_parsed_station(stations);
            break;
        }

        free_parsed_car(cars);
        free_parsed_station(stations);
    }

    t = clock() - t;
    printf("\nTemps d'execution : %f secondes\n", ((float)t)/CLOCKS_PER_SEC);

    return 0;
}
