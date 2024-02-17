#
# To plot the performances, you need to compile the C file and execute time_distance_calcul
# before running this script
#


from matplotlib import pyplot as plt

# performances
ftimes = open("./src/performances/perf_time_dist", "r")

times = []
sizes = []

for line in ftimes:
    # separate line by ;
    x = line.split(";")
    size = x[0]
    time = x[1]

    # convert to float
    size = float(size)
    time = float(time)

    sizes = sizes + [size]
    times = times + [time]

ftimes.close()

plt.plot(sizes, times)
plt.xlabel("Nombre de stations")
plt.ylabel("Temps d'exécution (s)")
plt.show()