from folium import *
from random import random, randint
from flask import Flask, redirect

out = "static/out"
carte = "static/carte.html"
app = Flask(__name__)

def genere_aleatoires(n=100):
    sortie = open(out, "a")
    for i in range(n):
        y = str(-5 + 12*random())
        x = str(42 + 9*random())
        u = str(randint(0,10))
        sortie.write(x + "," + y + "," + u + "\n")
    sortie.close()

def reset_out():
    open(out, "w").close()
    genere_aleatoires()

def genere_map():
    f = [i.replace('\n', '').split(',') for i in open(out, "r", encoding="utf-8").readlines()]
    for i in f: i[0], i[1], i[2] = float(i[0]), float(i[1]), int(i[2])
    m = Map([48,2], zoom_start=6)
    for i in f:
        if i[2] == 0: couleur = "green"
        elif i[2] < 4: couleur = "orange"
        else: couleur = "red"
        Marker(i[:2], icon=Icon(color=couleur)).add_to(m)
    return m

@app.route('/')
def index():
    genere_map().save(carte)
    return open(carte,'r').read()

@app.route('/random')
def aleatoire():
    reset_out()
    return redirect('/')