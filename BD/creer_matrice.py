# x = longitude, y = latitude
# Longitude Lambda (L), Latitude Phi (P)
from outils import *

# Test distance :
# print(distance(2,51,3,51), ", attendu : 69.97667335")
# 69.97669829281676 , attendu : 69.97667335
# Les distances sont en km

# Suppression de l'ancienne matrice
f = open('matrice.csv', 'w')
f.write('')
f.close()

# Ouverture de la nouvelle matrice
f = open('matrice.csv', 'a')

# Récupération des coordonnées
data = [i.replace('\n', '').split(',') for i in open('stations.csv', 'r').readlines()]
data = [(float(i[1]), float(i[2])) for i in data]

# Création des lignes
for k in range(len(data)):
    sortie = ''
    xk, yk = data[k]
    for i in range(len(data)):
        xi, yi = data[i]
        sortie += ',' + str(distance(xk, yk, xi, yi))
    sortie += '\n'
    f.write(sortie[1:])

f.close()