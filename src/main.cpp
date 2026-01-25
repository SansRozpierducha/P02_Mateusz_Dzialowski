#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <fstream>

std::vector<int> podciag(int ciag[], int N) {
    //program kończy się, jeśli tablica ciąg jest mniejszy niż 5
    if (N < 5) {
        return {};
    }
    //zmienne
    const int M = 5;
    std::vector<int> wynik;
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
                        wynik.push_back(ciag[i + m]);
                    }
                    //przerwanie pętli wewnętrznych po znalezieniu podciągu
                    j = N;
                    k = M;
                    break;
                }
            }
        }
    }
    //zwrócenie liczby znalezionych podciągów
    return wynik;
}

std::vector<int> podciag_wersja_2(int ciag[], int N) {
    //program kończy się, jeśli tablica ciąg jest mniejszy niż 5
    if (N < 5) {
        return {};
    }
    // zmienne
    const int M = 5;
    int Temp[M];
    std::vector<int> wynik;
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
                wynik.push_back(Temp[k]);
            }
        }
    }
    //zwrócenie liczby znalezionych podciągów
    return wynik; 
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

void wyswietl_wynik(std::vector<int> wynik) {
    //wyświetla podciągi które zostały znalezione
    if(!wynik.empty()) {
        int k{0};
        for (int i = 0; i < wynik.size() / 5; i++) {
            std::cout << "[ ";
            for (int j = 0; j < 5; j++) {
                std::cout << wynik[j+k] << " ";
            }
            std::cout << "]";
            if (i < wynik.size() / 5 - 1) std::cout << ", ";
            k += 5;
        }
        std::cout << std::endl;
    }
    else {
        std::cout << "Ciag jest za krotki lub nie ma zadnego spelnionego ciagu\n";
    }
}

void zapis_do_pliku(std::vector<int> wynik, const std::string& filename) {
    //funkcja do zapisywania wyników do pliku
    std::ofstream file(filename);
    if (file.is_open()) {
        if(!wynik.empty()) {
        int k{0};
        for (int i = 0; i < wynik.size() / 5; i++) {
            file << "[ ";
            for (int j = 0; j < 5; j++) {
                file << wynik[j+k] << " ";
            }
            file << "]";
            if (i < wynik.size() / 5 - 1) file << ", ";
            k += 5;
            }
        }
    }
}

struct Wynik {
    std::vector<int> p1;
    std::vector<int> p2;
};

Wynik test_zestawow(std::vector<int> tab, int N) {
    //funkcja do niewygodnych testów
    std::vector<int> wynik = podciag(tab.data(), N);
    std::vector<int> wynik2 = podciag_wersja_2(tab.data(), N);
    return {wynik, wynik2};
}
void test_niewygodnych_zestawow() {
    //funkcja związana z niewygodnymi testami
    int tab1[] = {1, 3, 2, 3};
    int tab2[] = {7, 7, 7, 7, 7};
    int tab3[] = {1, 130, 1, 9, 11, 6, 1, 1, 1, 3, 1};
    int tab4[] = {1, 100, 1, 100, 1, 2, 2, 2, 2};
    int tab5[] = {5, 200, 5, 200, 5, 10, 10, 10, 10};

    struct Test {
        int* tablica;
        int rozmiar;
    };

    Test testy[] = {
        {tab1, sizeof(tab1)/sizeof(tab1[0])},
        {tab2, sizeof(tab2)/sizeof(tab2[0])},
        {tab3, sizeof(tab3)/sizeof(tab3[0])},
        {tab4, sizeof(tab4)/sizeof(tab4[0])},
        {tab5, sizeof(tab5)/sizeof(tab5[0])}
    };

    // Wykonanie wszystkich testów
    for (int i = 0; i < 5; i++) {
        std::cout << "\n=== TEST " << (i+1) << " ===" << std::endl;
        std::cout << "Wejście: ";
        std::cout << std::endl;
        wyswietl_dane(testy[i].tablica, testy[i].rozmiar);
        
        Wynik wynik = test_zestawow(
            std::vector<int>(testy[i].tablica, testy[i].tablica + testy[i].rozmiar),
            testy[i].rozmiar
        );

        std::cout << std::endl;
        std::cout << "Algorytm 1: ";
        wyswietl_wynik(wynik.p1);
        std::cout << "Algorytm 2: ";
        wyswietl_wynik(wynik.p2);
    }
}

void test_wydajnosci() {
    //Utworzenie zmiennych startowych
    int N[] = {2500, 5000, 10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000};
    int liczba_testow = sizeof(N)/sizeof(N[0]);
    double* czas1 = new double[liczba_testow];
    double* czas2 = new double[liczba_testow];

    //Generowanie danych i wykonywanie testów
    for(int i = 0; i < liczba_testow; i++) {
        std::vector<int> ciag_wejsciowy(N[i]);
        std::vector<int> wynik(N[i]);

        //Generowanie danych
        generuj_dane(ciag_wejsciowy.data(), N[i]);
        //wyświetlanie danych 
        // wyswietl_dane(ciag_wejsciowy.data(), N[i]);

        //Rozpoczęcie głównego algorytmu
        clock_t start1 = clock();
        std::vector<int> wynik1 = podciag(ciag_wejsciowy.data(), N[i]);
        clock_t stop1 = clock();
        czas1[i] = (double)(stop1 - start1) / CLOCKS_PER_SEC;

        //Rozpoczęcie głównego algorytmu drugiego
        clock_t start2 = clock();
        std::vector<int> wynik2 = podciag_wersja_2(ciag_wejsciowy.data(), N[i]);
        clock_t stop2 = clock();
        czas2[i] = (double)(stop2 - start2) / CLOCKS_PER_SEC;

    }
    //Wyświetlanie w konsoli czasu algorytmów
    std::cout << "L.p.  n   t1[s]    t2[s]" << "\n";
    for(int i = 0; i < liczba_testow; i++) {
        std::cout << std::fixed << std::setprecision(6) << i+1 << "   " << N[i] << "    " << czas1[i] << "    " << czas2[i] << '\n';
    }

    std::string filename = "wyniki_wydajnosci.txt";
    std::ofstream file;
    file.open("wyniki_wydajnosci.txt");
    file << "L.p.  n   t1[s]    t2[s]" << "\n";
    for(int i = 0; i < liczba_testow; i++) {
        file << std::fixed << std::setprecision(6) << i+1 << "   " << N[i] << "    " << czas1[i] << "    " << czas2[i] << '\n';
    }
    file.close();
    
    delete[] czas1;
    delete[] czas2;
}

int main () {
    test_wydajnosci();

    return 0;
}