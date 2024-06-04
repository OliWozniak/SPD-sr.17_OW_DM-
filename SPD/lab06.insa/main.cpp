#include <iostream>
#include <fstream>
#include <climits>

using namespace std;

class Dane
{
public:
    int id;
    int ID_Job;
    int Job_num;
    int machin;
    int time;
};

void sortTime(int ilosc, Dane *daneAll)
{
    for (int i = 0; i < ilosc; i++)
    {
        for (int j = 1; j < ilosc - i; j++)
        {
            if (daneAll[j - 1].time < daneAll[j].time)
            {
                swap(daneAll[j - 1], daneAll[j]);
            }
        }
    }
}

int timeCmax(int m, int n, Dane **dane, Dane **machin)
{
    int Cmax = 0;
    int licz = 0;
    int statusCzyJestNieOblicz;
    int timePrzed;
    int timePrzedJob;
    int statusJob[n][m];
    int tabTimeDane[n][m];
    int jestObliczony[n][m];
    int tabTimeMachin[m][n];

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            tabTimeDane[i][j] = dane[i][j].time;
            jestObliczony[i][j] = -1;
            statusJob[i][j] = 1;
            tabTimeMachin[j][i] = 0;
        }
    }

    do
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (jestObliczony[machin[j][i].ID_Job - 1][machin[j][i].Job_num - 1] == -1)
                {
                    timePrzedJob = 0;
                    if (machin[j][i].Job_num - 2 > -1)
                    {
                        if (jestObliczony[machin[j][i].ID_Job - 1][machin[j][i].Job_num - 2] == 1)
                        {
                            timePrzedJob = tabTimeDane[machin[j][i].ID_Job - 1][machin[j][i].Job_num - 2];
                        }
                        else
                        {
                            statusJob[machin[j][i].ID_Job - 1][machin[j][i].Job_num - 1] = 2;
                        }
                    }

                    timePrzed = 0;
                    if (i > 0)
                    {
                        if (jestObliczony[machin[j][i - 1].ID_Job - 1][machin[j][i - 1].Job_num - 1] == 1)
                        {
                            timePrzed = tabTimeMachin[j][i - 1];
                        }
                        else
                        {
                            statusJob[machin[j][i].ID_Job - 1][machin[j][i].Job_num - 1] = 2;
                        }
                    }

                    if (statusJob[machin[j][i].ID_Job - 1][machin[j][i].Job_num - 1] == 1)
                    {
                        tabTimeMachin[j][i] = machin[j][i].time + max(timePrzed, timePrzedJob);
                        tabTimeDane[machin[j][i].ID_Job - 1][machin[j][i].Job_num - 1] = tabTimeMachin[j][i];
                        jestObliczony[machin[j][i].ID_Job - 1][machin[j][i].Job_num - 1] = 1;
                        Cmax = max(tabTimeMachin[j][i], Cmax);
                    }
                }
            }
        }

        statusCzyJestNieOblicz = 0;

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (statusJob[i][j] == 2)
                {
                    statusCzyJestNieOblicz = 1;
                    statusJob[i][j] = 1;
                }
            }
        }

        licz++;
        if (licz == 100)
        {
            licz = 0;
            return INT_MAX;
        }

    } while (statusCzyJestNieOblicz == 1);

    return Cmax;
}

void timeJobLeftToRight(int n, int m, Dane **dane, Dane **machin, int **statusJob, int **tabMachinLeftToRight, int **tabJobLeftToRight)
{
    int statusCzyJestNieOblicz;
    int timePrzed;
    int timePrzedJob;
    int tabTimeDane[n][m];
    int jestObliczony[n][m];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            tabTimeDane[i][j] = dane[i][j].time;
            tabMachinLeftToRight[j][i] = 0;
            jestObliczony[i][j] = 1;
        }
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (machin[j][i].id != -1)
            {
                jestObliczony[machin[j][i].ID_Job - 1][machin[j][i].Job_num - 1] = -1;
            }
        }
    }

    do
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (jestObliczony[machin[j][i].ID_Job - 1][machin[j][i].Job_num - 1] == -1)
                {
                    timePrzedJob = 0;
                    for (int k = machin[j][i].Job_num - 2; k > -1; k--)
                    {
                        if (statusJob[machin[j][i].ID_Job - 1][k] != -1)
                        {
                            if (jestObliczony[machin[j][i].ID_Job - 1][k] == 1)
                            {
                                timePrzedJob = tabTimeDane[machin[j][i].ID_Job - 1][k];
                            }
                            else
                            {
                                statusJob[machin[j][i].ID_Job - 1][machin[j][i].Job_num - 1] = 2;
                            }
                            break;
                        }
                    }

                    timePrzed = 0;
                    if (i > 0)
                    {
                        if (machin[j][i - 1].id != -1)
                        {
                            if (jestObliczony[machin[j][i - 1].ID_Job - 1][machin[j][i - 1].Job_num - 1] == 1)
                            {
                                timePrzed = tabMachinLeftToRight[j][i - 1];
                            }
                            else
                            {
                                statusJob[machin[j][i].ID_Job - 1][machin[j][i].Job_num - 1] = 2;
                            }
                        }
                    }

                    if (statusJob[machin[j][i].ID_Job - 1][machin[j][i].Job_num - 1] == 1)
                    {
                        tabMachinLeftToRight[j][i] = machin[j][i].time + max(timePrzed, timePrzedJob);
                        tabJobLeftToRight[machin[j][i].ID_Job - 1][machin[j][i].Job_num - 1] = tabMachinLeftToRight[j][i];
                        tabTimeDane[machin[j][i].ID_Job - 1][machin[j][i].Job_num - 1] = tabMachinLeftToRight[j][i];
                        jestObliczony[machin[j][i].ID_Job - 1][machin[j][i].Job_num - 1] = 1;
                    }
                }
            }
        }

        statusCzyJestNieOblicz = 0;

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (statusJob[i][j] == 2)
                {
                    statusCzyJestNieOblicz = 1;
                    statusJob[i][j] = 1;
                }
            }
        }

    } while (statusCzyJestNieOblicz == 1);
}

void timeJobRightToLeft(int n, int m, Dane **dane, Dane **machin, int **statusJob, int **tabMachinRightToLeft, int **tabJobRightToLeft)
{
    int statusCzyJestNieOblicz;
    int timePo;
    int timePoJob;
    int tabTimeDane[n][m];
    int jestObliczony[n][m];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            tabTimeDane[i][j] = dane[i][j].time;
            tabMachinRightToLeft[j][i] = 0;
            jestObliczony[i][j] = 1;
        }
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (machin[j][i].id != -1)
            {
                jestObliczony[machin[j][i].ID_Job - 1][machin[j][i].Job_num - 1] = -1;
            }
        }
    }

    do
    {
        for (int i = n - 1; i > -1; i--)
        {
            for (int j = m - 1; j > -1; j--)
            {
                if (jestObliczony[machin[j][i].ID_Job - 1][machin[j][i].Job_num - 1] == -1)
                {
                    timePoJob = 0;
                    for (int k = machin[j][i].Job_num; k < m; k++)
                    {
                        if (statusJob[machin[j][i].ID_Job - 1][k] != -1)
                        {
                            if (jestObliczony[machin[j][i].ID_Job - 1][k] == 1)
                            {
                                timePoJob = tabTimeDane[machin[j][i].ID_Job - 1][k];
                            }
                            else
                            {
                                statusJob[machin[j][i].ID_Job - 1][machin[j][i].Job_num - 1] = 2;
                            }
                            break;
                        }
                    }

                    timePo = 0;
                    if (i < n - 1)
                    {
                        if (machin[j][i + 1].id != -1)
                        {
                            if (jestObliczony[machin[j][i + 1].ID_Job - 1][machin[j][i + 1].Job_num - 1] == 1)
                            {
                                timePo = tabMachinRightToLeft[j][i + 1];
                            }
                            else
                            {
                                statusJob[machin[j][i].ID_Job - 1][machin[j][i].Job_num - 1] = 2;
                            }
                        }
                    }

                    if (statusJob[machin[j][i].ID_Job - 1][machin[j][i].Job_num - 1] == 1)
                    {
                        tabMachinRightToLeft[j][i] = machin[j][i].time + max(timePo, timePoJob);
                        tabJobRightToLeft[machin[j][i].ID_Job - 1][machin[j][i].Job_num - 1] = tabMachinRightToLeft[j][i];
                        tabTimeDane[machin[j][i].ID_Job - 1][machin[j][i].Job_num - 1] = tabMachinRightToLeft[j][i];
                        jestObliczony[machin[j][i].ID_Job - 1][machin[j][i].Job_num - 1] = 1;
                    }
                }
            }
        }

        statusCzyJestNieOblicz = 0;

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (statusJob[i][j] == 2)
                {
                    statusCzyJestNieOblicz = 1;
                    statusJob[i][j] = 1;
                }
            }
        }

    } while (statusCzyJestNieOblicz == 1);
}

void insa(int m, int n, Dane **dane, Dane **machin, Dane *daneAll)
{
    int pos;
    int wybor;
    int wyboroptymalny;
    int timePo;
    int timePoJob;
    int timePrzed;
    int timePrzedJob;
    int ilosc = n * m;
    int iloscNaMachine[m];

    int **tabJobLeftToRight = new int *[n];
    int **tabJobRightToLeft = new int *[n];
    int **tabMachinLeftToRight = new int *[m];
    int **tabMachinRightToLeft = new int *[m];
    int **statusJob = new int *[n];
    for (int i = 0; i < m; i++)
    {
        tabMachinLeftToRight[i] = new int[n];
        tabMachinRightToLeft[i] = new int[n];
        for (int j = 0; j < n; j++)
        {
            tabMachinLeftToRight[i][j] = 0;
            tabMachinRightToLeft[i][j] = 0;
        }
    }
    for (int i = 0; i < n; i++)
    {
        statusJob[i] = new int[m];
        tabJobLeftToRight[i] = new int[m];
        tabJobRightToLeft[i] = new int[m];
        for (int j = 0; j < m; j++)
        {
            tabJobLeftToRight[i][j] = 0;
            tabJobRightToLeft[i][j] = 0;
            statusJob[i][j] = -1;
        }
    }

    for (int i = 0; i < m; i++)
    {
        iloscNaMachine[i] = n - 1;
    }

    for (int i = 0; i < ilosc; i++)
    {
        if (iloscNaMachine[daneAll[i].machin - 1] == n - 1)
        {
            machin[daneAll[i].machin - 1][iloscNaMachine[daneAll[i].machin - 1]--] = daneAll[i];
            statusJob[daneAll[i].ID_Job - 1][daneAll[i].Job_num - 1] = 1;
        }
        else
        {
            wyboroptymalny = INT_MAX;

            timePrzedJob = 0;
            for (int j = daneAll[i].Job_num - 2; j > -1; j--)
            {
                if (statusJob[daneAll[i].ID_Job - 1][j] == 1)
                {
                    timePrzedJob = tabJobLeftToRight[daneAll[i].ID_Job - 1][j];
                    break;
                }
            }

            timePoJob = 0;
            for (int j = daneAll[i].Job_num; j < m; j++)
            {
                if (statusJob[daneAll[i].ID_Job - 1][j] == 1)
                {
                    timePoJob = tabJobRightToLeft[daneAll[i].ID_Job - 1][j];
                    break;
                }
            }

            for (int j = iloscNaMachine[daneAll[i].machin - 1]; j < n; j++)
            {
                if (j > -1)
                {
                    timePrzed = tabMachinLeftToRight[daneAll[i].machin - 1][j];
                }
                else
                {
                    timePrzed = 0;
                }

                if (j + 1 < n)
                {
                    timePo = tabMachinRightToLeft[daneAll[i].machin - 1][j + 1];
                }
                else
                {
                    timePo = 0;
                }

                wybor = max(timePrzedJob, timePrzed) + max(timePoJob, timePo) + daneAll[i].time;

                if (wybor < wyboroptymalny)
                {
                    pos = j;
                    wyboroptymalny = wybor;
                }
            }
            machin[daneAll[i].machin - 1][iloscNaMachine[daneAll[i].machin - 1]--] = daneAll[i];
            statusJob[daneAll[i].ID_Job - 1][daneAll[i].Job_num - 1] = 1;

            for (int j = iloscNaMachine[daneAll[i].machin - 1] + 1; j < n; j++)
            {
                if (j < pos)
                {
                    swap(machin[daneAll[i].machin - 1][j], machin[daneAll[i].machin - 1][j + 1]);
                }
            }
        }

        timeJobLeftToRight(n, m, dane, machin, statusJob, tabMachinLeftToRight, tabJobLeftToRight);
        timeJobRightToLeft(n, m, dane, machin, statusJob, tabMachinRightToLeft, tabJobRightToLeft);
    }

    // próba przestawiać dopóki nie osięgnie minimum
    int Cmax, CmaxAktual;
    Cmax = timeCmax(m, n, dane, machin);
    for (int i = 0; i < m; i++)
    {
        for (int j = 1; j < n; j++)
        {
            swap(machin[i][j - 1], machin[i][j]);
            CmaxAktual = timeCmax(m, n, dane, machin);
            if (CmaxAktual < Cmax)
            {
                Cmax = CmaxAktual;
                i = 0;
                j = 1;
            }
            else
            {
                swap(machin[i][j - 1], machin[i][j]);
            }
        }
    }

    /*Cmax = timeCmax(m, n, dane, machin);
    for (int i=m-1; i>-1; i--){
        for (int j=n-1; j>0; j--){
            swap(machin[i][j-1], machin[i][j]);
            CmaxAktual = timeCmax(m, n, dane, machin);
            if (CmaxAktual < Cmax){
                Cmax = CmaxAktual;
                i=0; j=1;
            } else {
                swap(machin[i][j-1], machin[i][j]);
            }
        }
    }*/
}

int main()
{

    clock_t start_total = clock();
    clock_t end = clock();
    double elapsed;

    string plik, nazwa = "./dane/data.0";

    for (int set = 0; set < 80; set++)
    {

        string p = to_string(set);
        plik = nazwa;
        if (set<10)
        {
            plik+='0';
        }
        plik+=p;
        cout << plik << endl;
        ifstream dane_input(plik);

        int n, m, ilosc, ilosc_na_mach, id;
        dane_input >> n >> m >> ilosc;

        clock_t start= clock();

        ilosc = n * m;
        Dane **dane = new Dane *[n];
        for (int i = 0; i < n; i++)
        {
            dane[i] = new Dane[m];
        }
        Dane daneAll[ilosc];
        for (int i = 0; i < n; i++)
        {
           dane_input >> ilosc_na_mach;
            for (int j = 0; j < m; j++)
            {
                dane_input >> dane[i][j].machin >> dane[i][j].time;
                id = m * i + j + 1;
                dane[i][j].id = id;
                dane[i][j].ID_Job = i + 1;
                dane[i][j].Job_num = j + 1;
                daneAll[id - 1] = dane[i][j];
            }
        }

        sortTime(ilosc, daneAll);

        Dane **machin = new Dane *[m];
        for (int i = 0; i < m; i++)
        {
            machin[i] = new Dane[n];
            for (int j = 0; j < n; j++)
            {
                machin[i][j].id = -1;
                machin[i][j].ID_Job = daneAll[ilosc - 1].ID_Job;
                machin[i][j].Job_num = daneAll[ilosc - 1].Job_num;
            }
        }

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

        /*machin[0][0] = dane[2][0];
        machin[0][1] = dane[0][0];
        machin[0][2] = dane[1][1];
        machin[1][0] = dane[1][0];
        machin[1][1] = dane[2][1];
        machin[1][2] = dane[0][1];*/

        /*machin[0][0] = dane[2][0];
        machin[0][1] = dane[1][1];
        machin[0][2] = dane[3][0];
        machin[0][3] = dane[0][1];
        machin[1][0] = dane[2][1];
        machin[1][1] = dane[1][2];
        machin[1][2] = dane[3][2];
        machin[1][3] = dane[0][3];
        machin[2][0] = dane[0][0];
        machin[2][1] = dane[2][2];
        machin[2][2] = dane[3][1];
        machin[2][3] = dane[1][3];
        machin[3][0] = dane[1][0];
        machin[3][1] = dane[2][3];
        machin[3][2] = dane[0][2];
        machin[3][3] = dane[3][3];*/

        cout << "Cmax:\t"
             << timeCmax(m, n, dane, machin) << endl;

        /*for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cout << machin[i][j].id << ' ';
            }
            cout << endl;
        }*/
        end = clock();
        elapsed = double(end - start)/CLOCKS_PER_SEC;
        cout << "Czas pracy algorytmu:\t" << elapsed << endl << endl;
    }
    end = clock();
    elapsed = double(end - start_total)/CLOCKS_PER_SEC;
    cout << "Czas całkowity:\t" << elapsed<< endl;

    return 0;
}
