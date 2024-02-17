#include "station.h"


typedef struct station_node_t {
    station_t *station;
    double heuristic;
    double cost;
    double battery_after_charge;
    struct station_node_t *parent;
} station_node;


typedef struct station_node_queue_t {
    station_node *value;
    struct station_node_queue_t *left;
    struct station_node_queue_t *right;
    struct station_node_queue_t *parent;
} station_node_queue;


station_node* create_station_node(station_t *station, double cost, double heuristic);


station_node_queue* create_queue();

station_node_queue *remove_from_queue(station_node_queue *root, station_node *value);

void add_to_queue(station_node_queue **root, station_node *value);

station_node * get_from_queue(station_node_queue *root, station_t *station);


station_node* unqueue(station_node_queue **root);


bool is_in_queue(station_node_queue *root, station_t *station);


bool is_in_queue_with_lower_cost(station_node_queue *root, station_node *station);


bool queue_is_empty(station_node_queue *root);


void free_queue(station_node_queue **root);

void print_queue(station_node_queue *root);

void print_queue_prefixe(station_node_queue *root);

int size_queue(station_node_queue *root);
