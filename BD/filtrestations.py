from outils import *
# Ce script python douteux sert à filtrer les stations et les données qu'on veut garder.
# Il a besoin de la version modifiée de la BD fournie. Elle se trouve sur mon (PYJ) PC (car dans le gitignore)
nomBD = 'BD/consolidation-etalab-schema-irve-statique-v-2.2.0-20230327.csv'

print('Parsing...')
data = monstre(open(nomBD, 'r').read())[1:]
print('Parsing fini.')

# Rafraichissement de la BD
sortie = open('BD/stations.csv', 'w')
sortie.write('')
sortie.close()

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
        # On ne garde que les propriétés demandées
        ligne = [ligne[i] for i in a_garder]
        # On ne garde que les stations qui respectent les conditions données
        if (acces == "Accès libre" and libre) and ((x,y) not in xy_trouves and not doublons) and ("Non" not in id and concerne) and not a_proximite(x,y,xy_trouves,distmin):
            xy_trouves.append((x,y))
            sortie.write(','.join(ligne) + '\n')
    # Et si tout va bien ça n'a toujours pas planté.
    print('Fini !')
    sortie.close()

filtre(['id_station_itinerance', 'consolidated_longitude', 'consolidated_latitude', 'nbre_pdc'])