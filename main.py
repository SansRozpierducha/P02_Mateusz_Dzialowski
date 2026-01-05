import random

def podciag(ciag_a):
    if len(ciag_a) < 5:
        return []
    
    wyniki = []
    for i in range(len(ciag_a) - 4):
        okno = ciag_a[i:i+5]
        if okno[1] + okno[3] > okno[0] + okno[2] + okno[4]:
            wyniki.append(okno)
    return wyniki

# ciag_wejsciowy = [1, 130, 1, 9, 11, 6, 1, 1, 1, 3, 1]
ciag_wejsciowy = [random.randint(1, 150) for _ in range(20)]
print("Ciag wejsciowy:", ciag_wejsciowy)
print("Podciagi spełniające warunek:")
podciag(ciag_wejsciowy)

for i in podciag(ciag_wejsciowy):
    if i != []:
        print(i)
