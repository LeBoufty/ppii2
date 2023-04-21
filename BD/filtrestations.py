from outils import *
# Ce script python douteux sert à filtrer les stations et les données qu'on veut garder.
# Il a besoin de la version modifiée de la BD fournie. Elle se trouve sur mon (PYJ) PC (car dans le gitignore)
nomBD = 'BD/consolidation-etalab-schema-irve-statique-v-2.2.0-20230327.csv'

print('Parsing...')
data = monstre(open(nomBD, 'r').read())[1:]
print('Parsing fini.')

def filtre(proprietes:list, distmin:float = 1, concerne:bool = True, libre:bool = True, doublons:bool = False, nomsortie:str = 'stations'):
    # Màj du nom de la sortie : ne pas oublier de lancer le programme depuis la racine du projet !!
    nomsortie = 'BD/'+nomsortie+'.csv'
    print('Début du filtre, sortie sur', nomsortie)

    # Définition des colonnes à garder
    a_garder = indices(proprietes)

    # Remise à zéro de la BD
    sortie = open(nomsortie, 'w')
    sortie.write(','.join(proprietes) + '\n')
    sortie.close()
    sortie = open(nomsortie, 'a')

    # Compteur : à titre indicatif.
    n = len(data)
    i = 0

    # Liste des coordonnées trouvées
    stations_trouvees = []
    xy_trouves = []

    for ligne in data:
        # Mise à jour du compteur
        i += 1
        if i%5000 == 0:
            print('Ligne', i, '/', n)
        # On récupère des données importantes au traitement qui ne sont peut-être pas gardées dans la BD finale
        x, y = float(ligne[indice('consolidated_longitude')]), float(ligne[indice('consolidated_latitude')])
        id = ligne[indice('id_station_itinerance')]
        acces = ligne[indice('condition_acces')]
        nbre_pdc = int(ligne[indice('nbre_pdc')])
        stat = Station(x, y, id, proprietes, acces, nbre_pdc)
        # On ne garde que les propriétés demandées
        stat.scan(ligne)
        # On ne garde que les stations qui respectent les conditions données
        drapo = True
        # On fait tous les test 1 par 1 pour éviter les calculs inutiles
        if concerne and drapo:
            if "Non" in id: drapo = False
        if libre and drapo:
            if acces != "Accès libre": drapo = False
        if not doublons and drapo:
            if (x,y) in xy_trouves: drapo = False
        if distmin > 0 and drapo:
            if a_proximite(stat,stations_trouvees,distmin): drapo = False
        if drapo:
            stations_trouvees.append(stat)
            xy_trouves.append(stat.xy()) # On garde xy_trouves pour éviter les doublons
    # Et si tout va bien ça n'a toujours pas planté.
    print('Ecriture des données...')
    # On écrit toutes les stations qu'on a trouvées
    for s in stations_trouvees:
        sortie.write(str(s))
    print('Fini !')
    sortie.close()

filtre(['id_station_itinerance', 'consolidated_longitude', 'consolidated_latitude', 'nbre_pdc'])