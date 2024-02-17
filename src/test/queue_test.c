#include "../station_node_priority_queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

# define SIZE_ARRAY 10

void free_parsed_station(station_t **stations){
    for (int i = 0; i < SIZE_ARRAY; i ++) {
        if(stations[i]!= NULL){
            free(stations[i]);
        }
    }
}

void shuffle(int *array, size_t n) {
    if (n > 1) {
        for (size_t i = 0; i < n - 1; i++) {
          srand(time(NULL));
          size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
          int t = array[j];
          array[j] = array[i];
          array[i] = t;
        }
    }
}


int main(){

    int tab[SIZE_ARRAY] = {1, 2, 3, 3, 4, 5, 6, 8, 9, 5};
    shuffle(tab, SIZE_ARRAY);
    for(int i = 0; i < SIZE_ARRAY; i++){
        printf("%d, ", tab[i]);
    }
    printf("\n");
    station_t *stations[SIZE_ARRAY];
    station_node_queue *root = create_queue();

    int heuristics[SIZE_ARRAY] = {83, 86, 77, 15};
    for(int i = 0; i < SIZE_ARRAY; i++){
        heuristics[i] = (rand() % 100);
        printf("%d, ", heuristics[i]);
    }
    
    print_queue(root);

    // Insert test
    for(int i = 0; i < SIZE_ARRAY; i++){
        station_t *station = malloc(sizeof(station_t));
        printf("Insert : %d\n", tab[i]);
        
        station->id = tab[i];
        station->name = "test";
        stations[i] = station;
        
        add_to_queue(&root, create_station_node(station, heuristics[i], heuristics[i]));
        print_queue_prefixe(root);
        printf("\n----------------\n");
    }

    printf("End Insert\n---------------\nStart Delete\n\n");

    // Delete test
    /*for(int i = 0; i < SIZE_ARRAY; i++){
        printf("Delete : %d\n", stations[i]->id);
         
        station_node *value = get_from_queue(root, stations[i]);

        if(value == NULL){
            printf("Value not found\n");
        }
        printf("Value : %d\n", value->station->id);

        root = remove_from_queue(root,value);
        free(value);
              
        print_queue_prefixe(root);
        printf("\n----------------\n");
    }*/
    
    free_queue(&root);
    free_parsed_station(stations);

    return 0;
}
