from math import radians, sin, cos, acos

def distance(x1:float, y1:float, x2:float, y2:float) -> float:
    """Calcule la distance entre x1,y1 et x2,y2."""
    if x1 == x2 and y1 == y2:
        return 0 # Pour éviter les potentielles erreurs de calcul faisant que la distance soit non-nulle.
    x1 = radians(x1)
    y1 = radians(y1)
    x2 = radians(x2)
    y2 = radians(y2)
    
    A = sin(y1)*sin(y2) + cos(y1)*cos(y2)*cos(x2-x1)
    # Gestion des erreurs de flottant
    if A > 1: A = 1
    if A < -1: A = -1 
    
    return 6371 * acos(A)

class Station:
    def __init__(self, x:float, y:float, id:str, val_id:list, acces:str, nbre_pdc:int):
        self.x = x
        self.y = y
        self.id = id
        self.val_id = val_id
        self.val_num = [indice(i) for i in val_id]
        self.values = []
        self.stations = [id]
        self.acces = acces == "Accès libre"
        self.nb_pdc = nbre_pdc
    
    def distance(self, x:float, y:float):
        return distance(x, y, self.x, self.y)
    
    def __str__(self):
        return ','.join(self.values) + '\n'
    
    def xy(self):
        return (self.x, self.y)
    
    def scan(self, ligne:list):
        self.values = [ligne[i] for i in self.val_num]
        return self
    
    def indice(self, propriete:str):
        i = 0
        while i < len(self.val_id) and self.val_id[i] != propriete: i += 1
        if self.val_id[i] == propriete: return i
        else: return None
    
    def add_station(self, id:str, nb_pdc:int):
        if 'nbre_pdc' in self.val_id:
            self.nb_pdc += nb_pdc
            self.values[self.indice('nbre_pdc')] = str(self.nb_pdc)
        self.stations.append(id)
    
    def __sub__(self, other):
        x, y = other.xy()
        return self.distance(x, y)

def a_proximite(stat:Station, stations_trouvees:list, distmin = 5) -> bool:
    """Donne si une station x,y est à moins de distmin d'une autre."""
    i = 0
    if len(stations_trouvees) == 0: return False
    while i < len(stations_trouvees) and stat - stations_trouvees[i] > distmin: i += 1
    if i != len(stations_trouvees):
        if stat - stations_trouvees[i] != 0:
            stations_trouvees[i].add_station(stat.id, stat.nb_pdc)
        return True
    else: return False

colonnes = [
    # La description des propriétés se trouve ici : https://schema.data.gouv.fr/etalab/schema-irve-statique/2.2.0/documentation.html
    'nom_amenageur',
    'siren_amenageur',
    'contact_amenageur',
    'nom_operateur',
    'contact_operateur',
    'telephone_operateur',
    'nom_enseigne',
    'id_station_itinerance',
    'id_station_local',
    'nom_station',
    'implantation_station',
    'adresse_station',
    'code_insee_commune',
    'coordonneesXY',
    'nbre_pdc',
    'id_pdc_itinerance',
    'id_pdc_local',
    'puissance_nominale',
    'prise_type_ef',
    'prise_type_2',
    'prise_type_combo_ccs',
    'prise_type_chademo',
    'prise_type_autre',
    'gratuit',
    'paiement_acte',
    'paiement_cb',
    'paiement_autre',
    'tarification',
    'condition_acces',
    'reservation',
    'horaires',
    'accessibilite_pmr',
    'restriction_gabarit',
    'station_deux_roues',
    'raccordement',
    'num_pdl',
    'date_mise_en_service',
    'observations',
    'date_maj',
    'cable_t2_attache',
    'last_modified',
    'datagouv_dataset_id',
    'datagouv_resource_id',
    'datagouv_organization_or_owner',
    'consolidated_longitude',
    'consolidated_latitude',
    'consolidated_code_postal',
    'consolidated_commune',
    'consolidated_is_lon_lat_correct',
    'consolidated_is_code_insee_verified'
]

def indice(propriete:str) -> int:
    """Donne l'indice correspondant à la propriété"""
    i = 0
    while i < len(colonnes) and colonnes[i] != propriete: i += 1
    if i == len(colonnes): return None
    else: return i

def indices(proprietes:list) -> list:
    """Renvoie la liste des indices correspondant aux propriétés fournies."""
    return [indice(i) for i in proprietes]

def monstre(fichier:str) -> list:
    """Sert au parsing des données. Cette fonction est un monstre."""
    sortie = []
    # Le .csv étant trop imprévisible, je suis contraint de procéder caractère par caractère.
    ligne = []
    quote = False # Sert à définir si on se trouve dans un string. Dans ce cas les , ne séparent pas des informations.
    param = ''
    col = 0
    for i in fichier:
        if i == '"': quote = not quote
        if i == ',' and not quote:
            ligne.append(param)
            param = ''
        elif i == '\n' and not quote:
            ligne.append(param)
            sortie.append(ligne)
            ligne = []
        elif i == '\n' and quote:
            param += ' '
        else: param += i
    return sortie