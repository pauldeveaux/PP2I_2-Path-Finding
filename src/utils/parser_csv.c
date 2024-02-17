#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parser_csv.h"

csv_reader_t create_reader_default(const char* filename) {
    csv_reader_t reader = {
        .filename = filename,
        .separator = ";",
        .max_line_size = 512};
    return reader;
}

csv_reader_t create_reader(const char* filename, const char *separator, int max_line_size) {
    csv_reader_t reader = {
        .filename = filename, 
        .separator = separator,
        .max_line_size = max_line_size};
    return reader;
}

int parse_to_car(csv_reader_t* reader, car_t array[]) {
    FILE* file = fopen(reader->filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Impossible de trouver le fichier '%s'\n", reader->filename);
        return EXIT_FAILURE;
    }

    char line[reader->max_line_size];
    char* field, *copy;

    int line_index = 0, column_index = 0;
    int first_line = 1;
    while (fgets(line, reader->max_line_size, file) != NULL) {

        // to not add the headers of the csv
        if (first_line) {
            first_line = 0;
            continue;
        }

        field = strtok(line, reader->separator);
        while (field != NULL) {

            // --- parsing
            switch (column_index) {
                case 0:
                    copy = malloc(strlen(field) + 1);
                    strcpy(copy, field);
                    array[line_index].name = copy;
                    break;
                case 1:
                    array[line_index].range = atoi(field);
                    break;
                case 2:
                    array[line_index].battery = atof(field);
                    break;
                case 3:
                    array[line_index].consumption = atoi(field);
                    break;

                default:
                    fprintf(stderr, "Parsing du fichier '%s' colonne en trop\n", reader->filename);
                    return EXIT_FAILURE;
            }
            // --- end

            field = strtok(NULL, reader->separator);
            column_index++;
        }

        column_index = 0;
        line_index++;
    }

    fclose(file);
    return EXIT_SUCCESS;
}

int free_parsed_car(car_t array[]) {
    for (int i = 0; i < DATASET_CARS_LINES; i ++) {
        free(array[i].name);
    }
    return EXIT_SUCCESS;
}

// parse the csv in the array of station_t return 0 if done successfully
int parse_to_station(csv_reader_t* reader, station_t array[]) {
    FILE* file = fopen(reader->filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Impossible de trouver le fichier '%s'\n", reader->filename);
        return EXIT_FAILURE;
    }
    char line[reader->max_line_size];
    char* field, *copy, *tmp;

    int line_index = 0, column_index = 0;
    int first_line = 1;
    while (fgets(line, reader->max_line_size, file) != NULL) {
        // to not add the headers of the csv
        if (first_line) {
            first_line = 0;
            continue;
        }
        array[line_index].id = line_index;
        field = strtok(line, reader->separator);

        array[line_index].num_cars_charging = 0;
        array[line_index].car_queue = NULL;

        while (field != NULL) {
            // --- parsing
            switch (column_index) {
                case 0:
                    // this mean we have a value like "name; localisation" who has only been parsed as "name
                    if   (field[0] == '"' && field[strlen(field)-1] != '"') {

                        tmp = malloc(strlen(field) + 1);
                        strcpy(tmp, field);
                        // concat while we don't have the end of the field
                        do  {
                            field = strtok(NULL, reader->separator);
                            tmp = realloc(tmp, strlen(tmp) + strlen(field) + 1);
                            strcat(tmp, field);
                        } while (field[strlen(field)-1] != '"');

                        memmove(tmp, tmp + 1, strlen(tmp)); // remove the first "
                        tmp[strlen(tmp)-1] = '\0'; // remove the last "
                        array[line_index].name = tmp;

                    } else {
                        copy = malloc(strlen(field) + 1);
                        strcpy(copy, field);
                        array[line_index].name = copy;
                    }
                    break;

                case 1:
                    array[line_index].capacity = atoi(field);
                    break;
                case 2:
                    array[line_index].power = atoi(field);
                    if (array[line_index].power == 0) { array[line_index].power = 10; } // if the power is 0 (not register in the csv , we set it to 10)
                    while (array[line_index].power >= 1000) { array[line_index].power /= 10; } // convert the power in kW (if it's in W)
                    break;

                case 3:
                    array[line_index].is_free = (strcmp(field, "true") || strcmp(field, "TRUE") || strcmp(field, "1") ) ? true : false;
                    break;
                case 4:
                    array[line_index].longitude = atof(field) * RADIAN;
                    break;
                case 5:
                    array[line_index].latitude = atof(field) * RADIAN;
                    break;

                default:
                    fprintf(stderr, "Parsing du fichier '%s' colonne en trop à la ligne: %i\n", reader->filename, line_index + 2);
                    return EXIT_FAILURE;
            }
            // --- end
            field = strtok(NULL, reader->separator);
            column_index++;
        }

        column_index = 0;
        line_index++;
    }

    fclose(file);
    return EXIT_SUCCESS;
}

// free the array of car_t from the parse_to_station return 0 if done successfully
int free_parsed_station(station_t array[]) {
    for (int i = 0; i < DATASET_STATIONS_LINES; i ++) {
        free(array[i].name);
    }
    return EXIT_SUCCESS;
}
