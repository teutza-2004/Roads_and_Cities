/*SINTEA Teodora - 314CB*/

#include "functii1.h"
#include "functii2.h"

int main (int argc, char **argv) {
    freopen("tema3.in", "r", stdin);
    freopen("tema3.out", "w", stdout);

    char cerinta[5];
    strcpy(cerinta, argv[1]);

    if (strcmp(cerinta, "1") == 0) {
        int n = 0; // nr de orase din graf
        TLista1 list = NULL;
        int R = 0, K = 0;
        float L = 0;
        Citire1(&R, &K, &L, &n, &list);

        int i = 0;
        for (i = 0; i < K; i++) {
            TreceUnAn1(list);
        }

        Afisare1(list, R);

        VerifUzura1(list, L, R);

        Dezaloc1(list);
        return 0;
    }

    char *orasStart = NULL;
    int K = 0, M = 0, T = 0;
    int n = 0; // nr de orase din graf
    TLista2 list = NULL;
    Citire2(&K, &M, &n, &list, &orasStart);
    int *d = NULL, *tata = NULL;
    d = calloc(n, sizeof(int)); // vector distante minime
    if (!d) {
        exit(1);
    }
    tata = calloc(n, sizeof(int)); // vector de tati
    if (!tata) {
        exit(1);
    }
    Dijkstra2(list, IndiceOras2(list, orasStart), n, d, tata);
    while (T < K && T < n-1) {
        SelectArce2(list, n, d, tata);
        T++;
    }

    printf("%d\n", T);
    Afisare2(list, M);
    Dezaloc2(list, orasStart, d, tata);
    return 0;
}