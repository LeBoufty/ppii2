from folium import *
from random import random, randint
from flask import Flask, redirect, render_template

### Variables globales
out = "static/out"
carte = "static/carte.html"
app = Flask(__name__)

### Fonctions de manipulation des données
def genere_aleatoires(n=100):
    sortie = open(out, "a")
    for i in range(n):
        y = str(-5 + 12*random())
        x = str(42 + 9*random())
        u = str(randint(0,6))
        sortie.write(x + "," + y + "," + u + "\n")
    sortie.close()

def reset_out():
    open(out, "w").close()
    genere_aleatoires()

def get_couleur(n:int) -> str:
    if n == 0: return "darkgreen"
    if n <= 2: return "green"
    if n <= 4: return "orange"
    if n <= 6: return "red"
    if n < 10: return "darkred"
    else: return "black"

def get_donnees() -> list:
    f = [i.replace('\n', '').split(',') for i in open(out, "r", encoding="utf-8").readlines()]
    for i in f: i[0], i[1], i[2] = float(i[0]), float(i[1]), int(i[2])
    return f

def genere_map():
    f = get_donnees()
    m = Map([48,2], zoom_start=6)
    for i in f:
        couleur = get_couleur(i[2])
        Marker(i[:2], icon=Icon(color=couleur)).add_to(m)
    return m

### Routes
@app.route('/')
def index():
    genere_map().save(carte)
    return render_template("map.html")

@app.route('/random')
def aleatoire():
    reset_out()
    return redirect('/')