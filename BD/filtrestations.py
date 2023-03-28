from outils import *
# Ce script python douteux sert à filtrer les stations et les données qu'on veut garder.
# Il a besoin de la version modifiée de la BD fournie. Elle se trouve sur mon (PYJ) PC (car dans le gitignore)
data = [i.replace('\n', '').replace('"[', '').replace(']"', '').split(',') for i in open('consolidation-etalab-schema-irve-statique-v-2.2.0-20230323.csv', 'r').readlines()]
sortie = open('stations.csv', 'a')

xy_trouves = []

def a_proximite(x, y):
    pass

for ligne in data:
    if len(ligne) == 4:
        id, x, y, acces = ligne
        if (acces == "Accès libre") and ((x,y) not in xy_trouves) and ("Non" not in id):
            xy_trouves.append((x,y))
            sortie.write((id + ',' + x + ',' + y + '\n').replace(' ', ''))

sortie.close()