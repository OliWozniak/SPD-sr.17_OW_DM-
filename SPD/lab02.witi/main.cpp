#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
using namespace std;

class Dane{
  public:
    int id;
    int czas_zadania;
    int kara;
    int termin;
};

int sumaWiti(vector<Dane> dane){

}

int main(){
    int n;
    cin >> n;
    vector <Dane> dane(n);
    for (int i=0; i<n; i++){
        dane[i].id = i+1;
        cin >> dane[i].czas_zadania >> dane[i].kara >> dane[i].termin;
    }

    clock_t start = clock();
    //sorting(n, dane);
    clock_t end = clock();
    double elapsed = double(end - start)/CLOCKS_PER_SEC;
    cout << endl << "Sortowanie danych: " << elapsed << " sekund"  << endl << endl;

}