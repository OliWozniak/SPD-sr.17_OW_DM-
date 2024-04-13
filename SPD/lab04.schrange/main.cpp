#include <iostream>
#include <time.h>
#include <stdlib.h>
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
    sortR(n, dane, NieUszereg);

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

int main()
{
    int n;
    cin >> n;
    Dane dane[n];
    for (int i=0; i<n; i++){
        dane[i].id = i+1;
        cin >> dane[i].r >> dane[i].p >> dane[i].q;
    }
    cout << "Podzial: " << schragePodzial(n, dane) << endl;
	cout << "Schrage: " << schrage(n, dane) << endl;
    return 0;
}
