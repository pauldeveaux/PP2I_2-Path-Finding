import csv

def modifcsv(filename):
    lignes = []
    with open(filename, 'r') as csvfile:
        reader = csv.reader(csvfile, delimiter=';')
        en_tetes = next(csvfile)
        for row in reader:
            lignes.append(row)

    for i in range(len(lignes)):
        j = i+1
        while j < len(lignes):
            if lignes[i][0] == lignes[j][0]:
                l = lignes[i][0].split('--')
                if len(l) > 1:
                    lignes[j][0] = l[0] +"--"+ str(int(l[1])+1)
                else:
                    lignes[j][0] = l[0] + "--2"
                print(lignes[i][0] + " -> " + lignes[j][0])
            j += 1
    
    with open(filename, 'w') as csvfile:
        writer = csv.writer(csvfile, delimiter=';')
        writer.writerow(en_tetes)
        for row in lignes:
            writer.writerow(row)


modifcsv('./stations.csv')