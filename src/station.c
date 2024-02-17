#include <math.h>

#include "station.h"

#define RAYON_TERRE 6371


double distance(station_t *station1, station_t *station2) {

    double a = pow(sin((station2->latitude - station1->latitude) / 2), 2)
            + cos(station1->latitude)
            * cos(station2->latitude)
            * pow(sin((station2->longitude - station1->longitude) / 2), 2);

    return RAYON_TERRE * 2 * atan2(sqrt(a), sqrt(1-a));
}
