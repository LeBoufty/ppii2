# Potagibus

Potagibus est une application permettant aux utilisateurs de véhicule électrique de trouver un itinéraire routier garantissant le passage par des bornes de rechargement sans tomber à court de batterie.

En rentrant le point de départ, le point d'arrivée et le modèle de la voiture dans la ligne de commande, l'application vous donnera une liste des bornes par lesquels passer afin d'arriver à bon port.

Potagibus est également capable de simuler du traffic routier via des automobilistes générés aléatoirement.

Ces automobilistes seront représentés en temps réel via une page html. Le passage du temps sera modélisé par un slider sur cette même page.

## Installation

Pour installer Potagibus, il vous suffit de cloner le dossier gitlab sur votre machine.

```bash
git clone https://gitlab.telecomnancy.univ-lorraine.fr/ppii2_2223/ppii2-grp_28.git
```

## Dépendances

Le projet nécessite les dépendances suivantes :
- Compilateur Clang
- Make
- Librairie C Standard
- Python 3, pip et flask (pour l'utilisation en web)

## Make

### Compilation
Pour compiler tous les fichiers sources, il vous suffit de lancer la commande suivante :

```bash
make all
```
Cela créera deux exécutables dans le dossier exe : pota_p1.exe et simulation.exe

### Nettoyage

Pour nettoyer les fichiers objets et les exécutables, il vous suffit de lancer la commande suivante :
```bash
make clean
```

## Utilisation en CLI (Ligne de commande)

### Simple Parcours

Pour utiliser l'application en ligne de commande, il vous suffit de lancer la commande suivante :
```bash
./exe/pota_p1.exe <lattitude_depart> <longitude_depart> <lattitude_arrivee> <longitude_arrivee> <id_voiture> <pourcentage_minimal_batterie> <temps_recharge_maximal>
```
Les paramètres sont les suivants (les chiffres après la virgule sont séparés par un point) :
- lattitude_depart : la lattitude du point de départ
- longitude_depart : la longitude du point de départ
- lattitude_arrivee : la lattitude du point d'arrivée
- longitude_arrivee : la longitude du point d'arrivée
- id_voiture : l'id de la voiture (renseignez-vous dans le fichier BD/ev-data.csv pour trouver l'id de votre voiture)
- pourcentage_minimal_batterie : le pourcentage minimal de batterie sous lequel vous ne voulez pas tomber (entre 0 et 100)
- temps_recharge_maximal : le temps maximal que vous êtes prêt à attendre à une borne de recharge (en heures)

Un exemple d'utilisation :
```bash
./exe/pota_p1.exe 47.608 7.502 45.785 4.783 0 70 0.333
```

Le résultat de la commande sera une liste de bornes de recharge par lesquelles passer pour arriver à bon port sur le terminal.
Un autre résultat est aussi donné dans web/static/parcous/parcours.txt (ce fichier est écrasé à chaque nouvelle utilisation de l'application).

### Simulation

Pour utiliser l'application en ligne de commande, il vous suffit de lancer la commande suivante :
```bash
./exe/simulation.exe <N>
```
Les paramètres sont les suivants :
- N : le nombre d'automobilistes à simuler

Un exemple d'utilisation :
```bash
./exe/simulation.exe 10
```

Le résultat est une liste de l'occupation des bornes de recharge en temps réel dans les fichiers du dossier web/static/stations. (ces fichiers sont écrasés à chaque nouvelle utilisation de l'application).

## Utilisation en Web

### Démarrage

Lancez script `runsite.sh` depuis la racine du projet :
```bash
./runsite.sh
```
En suite, ouvrez votre navigateur web et entrez-y l'adresse renseignée sur le terminal (par défaut : `http://127.0.0.1:5000`).

### Simple Parcours

Depuis l'index, cliquez sur `Calculer`, puis `Calculer un itinéraire`. Vous devrez renseigner :
- La ville de départ (nom exact)
- La ville d'arrivée (nom exact)
- Le pourcentage minimal de batterie accepté
- Le temps maximal (en minutes) que vous êtes prêt à attendre
- Le modèle de voiture

Une fois le calcul réalisé, vous serez redirigé sur la carte du résultat. Les points bleus affichent les stations auxquelles vous devrez vous arrêter et le temps passé à charger la voiture. Vous pourrez la consulter à nouveau en cliquant sur `Carte : Itinéraire` depuis l'index.

### Simulation

Depuis l'index, cliquez sur `Calculer`. Vous devrez renseigner :
- Le nombre d'usagers que vous voulez simuler

Une fois le calcul réalisé, vous serez redirigé sur la carte du résultat. Vous pouvez afficher un seul tick grâce au slider, ou tous en même temps. Dans le second cas, cliquer sur un marqueur affichera les ticks durant lesquels cette station est utilisée. Vous pourrez consulter la carte à nouveau en cliquant sur `Carte : Simulation` depuis l'index.

### Informations supplémentaires

La catégorie `Calculer` nécessite d'avoir les programmes `pota_p1.exe` et `simulation.exe` présents dans le dossier [exe/](/exe/). De plus, cela nécessite d'être en capacité d'exécuter ces programmes. Les cartes seront tout de même disponibles : elles afficheront les résultats du dernier calcul. 

## Désinstallation

Pour désinstaller Potagibus, il vous suffit de supprimer le dossier gitlab de votre machine.

```bash
rm -rf ppii2-grp_28
```

## Documentation
Il existe une documentation du code dans informations/Docs.txt

## Crédits

Utilisation de l'algorithme A* pour le calcul du plus court chemin.
