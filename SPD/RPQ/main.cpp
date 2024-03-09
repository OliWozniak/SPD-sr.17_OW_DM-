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

void sorting (int n, vector <Dane> &dane)
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
    }*/
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
    sorting(n, dane);
    cout << endl;
    for (int i=0; i<n; i++){
        cout << dane[i].id << ' ';
    }
    cout << endl << endl;
    cout << timeCmax(n, dane) << endl;
    return 0;
}
