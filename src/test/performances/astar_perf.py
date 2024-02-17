from statistics import mean 
from matplotlib import pyplot as plt
ftimes = open('./src/test/performances/perf_astar', 'r')

t = []
times = []
path_sizes = []
for line in ftimes:
    # depart;arrivee;path_size;time
    x = line.split(";")
    depart = int(x[0])
    arrivee = int(x[1])
    path_size = float(x[2])
    time = float(x[3])
    t.append((path_size,time,depart,arrivee))

t.sort(key=lambda x: x[1])
times = [x[1] for x in t]
path_sizes = [x[0] for x in t]

mean = mean(times)
max = max(times)
min = min(times)
med = times[int(len(times)/2)]

print(t[-1])

print("Moyenne : %f\nMax : %f\nMin : %f\nMed : %f" % (mean, max, min, med))

plt.plot(times)
plt.ylabel("Temps d'exécution (s)")
plt.show()
