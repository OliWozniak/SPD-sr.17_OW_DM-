#include <iostream>

using namespace std;

class Dane{
  public:
    int id;
    int ID_Job;
    int Job_num;
    int machin;
    int time;
};
/*
class Machin{
  public:
    int id;
    int ID_Job;
    int Job_num;
    int time;
};*/

void sortTime(int ilosc, Dane *daneAll)
{
    for (int i=0; i<ilosc; i++){
        for (int j=1; j<ilosc-i; j++){
            if(daneAll[j-1].time < daneAll[j].time){
                swap(daneAll[j-1], daneAll[j]);
            }
        }
    }
}

int Cmax(int m, int n, Dane **dane, Dane **machin)
{
    int Cmax=0;
    int tabTimeDane[n][m];
    int tabTimeMachin[m][n];

    for (int i=0; i<n; i++){
        for (int j=0; j<m; j++){
            tabTimeDane[i][j] = dane[i][j].time;
        }
    }

    for (int i=0; i<n; i++){
        for (int j=0; j<m; j++){
            if (machin[j][i].Job_num == 1 && i == 0){
                tabTimeMachin[j][i] = machin[j][i].time;
                tabTimeDane[machin[j][i].ID_Job-1][machin[j][i].Job_num-1] = tabTimeMachin[j][i];
            } else if(i == 0){
                tabTimeMachin[j][i] = machin[j][i].time + tabTimeDane[machin[j][i].ID_Job-1][machin[j][i].Job_num-2];
                tabTimeDane[machin[j][i].ID_Job-1][machin[j][i].Job_num-1] = tabTimeMachin[j][i];
            } else {
                tabTimeMachin[j][i] = max(tabTimeMachin[j][i-1], tabTimeDane[machin[j][i].ID_Job-1][machin[j][i].Job_num-2]) + machin[j][i].time;
                tabTimeDane[machin[j][i].ID_Job-1][machin[j][i].Job_num-1] = tabTimeMachin[j][i];
            }
            Cmax = max(tabTimeMachin[j][i], Cmax);
        }
    }
    return Cmax;
}

void insa(int m, int n, Dane **dane, Dane **machin, Dane *daneAll)
{
    int ilosc=n*m;
    int iloscNaMachine[m];
    /*int timeJob[n][m];
    int timeMachin[m][n];

    for (int i=0; i<m; i++){
        iloscNaMachine[i]=n-1;
        for (int j=0; j<n; j++){
            timeMachin[i][j] = 0;
        }
    }
    for (int i=0; i<n; i++){
        for (int j=0; j<m;j++){
            timeJob[i][j] = 0;
        }
    }*/

    for (int i=0; i<ilosc; i++){
        /*if(iloscNaMachine[daneAll[i].machin-1]==0){
            iloscNaMachine[daneAll[i].machin-1]++;
            machin[daneAll[i].machin-1][0] = daneAll[i];
        }*/
        machin[daneAll[i].machin-1][iloscNaMachine[daneAll[i].machin-1]--] = daneAll[i];
        if (iloscNaMachine[daneAll[i].machin-1] < n-1){
            for (int j=iloscNaMachine[daneAll[i].machin-1]; j<n; j++){

            }
        }
        for (int k=0; k<m; k++){
            for (int j=0; j<n; j++){
                cout << machin[k][j].id << ' ';
            }
            cout << endl;
        }
        cout << endl;

    }
}

int main() {
    int n, m, ilosc, ilosc_na_mach, id;
    cin >> n >> m;// >> ilosc;

    ilosc = n*m;
    Dane **dane = new Dane*[n];
    for (int i=0; i<n; i++){
        dane[i] = new Dane[m];
    }
    Dane daneAll[ilosc];
    for (int i=0; i<n; i++){
        //cin >> ilosc_na_mach;
        for (int j=0; j<m; j++){
            cin >> dane[i][j].machin >> dane[i][j].time;
            id = m*i+j+1;
            dane[i][j].id = id;
            dane[i][j].ID_Job = i+1;
            dane[i][j].Job_num = j+1;
            daneAll[id-1] = dane[i][j];
        }
    }

    Dane **machin = new Dane*[m];
    for (int i=0; i<m; i++){
        machin[i] = new Dane[n];
        for (int j=0; j<n; j++){
            machin[i][j].id = -1;
        }
    }

    /*cout << endl << endl;
    for (int i=0; i<ilosc; i++){
        cout << daneAll[i].ID_Job << daneAll[i].Job_num << ' ';
    }*/

    sortTime(ilosc, daneAll);

    /*cout << endl << endl;
    for (int i=0; i<ilosc; i++){
        cout << daneAll[i].ID_Job << daneAll[i].Job_num << ' ';
    }*/
    cout << endl;
    for (int i=0; i<ilosc; i++){
        cout << daneAll[i].id  << "  ";
    }
    cout << endl;

    insa(m, n, dane, machin, daneAll);

    /*machin[0][0] = dane[0][0];
    machin[0][1] = dane[3][1];
    machin[0][2] = dane[2][0];
    machin[0][3] = dane[1][2];
    machin[1][0] = dane[1][0];
    machin[1][1] = dane[3][2];
    machin[1][2] = dane[2][1];
    machin[1][3] = dane[0][2];
    machin[2][0] = dane[3][0];
    machin[2][1] = dane[1][1];
    machin[2][2] = dane[0][1];
    machin[2][3] = dane[2][2];*/

    /*cout << endl << endl;
    for (int i=0; i<n; i++){
        for (int j=0; j<m; j++){
            cout << dane[i][j].ID_Job << dane[i][j].Job_num << ' ';
        }
        cout << endl;
    }*/
    cout << endl << Cmax(m, n, dane, machin) << endl;
    //cout << endl << endl;
    for (int i=0; i<m; i++){
        for (int j=0; j<n; j++){
            cout << machin[i][j].id << ' ';
        }
        cout << endl;
    }

    return 0;
}

