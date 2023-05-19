from folium import *
from random import random, randint
from flask import Flask, redirect, render_template, request
import logging

### Variables globales
out = "static/stations/" # dossier sortie
carte = "static/carte.html"
app = Flask(__name__)
app.logger.setLevel(logging.INFO)

### Fonctions de manipulation des données
def genere_aleatoires(n=100):
    sortie = open(out, "a")
    for i in range(n):
        y = str(-5 + 12*random())
        x = str(42 + 9*random())
        u = str(randint(0,6))
        sortie.write(x + "," + y + "," + u + "\n")
    sortie.close()

def get_couleur(n:float) -> str:
    if n == 0: return "darkgreen"
    if n <= 0.2: return "green"
    if n <= 0.4: return "orange"
    if n <= 0.6: return "red"
    if n < 0.8: return "darkred"
    else: return "black"

def get_donnees(n:int) -> list:
    fichier = out + str(n) + ".txt"
    f = open(fichier, "r", encoding="utf-8").read()
    if f == '':
        return []
    f = f.split(";")[:-1]
    f = [i.split(',') for i in f]
    for i in f: i[0], i[1], i[2] = float(i[1]), float(i[0]), float(i[2])
    return f

def get_donnees_all():
    xy_trouves = []
    donnees = []
    for n in range(nombre_ticks()):
        l = get_donnees(n)
        for i in l:
            xy = (i[0], i[1])
            if xy not in xy_trouves:
                donnees.append(i)
                xy_trouves.append(xy)
            else:
                for j in l:
                    if j[0] == i[0] and j[1] == i[1]: j[2] = max(j[2], i[2])
    return donnees

def genere_map(n:int):
    f = get_donnees(n)
    m = Map([48,2], zoom_start=6)
    for i in f:
        couleur = get_couleur(i[2])
        Marker(i[:2], icon=Icon(color=couleur)).add_to(m)
    return m

def genere_map_depuis(data:list):
    f = data
    m = Map([48,2], zoom_start=6)
    for i in f:
        couleur = get_couleur(i[2])
        Marker(i[:2], icon=Icon(color=couleur)).add_to(m)
    return m

def nombre_ticks() -> int:
    drapo = True
    n = 0
    while drapo:
        try:
            nom = out + str(n) + ".txt"
            open(nom, 'r', encoding='utf-8')
            n += 1
        except OSError: drapo = False
    return n

### Routes
@app.route('/')
def hello():
    return redirect('/index')

@app.route('/index')
def index():
    return render_template('index.html')

@app.route('/simuler')
def simuler():
    return render_template('simuler.html')

@app.route('/carte')
def carte0():
    n = request.args.get("tick", default=0, type=int)
    genere_map(n).save(carte)
    return render_template("map.html", nbt=nombre_ticks()-1, actuel=n, all=False)

@app.route('/carte/all')
def carteall():
    genere_map_depuis(get_donnees_all()).save(carte)
    return render_template("map.html", nbt=nombre_ticks()-1, all=True)
