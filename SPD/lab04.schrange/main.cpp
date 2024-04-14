#include <iostream>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <fstream>
#include <iomanip>

using namespace std;

const int MAX_SIZE = 50;

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

int schrageNotHeap (int n, Dane* dane)
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

int schragePodzialNotHeap (int n, Dane* dane)
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

struct CompareR {
    bool operator()(const Dane& a, const Dane& b) {
        return a.r > b.r;
    }
};

struct CompareQ {
    bool operator()(const Dane& a, const Dane& b) {
        return a.q < b.q;
    }
};

int schrageSTLHeap(int n, Dane dane[]) {
    vector<Dane> Gotow;
    vector<Dane> NieUszereg;
    for (int i=0; i<n; i++){
        NieUszereg.push_back(dane[i]);
    }
    make_heap(NieUszereg.begin(), NieUszereg.end(), CompareR());

    int time = 0, Cmax = 0;

    while (!Gotow.empty() || !NieUszereg.empty()) {
        while (!NieUszereg.empty() && NieUszereg.front().r <= time) {
            Gotow.push_back(NieUszereg.front());
            push_heap(Gotow.begin(), Gotow.end(), CompareQ());
            pop_heap(NieUszereg.begin(), NieUszereg.end(), CompareR());
            NieUszereg.pop_back();
        }

        if (!Gotow.empty()) {
            pop_heap(Gotow.begin(), Gotow.end(), CompareQ());
            Dane current_job = Gotow.back();
            Gotow.pop_back();
            time += current_job.p;
            Cmax = max(Cmax, time + current_job.q);
        } else {
            time = NieUszereg.front().r;
        }
    }
    return Cmax;
}

int schragePodzialSTLHeap(int n, Dane dane[]) {
    vector<Dane> NieUszereg;
    vector<Dane> Gotow;
    for (int i=0; i<n; i++){
        NieUszereg.push_back(dane[i]);
    }
    make_heap(NieUszereg.begin(), NieUszereg.end(), CompareR());

    int time = 0, Cmax = 0;
    Dane current_job;
    current_job.r = 9999999;

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

void ShiftUp(Dane heap[], int index, char ch) {
    while (index > 0 && ((ch == 'r' && heap[(index - 1) / 2].r > heap[index].r) ||
                         (ch == 'q' && heap[(index - 1) / 2].q < heap[index].q))){
        swap(heap[index], heap[(index - 1) / 2]);
        index = (index - 1) / 2;
    }
}

void ShiftDown(Dane heap[], int index, int heapSize, char ch) {
    int leftChild, rightChild, largestChild;
    while (true) {
        leftChild = 2 * index + 1;
        rightChild = 2 * index + 2;
        largestChild = index;

        if (leftChild < heapSize && ((ch == 'r' && heap[leftChild].r < heap[largestChild].r) ||
                                     (ch == 'q' && heap[leftChild].q > heap[largestChild].q))){
            largestChild = leftChild;
        }
        if (rightChild < heapSize && ((ch == 'r' && heap[rightChild].r < heap[largestChild].r) ||
                                      (ch == 'q' && heap[rightChild].q > heap[largestChild].q))){
            largestChild = rightChild;
        }

        if (largestChild == index) {
            break;
        }

        swap(heap[index], heap[largestChild]);
        index = largestChild;
    }
}

void make_Heap (Dane heap[], int heapSize, char ch)
{
    for (int i=heapSize/2; i>0; i--){
        ShiftDown(heap, i, heapSize, ch);
    }
}

void push_Heap (Dane heap[], int& heapSize, Dane value, char ch) {
    if (heapSize == MAX_SIZE) {
        cerr << "Heap is full" << endl;
        return;
    }

    heap[heapSize] = value;
    ShiftUp(heap, heapSize, ch);
    heapSize++;
}

Dane pop_Heap (Dane heap[], int& heapSize, char ch) {
    if (heapSize == 0) {
        cerr << "Heap is empty" << endl;
        Dane emptyDane;
        emptyDane.r = -1;
        return emptyDane;
    }

    Dane maxValue = heap[0];
    heap[0] = heap[heapSize - 1];
    heapSize--;
    ShiftDown(heap, 0, heapSize, ch);
    return maxValue;
}

int schrageTabHeap(int n, Dane dane[]) {
    Dane Gotow[n], NieUszereg[n];
    int gotow = 0, nieUszereg = 0;

    for (int i=0; i<n; i++){
        push_Heap(NieUszereg, nieUszereg, dane[i], 'r');
    }

    int time = 0, Cmax = 0;

    while (gotow != 0 || nieUszereg != 0) {
        while (nieUszereg != 0 && NieUszereg[0].r <= time) {
            push_Heap(Gotow, gotow, NieUszereg[0], 'q');
            pop_Heap(NieUszereg, nieUszereg, 'r');
        }

        if (gotow != 0) {
            Dane current_job = pop_Heap(Gotow, gotow, 'q');
            time += current_job.p;
            Cmax = max(Cmax, time + current_job.q);
        } else {
            time = NieUszereg[0].r;
        }
    }
    return Cmax;
}

int schragePodzialTabHeap(int n, Dane dane[]) {
    Dane Gotow[n], NieUszereg[n];
    int gotow = 0, nieUszereg = 0;

    for (int i=0; i<n; i++){
        push_Heap(NieUszereg, nieUszereg, dane[i], 'r');
    }

    int time = 0, Cmax = 0;
    Dane current_job;
    current_job.r = 9999999;

    while (gotow != 0 || nieUszereg != 0) {
        while (nieUszereg != 0 && NieUszereg[0].r <= time) {
            Dane job = pop_Heap(NieUszereg, nieUszereg, 'r');
            push_Heap(Gotow, gotow, job, 'q');
            if (job.q > current_job.q) {
                current_job.p = time - job.r;
                time = job.r;
                if (current_job.p > 0){
                    push_Heap(Gotow, gotow, current_job, 'q');
                }
            }
        }

        if (gotow != 0) {
            Dane job = pop_Heap(Gotow, gotow, 'q');
            current_job = job;
            time += job.p;
            Cmax = max(Cmax, time + job.q);
        } else {
            time = NieUszereg[0].r;
        }
    }

    return Cmax;
}

int main()
{
    int odp[9][2];
    odp[0][0] = 221;   odp[0][1] = 283;
    odp[1][0] = 3026;  odp[1][1] = 3109;
    odp[2][0] = 3654;  odp[2][1] = 3708;
    odp[3][0] = 3309;  odp[3][1] = 3353;
    odp[4][0] = 3172;  odp[4][1] = 3235;
    odp[5][0] = 3618;  odp[5][1] = 3625;
    odp[6][0] = 3439;  odp[6][1] = 3446;
    odp[7][0] = 3820;  odp[7][1] = 3862;
    odp[8][0] = 3633;  odp[8][1] = 3645;

    string plik, nazwa = "dane", roz = ".txt";
    char p;
    int n;
    int spnh, spsh, spth, snh, ssh, sth;
    for (int j=0; j<9; j++){
        p = j+48;
        plik = nazwa + p + roz;
        ifstream dane_input(plik);

        dane_input >> n;
        Dane dane[n];
        for (int i=0; i<n; i++){
            dane[i].id = i+1;
            dane_input >> dane[i].r >> dane[i].p >> dane[i].q;
        }

        spnh = schragePodzialNotHeap(n, dane);
        spsh = schragePodzialSTLHeap(n, dane);
        spth = schragePodzialTabHeap(n, dane);
        snh = schrageNotHeap(n, dane);
        ssh = schrageSTLHeap(n, dane);
        sth = schrageTabHeap(n, dane);

        cout << "Dane nr." << j << endl;
        cout << "         NotHeap STLHeap TabHeap Odpowedz Poprawnosc" << endl;
        cout << "Podzial:" << setw(8) << spnh
                           << setw(8) << spsh
                           << setw(8) << spth
                           << setw(9) << odp[j][0];
        if (spnh == odp[j][0] && spsh == odp[j][0] && spth == odp[j][0]){
            cout << setw(11) << "true";
        } else {
            cout << setw(11) << "false";
        }
        cout << endl;
        cout << "Schrage:" << setw(8) << snh
                           << setw(8) << ssh
                           << setw(8) << sth
                           << setw(9) << odp[j][1];
        if (snh == odp[j][1] && ssh == odp[j][1] && sth == odp[j][1]){
            cout << setw(11) << "true";
        } else {
            cout << setw(11) << "false";
        }
        cout << endl << endl;
    }


    return 0;
}
