from outils import *
# Ce script python douteux sert à filtrer les stations et les données qu'on veut garder.
# Il a besoin de la version modifiée de la BD fournie. Elle se trouve sur mon (PYJ) PC (car dans le gitignore)
data = [i.replace('\n', '').replace('"[', '').replace(']', '').replace(' ', '').replace('"', '').split(',') for i in open('BD/consolidation-etalab-schema-irve-statique-v-2.2.0-20230323.csv', 'r').readlines()]

# Rafraichissement de la BD
sortie = open('BD/stations.csv', 'w')
sortie.write('')
sortie.close()

sortie = open('BD/stations.csv', 'a')

xy_trouves = []

for ligne in data:
    if len(ligne) == 4:
        id, x, y, acces = ligne
        x = float(x)
        y = float(y)
        if (acces == "Accèslibre") and ((x,y) not in xy_trouves) and ("Non" not in id) and not a_proximite(x, y, xy_trouves, 1):
            xy_trouves.append((x,y))
            sortie.write((id + ',' + str(x) + ',' + str(y) + '\n').replace(' ', ''))

print('Fini !')
sortie.close()