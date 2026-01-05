#include <iostream>
#include <random>

void podciag(int ciag_a[], int N) {
    if (N < 5) {
        std::cout << "Ciag jest za krotki.\n";
    }
    const int M = 5;
    bool znaleziono = false;
    // int wynik[M]; 
    for(int i = 0; i < N - 4; i++) {
        int Temp[M];
        for(int j = 0; j < M; j++) {
            Temp[j] = ciag_a[i + j];
        }
        if(Temp[1] + Temp[3] > Temp[0] + Temp[2]+ Temp[4]) {
            znaleziono = true;
            for(int j = 0; j < M; j++) {
                std::cout << Temp[j] << " ";
            }
        }
        if (znaleziono) {
            std::cout << "\n";
            znaleziono = false;
        }
    }
}
int main () {
    const int N = 20;
    // int ciag_wejsciowy[N] = {1, 130, 1, 9, 11, 6, 1, 1, 1, 3, 1};
    int ciag_wejsciowy[N] = {};
    std::srand(std::time(NULL));
    for (int i = 0; i < N-1; i++) {
        ciag_wejsciowy[i] = rand() % 150 + 1; // Losowe liczby od 1 do 150
    }
    std::cout << "Ciag wejsciowy: ";
    for (int i = 0; i < N; i++) {
        std::cout << ciag_wejsciowy[i] << " ";
    }
    podciag(ciag_wejsciowy, N);
    return 0;
}