# En copie-collant la liste des voitures donnée par le site dans le fichuer voitures_nf.csv,
# on peut utiliser ce script pour rendre ce fichier lisible par un programme et le sortir sur voitures.csv.
data = open('BD/voitures_nf.csv', 'r').read().replace('Average', '').replace('\t', ',')
f = open('BD/voitures.csv', 'w')
f.write(data)