# Ce script python douteux sert à filtrer les stations et les données qu'on veut garder.
data = [i.replace('\n', '').replace('"[', '').replace(']"', '').split(',') for i in open('consolidation-etalab-schema-irve-statique-v-2.2.0-20230323.csv', 'r').readlines()]
sortie = open('stations.csv', 'a')

xy_trouves = []

for ligne in data:
    if len(ligne) == 4:
        id, x, y, acces = ligne
        if acces == "Accès libre" and (x,y) not in xy_trouves:
            xy_trouves.append((x,y))
            sortie.write((id + ',' + x + ',' + y + '\n').replace(' ', ''))

sortie.close()