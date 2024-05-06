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

int schrage (int n, Dane* dane, int* Kolejnosc)
{
    int Gotow[n], NieUszereg[n];
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

void Blok (int n, Dane* dane, int* Kolejnosc, int& Id, int& R, int& Q)
{
    int pos=-1, m=0, Cmax=0;
    int tmp[n];
    for (int i=0; i<n; i++){
        int j=Kolejnosc[i];
        tmp[i] = (m>=dane[j].r);
        m = max(m, dane[j].r) + dane[j].p;
        if(Cmax < m+dane[j].q){
            Cmax = m+dane[j].q;
            pos = i;
        }
    }
    int i=pos, j=-1;
    Dane pomoc = dane[Kolejnosc[pos]];
    while (tmp[i]){
        if (dane[Kolejnosc[--i]].q < pomoc.q){
            j = Kolejnosc[i];
            break;
        }
        pomoc.r = min(pomoc.r, dane[Kolejnosc[i]].r);
        pomoc.p += dane[Kolejnosc[i]].p;
    }
    Id = j;
    R = pomoc.r + pomoc.p;
    Q = pomoc.q + pomoc.p;
}

void carlier (int n, Dane* dane, int* Kolejnosc, int& UB)
{
    if(schragePodzial(n, dane) >= UB){
        return;
    }
    int Cmax = schrage(n, dane, Kolejnosc);
    if(Cmax < UB){
        UB = Cmax;
    }
    int Id, R, Q;
    Blok(n, dane, Kolejnosc, Id, R, Q);
    if(Id < 0){
        return;
    }
    int pomR = dane[Id].r;
    int pomQ = dane[Id].q;
    dane[Id].r = R;
    carlier(n, dane, Kolejnosc, UB);
    dane[Id].r = pomR;
    dane[Id].q = Q;
    carlier(n, dane, Kolejnosc, UB);
    dane[Id].q = pomQ;
}

int main()
{
    int odp[9][3];
    odp[0][0] = 221;   odp[0][1] = 283;   odp[0][2] = 228;
    odp[1][0] = 3026;  odp[1][1] = 3109;  odp[1][2] = 3026;
    odp[2][0] = 3654;  odp[2][1] = 3708;  odp[2][2] = 3665;
    odp[3][0] = 3309;  odp[3][1] = 3353;  odp[3][2] = 3309;
    odp[4][0] = 3172;  odp[4][1] = 3235;  odp[4][2] = 3191;
    odp[5][0] = 3618;  odp[5][1] = 3625;  odp[5][2] = 3618;
    odp[6][0] = 3439;  odp[6][1] = 3446;  odp[6][2] = 3446;
    odp[7][0] = 3820;  odp[7][1] = 3862;  odp[7][2] = 3821;
    odp[8][0] = 3633;  odp[8][1] = 3645;  odp[8][2] = 3634;

    string plik, nazwa = "dane", roz = ".txt";
    char p;
    int n;
    int schr, schrPod;

    for (int j=0; j<9; j++){
        if (j== 6){j++;}
        p = j+48;
        plik = nazwa + p + roz;
        ifstream dane_input(plik);

        dane_input >> n;
        Dane dane[n];
        int Kolejnosc[n];
        for (int i=0; i<n; i++){
            dane[i].id = i+1;
            dane_input >> dane[i].r >> dane[i].p >> dane[i].q;
        }
        int UB = schrage(n, dane, Kolejnosc);
        schr = UB;
        schrPod = schragePodzial(n, dane);
        carlier(n, dane, Kolejnosc, UB);

        cout << "Dane nr." << j << endl;
        cout << "         Obliczenia Odpowedz Poprawnosc" << endl;
        cout << "Podzial:" << setw(10) << schrPod
                           << setw(9)  << odp[j][0];
        if (schrPod == odp[j][0]){
            cout << setw(11) << "true";
        } else {
            cout << setw(11) << "false";
        }
        cout << endl;
        cout << "Schrage:" << setw(10) << schr
                           << setw(9)  << odp[j][1];
        if (schr == odp[j][1]){
            cout << setw(11) << "true";
        } else {
            cout << setw(11) << "false";
        }
        cout << endl;
        cout << "Carlier:" << setw(10) << UB
                           << setw(9)  << odp[j][2];
        if (UB == odp[j][2]){
            cout << setw(11) << "true";
        } else {
            cout << setw(11) << "false";
        }
        cout << endl << endl;
    }
    return 0;
}
