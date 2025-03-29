/*SINTEA Teodora - 314CB*/

#include "functii2.h"

TLista2 AllocCell2 (char *oras, int n) {
    TLista2 aux = calloc(1, sizeof(TCelula2));
    if (!aux) {
        exit(1);
    }
    aux->cod = n;
    aux->oras = calloc(100, sizeof(char));
    if (!aux->oras) {
        exit(1);
    }
    strcpy(aux->oras, oras);
    aux->urm = NULL;
    aux->vecini = NULL;
    return aux;
}

TVecini2 AllocVecin2 (char *oras, int n, int id) {
    TVecini2 aux = calloc(1, sizeof(TV2));
    if (!aux) {
        exit(1);
    }
    aux->id = id;
    aux->cod = n;
    aux->dist = 0;
    aux->oras = calloc(100, sizeof(char));
    if (!aux->oras) {
        exit(1);
    }
    strcpy(aux->oras, oras);
    aux->urm = NULL;
    return aux;
}

void InsertVecin2 (TVecini2 *vecini, char *oras, int n, int dist, int id) {
    TVecini2 aux = AllocVecin2(oras, n, id);
    aux->dist = dist;
    aux->urm = *vecini;
    *vecini = aux;
}

int IndiceOras2 (TLista2 list, char *oras) {
    int j = 0;
    TLista2 p = list;
    for (p = list; p; p = p->urm, j++) {
        if (strcmp(p->oras, oras) == 0) {
            return j;
        }
    }
    return -1;
}

void Citire2 (int *K, int *M, int *n, TLista2 *list, char **orasStart) {
    *orasStart = calloc(100, sizeof(char));
    if (!(*orasStart)) {
        exit(1);
    }
    scanf("%s", *orasStart);

    scanf("%d", K);
    scanf("%d", M);

    char *oras1 = calloc(100, sizeof(char));
    if (!oras1) {
        exit(1);
    }
    char *oras2 = calloc(100, sizeof(char));
    if (!oras2) {
        exit(1);
    }
    int i = 0;
    for (i = 0; i < *M; i++) {
        scanf("%s", oras1);
        int ok1 = IndiceOras2(*list, oras1); // verifica daca exista orasul deja in lista
        TLista2 aux = NULL;
        if (ok1 == -1) {
            aux = AllocCell2(oras1, *n);
            if (!(*list)) {
                *list = aux;
            } else {
                TLista2 p = *list;
                for (p = *list; p->urm; p = p->urm);
                p->urm = aux;
            }
            ok1 = *n;
            (*n)++;
        }
        scanf("%s", oras2);
        int ok2 = IndiceOras2(*list, oras2); // verifica daca exista orasul deja in lista
        if (ok2 == -1) {
            aux = AllocCell2(oras2, *n);
            if (!(*list)) {
                *list = aux;
            } else {
                TLista2 p = *list;
                for (p = *list; p->urm; p = p->urm);
                p->urm = aux;
            }
            ok2 = *n;
            (*n)++;
        }

        int dist = 0;
        scanf("%d", &dist);
        
        TLista2 p = *list;
        for (p = *list; p; p = p->urm) {
            if (strcmp(p->oras, oras1) == 0) {
                InsertVecin2(&(p->vecini), oras2, ok2, dist, i + 1);
                break;
            }
        }
        for (p = *list; p; p = p->urm) {
            if (strcmp(p->oras, oras2) == 0) {
                InsertVecin2(&(p->vecini), oras1, ok1, dist, -(i + 1));
                break;
            }
        }
    }
    free(oras1);
    free(oras2);
}

void Dijkstra2 (TLista2 list, int codStart, int n, int *d, int *tata) {
    int *v = calloc(n, sizeof(int)); // vector de vizitat
    
    int i = 0;
    for (i = 0; i < n; i++) {
        d[i] = INT_MAX;
        tata[i] = -1;
    }
    d[codStart] = 0;
    tata[codStart] = -1;
    v[codStart] = 0;
    for (i = 0; i < n; i++) {
        int mini = INT_MAX, next = 0, nod = 0;
        for (nod = 0; nod < n; nod++) {
            if (!v[nod] && d[nod] < mini) {
                mini = d[nod];
                next = nod;
            }
        }
        v[next] = 1;
        TLista2 l = list;
        for (l = list; l->cod != next; l = l->urm);
        TVecini2 p = l->vecini;
        for (p = l->vecini; p; p = p->urm) {
            if (!v[p->cod] && d[next] + p->dist < d[p->cod]) {
                d[p->cod] = d[next] + p->dist;
                tata[p->cod] = next;
            }
        }
    }
    d[codStart] = INT_MAX;
    free(v);
}

void SelectArce2 (TLista2 list, int n, int *d, int *tata) {
    int i = 0, minim = INT_MAX, pozMin = 0;
    for (i = 0; i < n; i++) {
        if (minim > d[i]) {
            minim = d[i];
            pozMin = i;
        }
    }
    d[pozMin] = INT_MAX;

    TLista2 l = list;
    for (l = list; l->cod != tata[pozMin]; l = l->urm);
    TVecini2 p = l->vecini;
    for (p = l->vecini; p->cod != pozMin; p = p->urm);
    p->cod *= -1;
    if (p->cod == 0) {
        p->cod = -1;
    }

    for (l = list; l->cod != pozMin; l = l->urm);
    p = l->vecini;
    for (p = l->vecini; p->cod != tata[pozMin]; p = p->urm);
    p->cod *= -1;
    if (p->cod == 0) {
        p->cod = -1;
    }
}

void Afisare2 (TLista2 list, int M) {
    int i = 1;
    for (i = 1; i <= M; i++) {
        TLista2 l = list;
        for (l = list; l; l = l->urm) {
            TVecini2 p = l->vecini;
            for (p = l->vecini; p; p = p->urm) {
                if (p->id == i && p->cod < 0) {
                    printf("%s %s\n", l->oras, p->oras);
                }
            }
        }
    }
}

void Dezaloc2 (TLista2 list, char *orasStart, int *d, int *tata) {
    TLista2 l = list;
    for (l = list; l;) {
        TVecini2 p = l->vecini;
        for (p = l->vecini; p;) {
            free(p->oras);
            TVecini2 aux = p;
            p = p->urm;
            free(aux);
        }
        free(l->oras);
        TLista2 aux = l;
        l = l->urm;
        free(aux);
    }
    free(orasStart);
    free(d);
    free(tata);
}