#include <iostream>
#include <cstdlib>
#include <ctime>

int podciag(int ciag_a[], int N, int wynik[]) {
    if (N < 5) {
        std::cout << "Ciag jest za krotki.\n";
        return -1;
    }
    const int M = 5;
    int Temp[M], count{0};
    for(int i = 0; i < N - 4; i++) {
        for(int j = 0; j < M; j++) {
            Temp[j] = ciag_a[i + j];
        }
        if(Temp[1] + Temp[3] > Temp[0] + Temp[2]+ Temp[4]) {
            count++;
            for(int k = 0; k < M; k++) {
                wynik[i * M + k] = Temp[k];
            }
        }
    }
    return count; 
}

void generuj_dane(int ciag[], int N) {
    std::srand(std::time(NULL));
    for (int i = 0; i < N; i++) {
        ciag[i] = rand() % 150 + 1; // rand()  % (max - min + 1) + min
    }
}
void wyswietl_dane(int tablica[], int N) {
    std::cout << "Ciag wejsciowy: ";
    for (int i = 0; i < N; i++) {
        std::cout << tablica[i] << " ";
    }
    std::cout << std::endl;
}
//Do zmainy coś nie działa
void wyswietl_wynik(int wynik[], int N, int count) {
    std::cout << count << "\n";
    if(count != -1) {
    int k{0};
    for (int i = 0; i < count; i++) {
        std::cout << "[ ";
        for (int j = 0; j < 5; j++)
        std::cout << wynik[j+k] << " ";
        std::cout << "], ";
        k += 5;
        }
    }
    else {
        std::cout << "Brak danych do wyświetlania";
    }
    std::cout << std::endl;
}
int main () {
    //Utworzenie zmiennych startowych
    const int N = 100;
    int ciag_wejsciowy[N] = {};
    int wynik[N*5] = {};
    //Generowanie danych
    generuj_dane(ciag_wejsciowy, N);
    //wyświetlanie danych 
    wyswietl_dane(ciag_wejsciowy, N);
    //Rozpoczęcie głownego algorytmu

    int count = podciag(ciag_wejsciowy, N, wynik);

    //Wyświetlenie wynikw
    wyswietl_wynik(ciag_wejsciowy, N, count);

    return 0;
}