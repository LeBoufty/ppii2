# Mettre cities.csv dans static
# Trouvable ici https://www.data.gouv.fr/fr/datasets/villes-de-france/
data = open('web/static/cities.csv', 'r').readlines()[1:]
data = [i.replace('\n', '').split(',') for i in data]
villes = [','.join([i[1], i[4], i[5]]) for i in data]
sortie = '\n'.join(villes)
f = open('web/static/villes.csv', 'w')
f.write(sortie)