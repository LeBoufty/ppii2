voitures = []
params = []
# En copie-collant la liste des voitures donnée par le site dans le fichuer voitures_nf.csv,
# on peut utiliser ce script pour rendre ce fichier lisible par un programme et le sortir sur voitures.csv.
data = [i.replace('Average', '').replace('\n', '').upper().split('\t') for i in open('BD/voitures_nf.csv', 'r').readlines()]
f = open('BD/voitures.csv', 'a')
for i in data:
    if i[0] in voitures:
        index = voitures.index(i[0])
        params[index].append(i[1])
    else:
        voitures.append(i[0])
        params.append([i[1]])
f.write('name,range,battery_useable\n')
for i in range(len(voitures)):
    f.write(voitures[i] + ',' + ','.join(params[i]) + '\n')
f.close()