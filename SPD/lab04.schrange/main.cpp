#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>
using namespace std;

class Dane{
  public:
    int id;
    int r;
    int p;
    int q;
};

void sortR (int n, Dane* dane, int* NieUszereg)
{
    for (int i=0; i<n-1; i++){
        for (int j=0; j<n-i-1; j++){
            if (dane[NieUszereg[j]].r < dane[NieUszereg[j+1]].r){
                swap(NieUszereg[j], NieUszereg[j+1]);
            }
        }
    }
}

int schrage (int n, Dane* dane)
{
    int Gotow[n], NieUszereg[n], Kolejnosc[n];
    int nieUszereg = n, gotow = 0, pom = 0;
    int time = 0, Cmax = 0;

    for (int i=0; i<n; i++){
        NieUszereg[i] = i;
    }

    sortR(n, dane, NieUszereg);

    while (pom != n){
        if (nieUszereg != 0){
            if (dane[NieUszereg[nieUszereg-1]].r <= time){
                Gotow[gotow] = NieUszereg[nieUszereg-1];
                ++gotow;
                --nieUszereg;

                for (int i=gotow-1; i>0; i--){
                    if (dane[Gotow[i]].q < dane[Gotow[i-1]].q){
                        swap(Gotow[i], Gotow[i-1]);
                    }
                }
                continue;
            }
        }

        if (gotow != 0){
            Kolejnosc[pom] = Gotow[gotow-1];
            time += dane[Kolejnosc[pom]].p;
            Cmax = max(Cmax, time + dane[Kolejnosc[pom]].q);
            gotow--;
            pom++;
            continue;
        }

        if (gotow == 0 && dane[NieUszereg[nieUszereg-1]].r > time){
            time = dane[NieUszereg[nieUszereg-1]].r;
        }
    }
    return Cmax;
}

int schragePodzial (int n, Dane* dane)
{
    int Gotow[n], NieUszereg[n], Kolejnosc[n];
    int nieUszereg = n, gotow = 0;
    int time = 0, Cmax = 0;
    int MAXX = 999999;
    int poz = MAXX;
    int ile_zrob = 0;

    for (int i=0; i<n; i++){
        NieUszereg[i] = i;
        Kolejnosc[i] = dane[i].p;
    }

    for (int i=0; i<n-1; i++){
        for (int j=0; j<n-i-1; j++){
            if (dane[NieUszereg[j]].r < dane[NieUszereg[j+1]].r){
                swap(NieUszereg[j], NieUszereg[j+1]);
            }
        }
    }

    while (nieUszereg != 0 || gotow != 0){
        if (nieUszereg != 0){
            if (dane[NieUszereg[nieUszereg-1]].r <= time){
                Gotow[gotow] = NieUszereg[nieUszereg-1];
                ++gotow;
                --nieUszereg;

                for (int i=gotow-1; i>0; i--){
                    if (dane[Gotow[i]].q < dane[Gotow[i-1]].q){
                        swap(Gotow[i], Gotow[i-1]);
                    }
                }

                if (poz != MAXX){
                    if (dane[Gotow[gotow-1]].q > dane[poz].q){
                        Gotow[gotow] = poz;
                        swap(Gotow[gotow], Gotow[gotow-1]);
                        gotow++;
                        poz = MAXX;
                    }
                }
                continue;
            }
        }

        if (gotow != 0){
            if (poz == MAXX){
                poz = Gotow[gotow-1];
                gotow--;
            }

            if (nieUszereg != 0){
                ile_zrob = min(Kolejnosc[poz], dane[NieUszereg[nieUszereg-1]].r - time);
            } else {
                ile_zrob = Kolejnosc[poz];
            }

            time += ile_zrob;
            Kolejnosc[poz] -= ile_zrob;

            if (Kolejnosc[poz] == 0){
                Cmax = max(Cmax, time + dane[poz].q);
                poz = MAXX;
            }
            continue;
        }

        if (gotow == 0 && nieUszereg != 0 && dane[NieUszereg[nieUszereg-1]].r > time){
            time = dane[NieUszereg[nieUszereg-1]].r;
        }
    }
    return Cmax;
}

// Comparator for sorting based on r value
struct CompareR {
    bool operator()(const Dane& a, const Dane& b) {
        return a.r > b.r; // Sorting in descending order of r
    }
};

// Comparator for sorting based on q value
struct CompareQ {
    bool operator()(const Dane& a, const Dane& b) {
        return a.q < b.q; // Sorting in ascending order of q
    }
};

int schrageSTL(int n, vector<Dane>& dane) {
    vector<Dane> Gotow; // Vector to store jobs sorted by q
    vector<Dane> NieUszereg = dane; // Copying dane to NieUszereg
    make_heap(NieUszereg.begin(), NieUszereg.end(), CompareR()); // Creating max-heap based on r

    int time = 0, Cmax = 0;

    while (!Gotow.empty() || !NieUszereg.empty()) {
        while (!NieUszereg.empty() && NieUszereg.front().r <= time) {
            Gotow.push_back(NieUszereg.front()); // Adding job to Gotow
            push_heap(Gotow.begin(), Gotow.end(), CompareQ()); // Re-arranging Gotow as max-heap based on q
            pop_heap(NieUszereg.begin(), NieUszereg.end(), CompareR()); // Extracting max element from NieUszereg
            NieUszereg.pop_back(); // Discarding max element
        }

        if (!Gotow.empty()) {
            pop_heap(Gotow.begin(), Gotow.end(), CompareQ()); // Extracting max element from Gotow
            Dane current_job = Gotow.back(); // Fetching max element based on q
            Gotow.pop_back(); // Discarding max element
            time += current_job.p;
            Cmax = max(Cmax, time + current_job.q);
        } else {
            time = NieUszereg.front().r;
        }
    }
    return Cmax;
}

int schragePodzialSTL(int n, vector<Dane>& dane) {
    vector<Dane> NieUszereg = dane; // Copying dane to NieUszereg
    vector<Dane> Gotow;
    make_heap(NieUszereg.begin(), NieUszereg.end(), CompareR());

    int time = 0, Cmax = 0;
    Dane current_job;
    current_job.r = 9999999; // Initialize with maximum value

    while (!Gotow.empty() || !NieUszereg.empty()) {
        while (!NieUszereg.empty() && NieUszereg.front().r <= time) {
            pop_heap(NieUszereg.begin(), NieUszereg.end(), CompareR());
            Dane job = NieUszereg.back();
            NieUszereg.pop_back();
            Gotow.push_back(job);
            push_heap(Gotow.begin(), Gotow.end(), CompareQ());
            if (job.q > current_job.q) {
                current_job.p = time - job.r;
                time = job.r;
                if (current_job.p > 0)
                    Gotow.push_back(current_job);
                push_heap(Gotow.begin(), Gotow.end(), CompareQ());
            }
        }

        if (!Gotow.empty()) {
            pop_heap(Gotow.begin(), Gotow.end(), CompareQ());
            Dane job = Gotow.back();
            Gotow.pop_back();
            current_job = job;
            time += job.p;
            Cmax = max(Cmax, time + job.q);
        } else {
            time = NieUszereg.front().r;
        }
    }

    return Cmax;
}

int main()
{
    int n;
    clock_t start = clock();
    clock_t end = clock();
    double elapsed;

    cin >> n;
    Dane dane[n];
    //vector <Dane> dane(n);
    for (int i=0; i<n; i++){
        dane[i].id = i+1;
        cin >> dane[i].r >> dane[i].p >> dane[i].q;
    }
    start = clock();
    cout << "Podzial: " << schragePodzial(n, dane) << endl;
    end = clock();
    elapsed = double(end - start)/CLOCKS_PER_SEC;
    cout << "Czas pracy: " << elapsed << endl;

    start = clock();
	cout << "Schrage: " << schrage(n, dane) << endl;
    end = clock();
    elapsed = double(end - start)/CLOCKS_PER_SEC;
    cout << "Czas pracy: " << elapsed << endl;

	/*
    start = clock();
    cout << "Podzial: " << schragePodzialSTL(n, dane) << endl;
    end = clock();
    elapsed = double(end - start)/CLOCKS_PER_SEC;
    cout << "Czas pracy: " << elapsed << endl;

    start = clock();
	cout << "Schrage: " << schrageSTL(n, dane) << endl;
    end = clock();
    elapsed = double(end - start)/CLOCKS_PER_SEC;
    cout << "Czas pracy: " << elapsed << endl;
    */
    return 0;
}
