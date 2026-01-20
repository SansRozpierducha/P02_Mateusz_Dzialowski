#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <fstream>

struct Wynik {
    int p1;
    int p2;
};

int podciag(int ciag[], int N, int wynik[]) {
    //program kończy się, jeśli tablica ciąg jest mniejszy niż 5
    if (N < 5) {
        return -1;
    }
    //zmienne
    const int M = 5;
    int count{0};
    //główna pętla algorytmu - przeszukiwanie wszystkich możliwych podciągów
    for(int i = 0; i < N - 4; i++) {
        //wewnętrzna pętla algorytmu - szukanie spełnienia warunku
        for(int j = i; j < N - 4; j++) {
            //pętla iteracyjna po elementach podciągu
            for(int k = 0; k < M; k++) {
                //sprawdzenie warunku: suma elementów na pozycjach nieparzystych > suma pozostałych
                if(ciag[i+1] + ciag[i+3] > ciag[i] + ciag[i+2] + ciag[i+4]) {
                    //przepisanie znalezionego podciągu do tablicy wyników
                    for(int m = 0; m < M; m++) {
                        wynik[count * M + m] = ciag[i + m];
                    }
                    //inkrementacja licznika znalezionych podciągów
                    count++;
                    //przerwanie pętli wewnętrznych po znalezieniu podciągu
                    j = N;
                    k = M;
                    break;
                }
            }
        }
    }
    //zwrócenie liczby znalezionych podciągów
    return count;
}

int podciag_wersja_2(int ciag[], int N, int wynik[]) {
    //program kończy się, jeśli tablica ciąg jest mniejszy niż 5
    if (N < 5) {
        return -1;
    }
    // zmienne
    const int M = 5;
    int Temp[M], count{0};
    //główna pętla algorytmu - przeszukiwanie wszystkich możliwych podciągów
    for(int i = 0; i < N - 4; i++) {
        //pętla wewnętrzna - przypisuje wartości do tablicy Temp
        for(int j = 0; j < M; j++) {
            Temp[j] = ciag[i + j];
        }
        //sprawdzenie warunku: suma elementów na pozycjach nieparzystych > suma pozostałych
        if(Temp[1] + Temp[3] > Temp[0] + Temp[2]+ Temp[4]) {
            //pętla wewnętrzna - przypisująca z tablicy Temp wyniki do tablicy Wyniki
            for(int k = 0; k < M; k++) {
                wynik[count * M + k] = Temp[k];
            }
            //inkrementacja licznika znalezionych podciągów
            count++;
        }
    }
    //zwrócenie liczby znalezionych podciągów
    return count; 
}

void generuj_dane(int ciag[], int N) {
    //generuje dane poprzez bibliotekę random
    std::srand(std::time(NULL));
    for (int i = 0; i < N; i++) {
        ciag[i] = rand() % 150 + 1; // rand()  % (max - min + 1) + min
    }
}

void wyswietl_dane(int tablica[], int N) {
    //wyświetla dane początkowe (wygenerowane)
    std::cout << "Ciag wejsciowy: ";
    for (int i = 0; i < N; i++) {
        std::cout << tablica[i] << " ";
    }
    std::cout << std::endl;
}

void wyswietl_wynik(int wynik[], int count) {
    //wyświetla podciągi które zostały znalezione
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
        std::cout << "Ciag jest za krotki lub nie ma zadnego spelnionego ciagu\n";
    }
}

Wynik test_zestawow(int *tab, int N, int *dane) {
    //funkcja do niewygodnych testów
    int wynik = podciag(tab, N, dane);
    int wynik2 = podciag_wersja_2(tab, N, dane);
    return {wynik, wynik2};
}
void test_niewygodnych_zestawow() {
    //funkcja związana z niewygodnymi testami
    int tab1[] = {1,3,2,3};
    int tab2[] = {7,7,7,7,7};
    int tab3[] = {1, 130, 1, 9, 11, 6, 1, 1, 1, 3, 1};

    //Pierwszy test
    int N1 = sizeof(tab1)/sizeof(tab1[0]);
    int wynik1[N1*5];
    Wynik count1 = test_zestawow(tab1, N1, wynik1);
    wyswietl_wynik(wynik1, count1.p1);
    wyswietl_wynik(wynik1, count1.p2);

    //Drugi test
    int N2 = sizeof(tab2)/sizeof(tab2[0]);
    int wynik2[N2*5];
    Wynik count2 = test_zestawow(tab2, N2, wynik2);
    wyswietl_wynik(wynik2, count2.p1);
    wyswietl_wynik(wynik2, count2.p2);

    //Trzeci test
    int N3 = sizeof(tab3)/sizeof(tab3[0]);
    int wynik3[N3*5];
    Wynik count3 = test_zestawow(tab3, N3, wynik3);
    wyswietl_wynik(wynik3, count3.p1);
    wyswietl_wynik(wynik3, count3.p2);
}

void test_wydajności() {
    //Utworzenie zmiennych startowych
    int N[] = {2500, 5000, 10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000};
    int liczba_testow = sizeof(N)/sizeof(N[0]);
    double* czas1 = new double[liczba_testow];
    double* czas2 = new double[liczba_testow];

    //Generowanie danych i wykonywanie testów
    for(int i = 0; i < liczba_testow; i++) {
        int* ciag_wejsciowy = new int[N[i]]();
        int* wynik = new int[N[i]*5]();

        //Generowanie danych
        generuj_dane(ciag_wejsciowy, N[i]);
        //wyświetlanie danych 
        // wyswietl_dane(ciag_wejsciowy, N);

        //Rozpoczęcie głównego algorytmu
        clock_t start1 = clock();
        int count1 = podciag(ciag_wejsciowy, N[i], wynik);
        clock_t stop1 = clock();
        czas1[i] = (double)(stop1 - start1) / CLOCKS_PER_SEC;

        //Rozpoczęcie głównego algorytmu drugiego
        clock_t start2 = clock();
        int count2 = podciag_wersja_2(ciag_wejsciowy, N[i], wynik);
        clock_t stop2 = clock();
        czas2[i] = (double)(stop2 - start2) / CLOCKS_PER_SEC;

        delete[] ciag_wejsciowy;
        delete[] wynik;
    }
    //Wyświetlanie w konsoli czasu algorytmów
    std::cout << "L.p.  n   t1[s]    t2[s]" << "\n";
    for(int i = 0; i < liczba_testow; i++) {
        std::cout << std::fixed << std::setprecision(6) << i+1 << "   " << N[i] << "    " << czas1[i] << "    " << czas2[i] << '\n';
    }
    
    delete[] czas1;
    delete[] czas2;
}

int main () {
    test_wydajności();
    test_niewygodnych_zestawow();
    return 0;
}