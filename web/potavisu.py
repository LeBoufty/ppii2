from folium import *
from random import random, randint
from flask import Flask, redirect, render_template, request
import logging
import os

### Variables globales
out = "static/stations/" # dossier sortie
outparcours = "static/parcours/parcours.txt"
carte = "static/carte.html"
villescsv = "static/villes.csv"
exe = "../exe/"
voitures = open("static/voiture.txt", 'r').read().split(';')
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
    n = 1-n
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
                donnees.append(i + [str(n)])
                xy_trouves.append(xy)
            else:
                for j in donnees:
                    if j[0] == i[0] and j[1] == i[1]:
                        j[2] = max(j[2], i[2])
                        j[3] += ', ' + str(n)
    return donnees

def get_parcours():
    f = open(outparcours, 'r', encoding='utf-8').read()
    if 'Erreur : chemin non trouvé' in f: return []
    f = f.split(';')[:-1]
    f = [i.split(',') for i in f]
    f = [[(float(i[1]), float(i[0])), float(i[2])] for i in f]
    return f

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
        Marker(i[:2], icon=Icon(color=couleur), popup="Tick N°"+str(i[3])).add_to(m)
    return m

def genere_map_itineraire(data:list):
    traj = [i[0] for i in data]
    m = Map([48,2], zoom_start=6)
    PolyLine(traj, tooltip="Itinéraire").add_to(m)
    for i in data:
        if i[1] != 0:
            Marker(i[0], icon=Icon(color="blue"), popup="Arrêt pour "+str(int(i[1]*60))+" minutes").add_to(m)
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

def get_coord_ville(ville:str):
    f = open(villescsv, 'r').read().split('\n')
    f = [i.split(',') for i in f]
    ville = ville.lower().replace('-', ' ')
    x,y = 0,0
    for i in f:
        if i[0] == ville:
            x,y = float(i[1]), float(i[2])
    return x,y

def simulation(n:int):
    os.system('rm -f '+out+"*.txt")
    cmd = 'cd .. && ./exe/simulation.exe '+str(n)
    return os.system(cmd)

def calculer_itineraire(depart, arrivee, idvoit, pcmin, attmax):
    xd, yd = get_coord_ville(depart)
    xa, ya = get_coord_ville(arrivee)
    xd, yd, xa, ya = str(xd), str(yd), str(xa), str(ya)
    idvoit = str(idvoit)
    pcmin = str(pcmin)
    attmax = str(attmax)
    cmd = 'cd .. && ./exe/pota_p1.exe '+' '.join([xd, yd, xa, ya, idvoit, pcmin, attmax])
    app.logger.info(cmd)
    return os.system(cmd)

def get_voiture(id:int):
    return voitures[id]

def get_id_voiture(voit:str):
    return voitures.index(voit)

### Routes
@app.route('/')
def hello():
    return redirect('/index')

@app.route('/index')
def index():
    return render_template('index.html')

@app.route('/simuler', methods=['GET', 'POST'])
def simuler():
    if request.method == 'GET': return render_template('simuler.html')
    else:
        n = request.form['nbu']
        simulation(n)
        return redirect('/carte')

@app.route('/carte')
def carte0():
    n = request.args.get("tick", default=0, type=int)
    genere_map(n).save(carte)
    return render_template("map.html", nbt=nombre_ticks()-1, actuel=n, all=False, simu=True)

@app.route('/carte/all')
def carteall():
    genere_map_depuis(get_donnees_all()).save(carte)
    return render_template("map.html", nbt=nombre_ticks()-1, all=True, simu=True)

@app.route('/itineraire')
def itineraire():
    genere_map_itineraire(get_parcours()).save(carte)
    return render_template("map.html", simu=False)

@app.route('/calcitineraire', methods=['GET', 'POST'])
def calcitineraire():
    if request.method == 'GET': return render_template("itineraire.html", vroum=voitures)
    else:
        vildepar = request.form['depart']
        vilarriv = request.form['arrivee']
        idvoit = get_id_voiture(request.form['voiture'])
        pcmin = int(request.form['pcmin'])
        attmax = int(request.form['attmax']) / 60
        calculer_itineraire(vildepar, vilarriv, idvoit, pcmin, attmax)
        return redirect('/itineraire')
