import random

def podciag(ciag_a):
    Temp = []
    podciag = []
    N = len(ciag_a)    
    if N < 5:
        return []
    
    i,s1,s2,s3,s4,s5 = 0, 0, 0, 0, 0, 0

    while i <= N - 5:
        s1 = ciag_a[i]
        s2 = ciag_a[i + 1]
        s3 = ciag_a[i + 2]
        s4 = ciag_a[i + 3]
        s5 = ciag_a[i + 4]
    
        if s2 + s4 > s1 + s3 + s5:
            Temp = [s1, s2, s3, s4, s5]
            podciag.append(Temp)

        i += 1
    return podciag

# ciag_wejsciowy = [1, 130, 1, 9, 11, 6, 1, 1, 1, 3, 1]
ciag_wejsciowy = [random.randint(1, 150) for _ in range(20)]
print("Ciag wejsciowy:", ciag_wejsciowy)
print("Podciagi spełniające warunek:")
podciag(ciag_wejsciowy)

for i in podciag(ciag_wejsciowy):
    if i != []:
        print(i)
