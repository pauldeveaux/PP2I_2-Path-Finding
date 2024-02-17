#
# To plot the performances, you need to compile the C file and execute degree_of_station.c
# before running this script
# You can change the distance max for an edge in the C file
#

from numpy import mean
from matplotlib import pyplot as plt

# performances
f = open("./src/performances/degree_stations_data", "r")

degrees = []


for line in f:
    degrees.append(int(line))

degrees.sort()

print("moyenne : " + str(mean(degrees)))
f.close()

plt.plot(range(0,len(degrees)), degrees)
plt.xlabel("Stations")
plt.ylabel("Nombre de stations adjacentes")
plt.show()