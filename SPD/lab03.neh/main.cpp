#include <iostream>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include <fstream>
#include <iomanip>
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
        przerzuc(i+1, obliczenia, wynik);
        mintime = timeCmax(i+1, m, obliczenia);
        for (int j=0; j<i; j++){
            swap (obliczenia[j], obliczenia[j+1]);
            timeC = timeCmax(i+1, m, obliczenia);
            if (timeC < mintime){
                mintime = timeC;
                przerzuc(i+1, obliczenia, wynik);
            }
        }
        przerzuc(i+1, wynik, obliczenia);
    }
    przerzuc(n, wynik, dane);
}

int main()
{
    int odp[121];
    odp[0] = 32;
    odp[1] = 1286;
    odp[2] = 1365;
    odp[3] = 1159;
    odp[4] = 1325;
    odp[5] = 1305;
    odp[6] = 1228;
    odp[7] = 1278;
    odp[8] = 1223;
    odp[9] = 1291;
    odp[10] = 1151;
    odp[11] = 1680;
    odp[12] = 1729;
    odp[13] = 1557;
    odp[14] = 1439;
    odp[15] = 1502;
    odp[16] = 1453;
    odp[17] = 1562;
    odp[18] = 1609;
    odp[19] = 1647;
    odp[20] = 1653;
    odp[21] = 2410;
    odp[22] = 2150;
    odp[23] = 2411;
    odp[24] = 2262;
    odp[25] = 2397;
    odp[26] = 2349;
    odp[27] = 2362;
    odp[28] = 2249;
    odp[29] = 2320;
    odp[30] = 2277;
    odp[31] = 2733;
    odp[32] = 2843;
    odp[33] = 2640;
    odp[34] = 2782;
    odp[35] = 2868;
    odp[36] = 2850;
    odp[37] = 2758;
    odp[38] = 2721;
    odp[39] = 2576;
    odp[40] = 2790;
    odp[41] = 3135;
    odp[42] = 3032;
    odp[43] = 2986;
    odp[44] = 3198;
    odp[45] = 3160;
    odp[46] = 3178;
    odp[47] = 3277;
    odp[48] = 3123;
    odp[49] = 3002;
    odp[50] = 3257;
    odp[51] = 4082;
    odp[52] = 3921;
    odp[53] = 3927;
    odp[54] = 3969;
    odp[55] = 3835;
    odp[56] = 3914;
    odp[57] = 3952;
    odp[58] = 3938;
    odp[59] = 3952;
    odp[60] = 4079;
    odp[61] = 5519;
    odp[62] = 5348;
    odp[63] = 5219;
    odp[64] = 5023;
    odp[65] = 5266;
    odp[66] = 5139;
    odp[67] = 5259;
    odp[68] = 5120;
    odp[69] = 5489;
    odp[70] = 5341;
    odp[71] = 5846;
    odp[72] = 5453;
    odp[73] = 5824;
    odp[74] = 5929;
    odp[75] = 5679;
    odp[76] = 5375;
    odp[77] = 5704;
    odp[78] = 5760;
    odp[79] = 6032;
    odp[80] = 5918;
    odp[81] = 6541;
    odp[82] = 6523;
    odp[83] = 6639;
    odp[84] = 6557;
    odp[85] = 6695;
    odp[86] = 6664;
    odp[87] = 6632;
    odp[88] = 6739;
    odp[89] = 6677;
    odp[90] = 6677;
    odp[91] = 10942;
    odp[92] = 10716;
    odp[93] = 11025;
    odp[94] = 11057;
    odp[95] = 10645;
    odp[96] = 10458;
    odp[97] = 10989;
    odp[98] = 10829;
    odp[99] = 10574;
    odp[100] = 10807;
    odp[101] = 11594;
    odp[102] = 11675;
    odp[103] = 11852;
    odp[104] = 11803;
    odp[105] = 11685;
    odp[106] = 11629;
    odp[107] = 11833;
    odp[108] = 11913;
    odp[109] = 11673;
    odp[110] = 11869;
    odp[111] = 26670;
    odp[112] = 27232;
    odp[113] = 26848;
    odp[114] = 27055;
    odp[115] = 26727;
    odp[116] = 26992;
    odp[117] = 26797;
    odp[118] = 27138;
    odp[119] = 26631;
    odp[120] = 26984;
    string plik, nazwa = "dane", roz = ".txt";
    char p = '0', d = '0', t; //pirwsza, druga, trzecia liczby
    int n, m, help;
    bool tf;
    for (int j=0; j<121; j++){
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
        if (odp[j]==timeCmax(n, m, dane)){
            tf = true;
        } else {
            tf = false;
        }

        cout << plik << "  " << setw(5) << timeCmax(n, m, dane) << "  " << setw(6)
             << elapsed << "   " << tf << endl;
        /*for (int i=0; i<n; i++){
            cout << dane[i].id << ' ';
        }
        cout << endl;*/
        //cout << endl << "Sortowanie danych: " << elapsed << " sekund"  << endl;
    }

    return 0;
}
