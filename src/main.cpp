#include <iostream>

// Funkcja działająca tylko na danym przykladzie {1, 130, 1, 9, 11, 6, 1, 1, 1, 3, 1}, prawdopodobnie (nie było testow);
void podciag(int ciag_a[], int N) {
    if (N < 5) {
        std::cout << "Ciag jest za krotki.\n";
    }
    const int M = 5;
    // int wynik[M]; 
    for(int i = 0; i <= N - 4; i++) {
        int Temp[M];
        for(int j = 0; j < M; j++) {
            Temp[j] = ciag_a[i + j];
        }
        if(Temp[1] + Temp[3] > Temp[0] + Temp[2]+ Temp[4]) {
            for(int j = 0; j < M; j++) {
                std::cout << Temp[j] << " ";
            }
        }
        std::cout << "\n";
    }
}
int main () {
    const int N = 11;
    int ciag_wejsciowy[N] = {1, 130, 1, 9, 11, 6, 1, 1, 1, 3, 1};
    podciag(ciag_wejsciowy, N);
    return 0;
}