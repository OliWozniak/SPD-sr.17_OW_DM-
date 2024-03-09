
//#include "../conteinters/dlist.hpp"
//#include "../conteinters/list.hpp"
//#include "../conteinters/p_queue.hpp"

#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
using namespace std;

class Dane{
  public:
    int id;
    int r;
    int p;
    int q;
};

int timeCmax (int n, vector <Dane> dane)
{
    int sumtime=0, Cmax=0, maxtime=0;
    for(int i=0; i<n; i++){
        if (dane[i].r>sumtime){
            sumtime += (dane[i].r - sumtime);
        }
        sumtime += dane[i].p;
        maxtime = sumtime + dane[i].q;
        if (maxtime > Cmax){
            Cmax = maxtime;
        }
    }
    return Cmax;
}

/*void sorting (int n, vector <Dane> &dane)
{
    for (int i=0; i<n; i++){
        for (int j=1; j<n-i; j++){
            if (dane[j-1].r > dane[j].r){
                swap(dane[j-1], dane[j]);
            }
        }
    }

    /*for (int i=0; i<n; i++){
        for (int j=n-1; j>i; j--){
            if (dane[j-1].q < dane[j].q){
                swap(dane[j-1], dane[j]);
            }
        }
    }
}*/

void przerzuc (int n, vector <Dane> pierwszy, vector <Dane> drugi)
{
    for (int i=0; i<n; i++){
        drugi[i] = pierwszy[i];
        cout << pierwszy[i].id << ' ';
    }
}

void sorting (int n, vector <Dane> &dane)
{
    int timemin=9999999, timeC;
    vector <Dane> obliczenia(n);
    vector <Dane> wynik(n);
    obliczenia[0] = dane[0];
    for (int i=1; i<n; i++){
        obliczenia[i] = dane[i];
        for (int j=i; j>-1; j--){
            timeC = timeCmax(i+1, obliczenia);
           /* for (int k=0; k<i+1; k++){
            cout << obliczenia[i].id << ' ';
            }
            cout << endl;*/
            if(timeC<timemin){
                timemin = timeC;
                przerzuc(i+1, obliczenia, wynik);
            }
            if(j>0){
                swap(obliczenia[j], obliczenia[j-1]);
            }
        }
        timemin=9999999;
        przerzuc(i+1, wynik, obliczenia);
    }
    przerzuc(n, wynik, dane);
}

int main()
{
    int n;
    cin >> n;
    vector <Dane> dane(n);
    for (int i=0; i<n; i++){
        dane[i].id = i+1;
        cin >> dane[i].r >> dane[i].p >> dane[i].q;
    }

    clock_t start = clock();
    sorting(n, dane);
    clock_t end = clock();
    double elapsed = double(end - start)/CLOCKS_PER_SEC;
    cout << endl << "Sortowanie danych: " << elapsed << " sekund"  << endl << endl;

    for (int i=0; i<n; i++){
        cout << dane[i].id << ' ';
    }
    cout << endl << endl;
    cout << timeCmax(n, dane) << endl;


    return 0;
}
