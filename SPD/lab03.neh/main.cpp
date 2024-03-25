#include <iostream>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include <fstream>
using namespace std;

class Dane{
  public:
    int id;
    vector <int> stream;
    int sumtime;
};

int timeCmax (int n, int m, vector <Dane> dane)
{
    int Cmax[m];
    Cmax[0] = dane[0].stream[0];
    for (int i=1; i<m; i++){
        Cmax[i] = Cmax[i-1] + dane[0].stream[i];
    }
    for (int i=1; i<n; i++){
        Cmax[0] += dane[i].stream[0];
        for (int j=1; j<m; j++){
            Cmax[j] = max(Cmax[j-1], Cmax[j]) + dane[i].stream[j];
        }
    }
    return Cmax[m-1];
}

void przerzuc (int n, vector <Dane> &pierwszy, vector <Dane> &drugi)
{
    for (int i=0; i<n; i++){
        drugi[i] = pierwszy[i];
    }
}

void print (int n, vector <Dane> dane)
{
    for (int i=0; i<n; i++){
        cout << dane[i].id << ' ';
    }
    cout << endl;
}

void SumTimeFoStream (int n, int m, vector <Dane> &dane)
{
    int sum = 0;
    for (int i=0; i<n; i++){
        for (int j=0; j<m; j++){
            sum += dane[i].stream[j];
        }
        dane[i].sumtime = sum;
        sum = 0;
    }
}

void sortTime (int n, vector <Dane> &dane)
{
    for (int i=0; i<n; i++){
        for (int j=n-1; j>i; j--){
            if (dane[j].sumtime > dane[j-1].sumtime){
                swap(dane[j], dane[j-1]);
            }
        }
    }
}

void sortQueue (int n, int m, vector <Dane> &dane)
{
    vector <Dane> obliczenia(1);
    vector <Dane> wynik(n);
    obliczenia[0] = dane[0];
    int mintime, timeC;
    for (int i=1; i<n; i++){
        obliczenia.insert(obliczenia.begin(), dane[i]);
        print(i+1, obliczenia);
        przerzuc(i+1, obliczenia, wynik);
        mintime = timeCmax(i+1, m, obliczenia);
        for (int j=0; j<i; j++){
            swap (obliczenia[j], obliczenia[j+1]);
            print(i+1, obliczenia);
            timeC = timeCmax(i+1, m, dane);
            cout << timeC << ' ' << mintime << endl;
            if (timeC <= mintime){
                mintime = timeC;
                przerzuc(i+1, obliczenia, wynik);
            }
        }
        print(i+1, wynik);
        cout <<endl;
        przerzuc(i+1, wynik, obliczenia);
    }
    przerzuc(n, wynik, dane);
}

int main()
{
    string plik, nazwa = "dane", roz = ".txt";
    char p = '0', d = '0', t; //pirwsza, druga, trzecia liczby
    int n, m, help;
    for (int j=0; j<1; j++){
        t = (j%10)+48;
        d = ((j/10)%10)+48;
        p = ((j/100)%10)+48;
        plik = nazwa + p + d + t + roz;
        ifstream dane_input(plik);

        dane_input >> n >> m;
        vector <Dane> dane(n);
        for (int i=0; i<n; i++){
            dane[i].id = i+1;
            for (int j=0; j<m; j++){
                dane_input >> help;
                dane[i].stream.push_back(help);
            }
        }
        SumTimeFoStream(n, m, dane);

        clock_t start = clock();
        sortTime(n, dane);
        sortQueue(n, m, dane);
        clock_t end = clock();
        double elapsed = double(end - start)/CLOCKS_PER_SEC;

        cout << plik << "  " << timeCmax(n, m, dane) << "  " << elapsed << endl;
        for (int i=0; i<n; i++){
            cout << dane[i].id << ' ';
        }
        cout << endl;
        //cout << endl << "Sortowanie danych: " << elapsed << " sekund"  << endl;
    }

    return 0;
}
