# Projet Pluridisciplinaire d'Informatique Intégrative 2 (2022-2023) 

Olivier Festor <<olivier.festor@telecomnancy.eu>>   
Gérald Oster <<gerald.oster@telecomnancy.eu>>  


**Membres du groupe** :
- ARIES Lucas <<Lucas.Aries@telecomnancy.eu>>  
- DEVAUX Paul <<Paul.Deveaux@telecomnancy.eu>>  
- HORNBERGER Théo <<Theo.Hornberger@telecomnancy.eu>>  
- TEMPESTINI Terry <<Terry.Tempestini@telecomnancy.eu>>  

# Utilisation

## Installation de gtk pour l'interface graphique 
### Linux
```shell
sudo apt-get install libgtk-3-dev
```
### Windows
[Installation GTK3 pour Windows](https://www.gtk.org/docs/installations/windows/)

### MacOS
```shell
brew install gtk+3
```

## Lancement du programme
```shell
make program
./program
``` 

## Test de l'application
```shell
# compile la partie parsing de csv en C et lance les tests
make parser_csv
./parser_csv

# assure que la distance entre longitude et latitude est correcte
make calculate_distance_test
./calculate_distance_test

# vérifie le fonctionnement de dijkstra 
make dijkstra_test
./dijkstra_test

# mesure le temps pris pour effectuer des calculs de distances
make time_distance_calcul_test
./time_distance_calcul_test

# calcul le degres d'une station
make degree_of_station_test
./degree_of_station_test
```
