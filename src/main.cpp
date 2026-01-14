#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>

int podciag(int ciag[], int N, int wynik[]) {
    if (N < 5) {
        std::cout << "Ciag jest za krotki.\n";
        return -1;
    }
    const int M = 5;
    int count{0};
    for(int i = 0; i < N - 4; i++) {
        for(int j = i; j < N - 4; j++) {
            for(int k = 0; k < M; k++) {
                if(ciag[i+1] + ciag[i+3] > ciag[i] + ciag[i+2] + ciag[i+4]) {
                    for(int m = 0; m < M; m++) {
                        wynik[count * M + m] = ciag[i + m];
                    }
                    count++;
                    j = N;
                    k = M;
                    break;
                }
            }
        }
    }
    return count;
}

int podciag_wersja_2(int ciag[], int N, int wynik[]) {
    if (N < 5) {
        std::cout << "Ciag jest za krotki.\n";
        return -1;
    }
    const int M = 5;
    int Temp[M], count{0};
    for(int i = 0; i < N - 4; i++) {
        for(int j = 0; j < M; j++) {
            Temp[j] = ciag[i + j];
        }
        if(Temp[1] + Temp[3] > Temp[0] + Temp[2]+ Temp[4]) {
            for(int k = 0; k < M; k++) {
                wynik[count * M + k] = Temp[k];
            }
            count++;
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
void wyswietl_wynik(int wynik[], int count) {
    if(count > 0) {
        int k{0};
        for (int i = 0; i < count; i++) {
            std::cout << "[ ";
            for (int j = 0; j < 5; j++) {
                std::cout << wynik[j+k] << " ";
            }
            std::cout << "]";
            if (i < count - 1) std::cout << ", ";
            k += 5;
        }
        std::cout << std::endl;
    }
    else {
        std::cout << "Brak danych do wyswietlania." << std::endl;
    }
}

void statystyka_czasu(double czas) {
    std::cout << "czas: " << std::fixed << std::setprecision(6) << czas << std::endl;
}
int main () {
    //Utworzenie zmiennych startowych
    const long N = 80000;
    int* ciag_wejsciowy = new int[N]();
    int* wynik = new int[N*5]();

    //Generowanie danych
    generuj_dane(ciag_wejsciowy, N);

    //wyświetlanie danych 
    // wyswietl_dane(ciag_wejsciowy, N);

    //Rozpoczęcie głownego algorytmu
    clock_t start1 = clock();
    int count1 = podciag(ciag_wejsciowy, N, wynik);
    clock_t stop1 = clock();
    double czas1 = static_cast<double>(stop1 - start1) / CLOCKS_PER_SEC;

    //Rozpoczęcie głownego algorytmu drugiego
    clock_t start2 = clock();
    int count2 = podciag_wersja_2(ciag_wejsciowy, N, wynik);
    clock_t stop2 = clock();
    double czas2 = static_cast<double>(stop2 - start2) / CLOCKS_PER_SEC;

    //Wyświetlenie wynikow
    std::cout << "Podciag wersja 1" << "\n";
    //wyswietl_wynik(wynik, count1);
    statystyka_czasu(czas1);

    std::cout << "Podciag wersja 2" << "\n";
    //wyswietl_wynik(wynik, count2);
    statystyka_czasu(czas2);

    // Zwolnij pamięć
    delete[] ciag_wejsciowy;
    delete[] wynik;

    return 0;
}