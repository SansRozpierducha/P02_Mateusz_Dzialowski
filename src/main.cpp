#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>

struct Wynik {
    int p1;
    int p2;
};

int podciag(int ciag[], int N, int wynik[]) {
    if (N < 5) {
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
        std::cout << "Ciag jest za krotki.\n";
    }
}

void statystyka_czasu(double czas) {
    std::cout << "czas: " << std::fixed << std::setprecision(6) << czas << std::endl;
}

Wynik test_niewygodnych_zestawow(int *tab, int N, int *dane) {
    int wynik = podciag(tab, N, dane);
    int wynik2 = podciag_wersja_2(tab, N, dane);
    return {wynik, wynik2};
}

void test_wydajności() {
    //Utworzenie zmiennych startowych
    int N[10] = {2500, 5000, 10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000};

    //Generowanie danych
    for(int i = 0; i < 10; i++) {
        int* ciag_wejsciowy = new int[N[i]]();
        int* wynik = new int[N[i]*5]();

        generuj_dane(ciag_wejsciowy, N[i]);
        //wyświetlanie danych 
        // wyswietl_dane(ciag_wejsciowy, N);

        //Rozpoczęcie głownego algorytmu
        clock_t start1 = clock();
        int count1 = podciag(ciag_wejsciowy, N[i], wynik);
        clock_t stop1 = clock();
        double czas1 = static_cast<double>(stop1 - start1) / CLOCKS_PER_SEC;

        //Rozpoczęcie głownego algorytmu drugiego
        clock_t start2 = clock();
        int count2 = podciag_wersja_2(ciag_wejsciowy, N[i], wynik);
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
    }
}

int main () {
    int tab2[] = {3,2,1};
    int tab3[] = {7,7,7,7,7};
    int tab4[] = {1, 130, 1, 9, 11, 6, 1, 1, 1, 3, 1};

    int N2 = sizeof(tab2)/sizeof(tab2[0]);
    int N3 = sizeof(tab3)/sizeof(tab3[0]);
    int N4 = sizeof(tab4)/sizeof(tab4[0]);

    int dane[20] = {};

    int count = podciag(tab2, N2, dane);
    wyswietl_wynik(tab2 ,count);
    count = podciag_wersja_2(tab2, N2, dane);
    wyswietl_wynik(tab2 ,count);
    count = podciag(tab3, N3, dane);
    wyswietl_wynik(tab3 ,count);
    count = podciag_wersja_2(tab3, N3, dane);
    wyswietl_wynik(tab3 ,count);
    count = podciag(tab4, N4, dane);
    wyswietl_wynik(tab4 ,count);
    count = podciag_wersja_2(tab4, N4, dane);
    wyswietl_wynik(tab4 ,count);
    return 0;
}