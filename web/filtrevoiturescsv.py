# Mettre voitures.csv dans static
# Trouvable dans le dossier BD
data = open('web/static/voitures.csv', 'r').readlines()[1:]
data = [i.replace('\n', '').split(',') for i in data]
voitures = [i[0] for i in data]
sortie = ';'.join(voitures)
f = open('web/static/voiture.txt', 'w')
f.write(sortie)