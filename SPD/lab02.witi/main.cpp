#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

class Dane{
  public:
    int id;
    int czas_zadania;
    int kara;
    int termin;
};


int sumaWiti (int n, vector<Dane> dane){
    int czas=0, suma_kar=0;
    for (int i = 0; i < n; ++i){
        czas+=dane[i].czas_zadania;
        if (dane[i].termin<czas){
            suma_kar+=(czas - dane[i].termin)*dane[i].kara;
        }
    }
    return suma_kar;
}

/*void sorting (int n, vector <Dane> &dane)
{
    int czas=0;
    for (int i=0; i<n; i++){
        czas += dane[i].czas_zadania;
    }
    int kara, minKara=9999999, ind;
    for (int i=0; i<n-1; i++){
        for (int j=0; j<n-i; j++){
            kara = (czas-dane[j].termin)*dane[j].kara;
            cout << kara << endl;
            if (kara < minKara){
                minKara = kara;
                ind = j;
            }
        }
        cout << endl << ind << ' ' << n-i-1 << endl;
        //cout << dane[ind].id << ' ' << dane[n-i-1].id << endl;
        if (ind<n-i-1){
            swap(dane[ind], dane[n-i-1]);
            cout << "AAAAAAAAAAAA" <<endl;
        }
        czas -= dane[n-i-1].czas_zadania;
    }
}*/

void sorting (int n, vector <Dane> &dane)
{
    int timemin = sumaWiti(n,dane), timeW;
    for (int i=0; i<n; i++){
        for (int j=0; j<n; j++){
            if (i != j){
                swap(dane[i], dane[j]);
                timeW = sumaWiti(n,dane);
                if (timeW < timemin){
                    timemin = timeW;
                    i=0; j=0;
                } else {
                    swap(dane[i], dane[j]);
                }
            }
        }
    }
}

int main(){
    for (int j=0; j<11; j++){
    string plik = "dane", roz = ".txt";
    char p = '1', d = j+48;
    if(j==10){
        p='2'; d='0';
    }
    ifstream dane_input(plik + p + d + roz);
    int n;
    dane_input >> n;
    vector <Dane> dane(n);
    for (int i=0; i<n; i++){
        dane[i].id = i+1;
        dane_input >> dane[i].czas_zadania >> dane[i].kara >> dane[i].termin;
    }

    clock_t start = clock();
    for (int i=0; i<2; i++){
        sorting(n, dane);
    }
    //sorting(n, dane);
    clock_t end = clock();
    double elapsed = double(end - start)/CLOCKS_PER_SEC;

    cout << "Kara:\t" << sumaWiti(n,dane)<< endl;
    for (int i=0; i<n; i++){
        cout << dane[i].id << ' ';
    }
    cout << endl << "Sortowanie danych: " << elapsed << " sekund"  << endl << endl;
    }
    return 0;
}
