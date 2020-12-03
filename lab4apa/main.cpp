#include <iostream>
#include <stdlib.h>
#include <time.h>
#define max 1001
using namespace std;
int sm[max][max], vs[max][max], smPRIM[max][max],
vskr[max][max], n;
const int INF = 10000;
int count1 = 0, count2 = 0;
int parent[max] = { 0 }, visited[max] = { 0 };
void cazul_favorabil() {
    cout << "Numarul de virfuri: ";
    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            if (j > i) {
                sm[i][j] = rand() % 10000;
            }
            else if (i > j) {
                sm[i][j] = sm[j][i];
            }
    }
}

void r() {
    count1 = 0;
    count2 = 0;
    for (int i = 0; i < n; i++) {
        parent[i] = 0;
        visited[i] = 0;
        for (int j = 0; j < n; j++) {
            smPRIM[i][j] = vs[i][j];
            vskr[i + 1][j + 1] = vs[i][j];
        }
    }
}

void CazulDefav() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (sm[i][j] && i != j) {
                vs[i][j] = sm[i][j];
            }
            else
                vs[i][j] = INF;
        }
    }
    r();
}

void nrVirfuriFavorabil() {
    cout << "Nr de varfuri: ";
    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            sm[i][i + 1] = rand() % 10000;
    }
}

void CostCazFav() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (sm[i][j] && i != j) {
                vs[i][j] = sm[i][j];
            }
            else
                vs[i][j] = INF;
        }
    }
    r();
}

void NrMediuVarfuri() {
    cout << "Nr de varfuri: ";
    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            if (i % 2 == 0 && j % 2 == 0) {
                j = j + 1;
                sm[i][j] = rand() % 1000;
            }
            else if (i % 2 != 0 && j % 2 != 0) {
                j = j + 1;
                sm[i][j] = rand() % 1000;
            }
            else if (i > j) {
                sm[i][j] = sm[j][i];
            }
    }
}
void costurile_mediu() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (sm[i][j] && i != j) {
                vs[i][j] = sm[i][j];
            }
            else
                vs[i][j] = INF;
        }
    }
    r();
}
int gasire(int i) {
    while (parent[i]) {
        i = parent[i];
        count2++;
    }
    return i;
}
bool uniune(int i, int j) {
    count2++;
    if (i != j) {
        parent[j] = i;
        return true;
    }
    return false;
}
void PRIM() {
    int a, b, u, v, ne = 1, min;
    visited[0] = 1;
    cout << "\nALGORITMUL PRIM: " << endl << endl;
    while (ne < n) {
        count1++;
        min = INF;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (smPRIM[i][j] < min)
                    if (visited[i] != 0) {
                        count1++;
                        min = smPRIM[i][j];
                        a = u = i;
                        b = v = j;
                    }
        if (visited[u] == 0 || visited[v] == 0) {
            //      cout << "\nMuchia " << ne << ":   " << a + 1 << " -> " << b + 1 << ",   Cost: " << min << endl;
            ne++;
            visited[b] = 1;
        }
        smPRIM[a][b] = smPRIM[b][a] = INF;
    }
    cout << endl << "Nr. de iteratii: " << count1 << endl;
}
void KRUSKAL() {
    int a, b, u, v, ne = 1, min;
    cout << "\nALGORITMUL KRUSKAL" << endl << endl;
    while (ne < n) {
        count2++;
        min = INF;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (vskr[i][j] < min) {
                    count1++;
                    min = vskr[i][j];
                    a = u = i;
                    b = v = j;
                }
            }
        }
        u = gasire(u);
        v = gasire(v);
        if (uniune(u, v)) {
            //      cout << "\nMuchia " << ne << ":   " << a << " ---> " << b << ",   Cost: " << min << "\n";
            ne++;
        }
        vskr[a][b] = vskr[b][a] = INF;
    }
    cout << "=========================================\n";
    cout << endl << "Nr. de iteratii: " << count2 << endl;
}
int main() {
    double t1, t2;
    int meniul;
x: while (true) {
    cout << "1. Cazul favorabil.\n" << endl <<
        "2. Cazul mediu.\n" << endl <<
        "3. Cazul defavorabil.\n" << endl <<
        "0. Iesire.\n" << endl;
    cout << "=========================================\n";
    cout << endl << "Optiunea aleasa: ";
    cin >> meniul;
    switch (meniul) {
    case 1:
    {
        while (true) {
            cout << "\n1. Introducerea nr. de varfuri\n" << endl <<
                "2. ALGORITMUL PRIM\n" << endl <<
                "3. ALGORITMUL KRUSKAL\n" << endl <<
                "0. Meniul principal.\n" << endl;
            cout << "=========================================\n";
            cout << endl << "Optiunea aleasa: ";
            cin >> meniul;
            switch (meniul) {
            case 1:
            {
                nrVirfuriFavorabil();
                CostCazFav();
                break;
            }
            case 2:
            {
                t1 = clock();
                PRIM();
                t2 = clock();
                cout << "Timpul de functionare: " << fixed << (t2 - t1) / CLOCKS_PER_SEC << " sec" << endl;
                cout << "=========================================\n";
                break;
            }
            case 3:
            {
                t1 = clock();
                KRUSKAL();
                t2 = clock();
                cout << "Timpul de functionare: " << fixed << (t2 - t1) / CLOCKS_PER_SEC << " sec" << endl;
                cout << "=========================================\n";
                break;
            }
            case 0:
            {
                goto x;
            }
            default:
            {
                cout << "EROARE" << endl;
                break;
            }
            }
        }
    case 2: {
        while (true) {
            cout << "\n1. Introducerea nr. de varfuri\n" << endl <<
                "2. ALGORITMUL PRIM\n" << endl <<
                "3. ALGORITMUL KRUSKAL\n" << endl <<
                "0. Meniul principal.\n" << endl;
            cout << "=========================================\n";
            cout << endl << "Optiunea aleasa: ";
            cin >> meniul;
            switch (meniul) {
            case 1:
            {
                NrMediuVarfuri();
                costurile_mediu();
                break;
            }
            case 2:
            {
                t1 = clock(); PRIM(); t2 = clock();
                cout << "Timpul de functionare: " << fixed << (t2 - t1) / CLOCKS_PER_SEC << " sec" << endl;
                cout << "=========================================\n";
                break;
            }
            case 3:
            {
                t1 = clock(); KRUSKAL(); t2 = clock();
                cout << "Timpul de functionare: " << fixed << (t2 - t1) / CLOCKS_PER_SEC << " sec" << endl;
                cout << "=========================================\n";
                break;
            }
            case 0:
            {
                goto x;
            }
            default:
            {
                cout << "EROARE" << endl;
                break;
            }
            }
        }
    case 3: {
        while (true) {
            cout << "\n1. Introducerea nr. de varfuri\n" << endl <<
                "2. ALGORITMUL PRIM\n" << endl <<
                "3. ALGORITMUL KRUSKAL\n" << endl <<
                "0. Meniul principal.\n" << endl;
            cout << "=========================================\n";
            cout << endl << "Optiunea aleasa: ";
            cin >> meniul;
            switch (meniul) {
            case 1:
            {
                cazul_favorabil();
                CostCazFav();
                break;
            }
            case 2:
            {
                t1 = clock();
                PRIM();
                t2 = clock();
                cout << "Timpul functionare: " << fixed << (t2 - t1) / CLOCKS_PER_SEC << " sec" << endl;
                cout << "=========================================\n";
                break;
            }
            case 3:
            {
                t1 = clock();
                KRUSKAL();
                t2 = clock();
                cout << "Timpul de functionare: " << fixed << (t2 - t1) / CLOCKS_PER_SEC << " sec" << endl;
                cout << "=========================================\n";
                break;
            }
            case 0:
            {
                goto x;
            }
            default:
            {
                cout << "EROARE" << endl;
                break;
            }
            }
        }
    case 0: {
        return 0;
    }
    default: {
        cout << "EROARE" << endl;
        break;
    } } } }
    }
}
return 0;
}
