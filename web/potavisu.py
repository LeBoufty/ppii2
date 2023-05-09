from folium import *
from random import random, randint

out = "web/out"
carte = "web/carte.html"

def genere_aleatoires(n=100):
    sortie = open(out, "a")
    for i in range(n):
        y = str(0 + 4*random())
        x = str(44 + 6*random())
        u = str(randint(0,10))
        sortie.write(x + "," + y + "," + u + "\n")
    sortie.close()

open(out, "w").close()
genere_aleatoires()

f = [i.replace('\n', '').split(',') for i in open(out, "r", encoding="utf-8").readlines()]
for i in f: i[0], i[1], i[2] = float(i[0]), float(i[1]), int(i[2])

def genere_map():
    m = Map([48,2], zoom_start=2)
    for i in f:
        if i[2] == 0: couleur = "green"
        elif i[2] < 4: couleur = "orange"
        else: couleur = "red"
        Marker(i[:2], icon=Icon(color=couleur)).add_to(m)
    return m

genere_map().save(carte)