#ifndef CAR_H
#define CAR_H

typedef struct car_t {
    char* name; // name of the vehicule
    int range; // range of the vehicule in km
    double battery; // battery in kWh
    int consumption; // consumption in Wh/km
} car_t;


#endif
