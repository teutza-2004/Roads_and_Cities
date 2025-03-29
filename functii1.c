/*SINTEA Teodora - 314CB*/

#include "functii1.h"
#define MAX(a, b) a<b ? b:a

TLista1 AllocCell1 (char *oras, int n) {
    TLista1 aux = calloc(1, sizeof(TCelula1));
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

TVecini1 AllocVecin1 (char *oras, int n, int id) {
    TVecini1 aux = calloc(1, sizeof(TV1));
    if (!aux) {
        exit(1);
    }
    aux->id = id;
    aux->cod = n;
    aux->nr = 0;
    aux->oras = calloc(100, sizeof(char));
    if (!aux->oras) {
        exit(1);
    }
    strcpy(aux->oras, oras);
    aux->tronsoane = NULL;
    aux->newt = NULL;
    aux->urm = NULL;
    return aux;
}

void InsertVecin1 (TVecini1 *vecini, char *oras, int n, int nr, float *tronsoane, int id) {
    TVecini1 aux = AllocVecin1(oras, n, id);
    aux->nr = nr;
    aux->tronsoane = calloc(nr + 1, sizeof(float));
    if (!(aux->tronsoane)) {
        exit(1);
    }
    memcpy(aux->tronsoane, tronsoane, nr * sizeof(float));
    aux->newt = calloc(nr, sizeof(float));
    if (!(aux->newt)) {
        exit(1);
    }
    aux->urm = *vecini;
    *vecini = aux;
}

int IndiceOras1 (TLista1 list, char *oras) {
    int j = 0;
    TLista1 p = list;
    for (p = list; p; p = p->urm, j++) {
        if (strcmp(p->oras, oras) == 0) {
            return j;
        }
    }
    return -1;
}

void swap1 (float *a, float *b) {
    float aux = *a;
    *a = *b;
    *b = aux;
}

void Reverse1 (int n, float *tronsoane) {
    int i = 0;
    for (i = 0; i < n/2; i++) {
        swap1(&(tronsoane[i]), &(tronsoane[n-i-1]));
    }
}

void Citire1 (int *R, int *K, float *L, int *n, TLista1 *list) {
    scanf("%d", R);
    scanf("%d", K);
    scanf("%f", L);

    char *oras1 = calloc(100, sizeof(char));
    if (!oras1) {
        exit(1);
    }
    char *oras2 = calloc(100, sizeof(char));
    if (!oras2) {
        exit(1);
    }
    int i = 0;
    for (i = 0; i < *R; i++) {
        scanf("%s", oras1);
        int ok1 = IndiceOras1(*list, oras1); // verifica daca exista orasul deja in lista
        TLista1 aux = NULL;
        if (ok1 == -1) {
            aux = AllocCell1(oras1, *n);
            if (!(*list)) {
                *list = aux;
            } else {
                TLista1 p = *list;
                for (p = *list; p->urm; p = p->urm);
                p->urm = aux;
            }
            ok1 = *n;
            (*n)++;
        }
        scanf("%s", oras2);
        int ok2 = IndiceOras1(*list, oras2); // verifica daca exista orasul deja in lista
        if (ok2 == -1) {
            aux = AllocCell1(oras2, *n);
            if (!(*list)) {
                *list = aux;
            } else {
                TLista1 p = *list;
                for (p = *list; p->urm; p = p->urm);
                p->urm = aux;
            }
            ok2 = *n;
            (*n)++;
        }

        int nr = 0;
        float *tronsoane = NULL;
        scanf("%d", &nr);
        tronsoane = calloc(nr, sizeof(float));
        int j = 0;
        for (j = 0; j < nr; j++) {
            scanf("%f", &tronsoane[j]);
        }
        
        TLista1 p = *list;
        for (p = *list; p; p = p->urm) {
            if (strcmp(p->oras, oras1) == 0) {
                InsertVecin1(&(p->vecini), oras2, ok2, nr, tronsoane, i + 1);
                break;
            }
        }
        Reverse1(nr, tronsoane);
        for (p = *list; p; p = p->urm) {
            if (strcmp(p->oras, oras2) == 0) {
                InsertVecin1(&(p->vecini), oras1, ok1, nr, tronsoane, -(i + 1));
                break;
            }
        }
        free(tronsoane);
    }
    free(oras1);
    free(oras2);
}

void Afisare1 (TLista1 list, int R) {
    int i = 0;
    for (i = 0; i < R; i++) {
        TLista1 l = list;
        for (l = list; l; l = l->urm) {
            TVecini1 p = l->vecini;
            for (p = l->vecini; p; p = p->urm) {
                if (p->id == i + 1) {
                    printf("%s %s %d ", l->oras, p->oras, p->nr);
                    int j = 0;
                    for (j = 0; j < p->nr; j++) {
                        printf("%.2f ", p->tronsoane[j]);
                    }
                    printf("\n");
                }
            }
        }
    }
}

// cod este codul orasului din care plec
void ModifPrim1 (TLista1 list, int cod, float *tronson, float *newt) {
    if (tronson[0] && tronson[0] != 100) {
        newt[0] = tronson[0] * 2;
        if (newt[0] > 100) {
            newt[0] = 100;
        }
        return;
    }
    if (tronson[0] == 0) {
        float maxim = 0; // tin maximul dintre val vecine
        if (tronson[1]) {
            maxim = tronson[1];
        }
        TLista1 l = list;
        for (l = list; l; l = l->urm) {
            TVecini1 p = l->vecini;
            for (p = l->vecini; p; p = p->urm) {
                if (p->cod == cod) {
                    maxim = MAX(maxim, p->tronsoane[p->nr - 1]);
                    break;
                }
            }
        }
        newt[0] = maxim / 2;
    }
}

//cod este codul orasului din care plec, n este nr de tronsoane
void ModifUltim1 (TLista1 list, int cod, float *tronson, float *newt, int n) {
    if (tronson[n] && tronson[n] != 100) {
        newt[n] = tronson[n] * 2;
        if (newt[n] > 100) {
            newt[n] = 100;
        }
        return;
    }
    if (tronson[n] == 0) {
        float maxim = 0; // tin maximul dintre val vecine
        if (n) {
            maxim = tronson[n - 1];
        }
        TLista1 l = list;
        for (l = list; l; l = l->urm) {
            if (l->cod == cod) {
                TVecini1 p = l->vecini;
                for (p = l->vecini; p; p = p->urm) {
                    maxim = MAX(maxim, p->tronsoane[0]);
                }
                break;
            }
        }
        newt[n] = maxim / 2;
    }
}

void TreceUnAn1 (TLista1 list) {
    TLista1 l = list;
    for (l = list; l; l = l->urm) {
        TVecini1 p = l->vecini;
        for (p = l->vecini; p; p = p->urm) {
            int i = 1;
            for (i = 1; i < p->nr - 1; i++) {
                if (p->tronsoane[i] && p->tronsoane[i] != 100) {
                    p->newt[i] = p->tronsoane[i] * 2;
                    if (p->newt[i] > 100) {
                        p->newt[i] = 100;
                    }
                } else if (p->tronsoane[i] == 0) {
                    p->newt[i] = MAX(p->tronsoane[i-1], p->tronsoane[i+1]);
                    p->newt[i] /= 2;
                }
            }
            ModifPrim1(list, l->cod, p->tronsoane, p->newt);
            ModifUltim1(list, p->cod, p->tronsoane, p->newt, p->nr - 1);
        }
    }

    for (l = list; l; l = l->urm) {
        TVecini1 p = l->vecini;
        for (p = l->vecini; p; p = p->urm) {
            int i = 0;
            for (i = 0; i < p->nr; i++) {
                p->tronsoane[i] = p->newt[i];
            }
        }
    }
}

void VerifUzura1 (TLista1 list, float L, int R) {
    int ind = 1;
    for (ind = 1; ind <= R; ind++) {
        TLista1 l = list;
        for (l = list; l; l = l->urm) {
            TVecini1 p = l->vecini;
            for (p = l->vecini; p; p = p->urm) {
                if (p->id == ind) {
                    int i = 0;
                    float sum = 0;
                    for (i = 0; i < p->nr; i++) {
                        sum += p->tronsoane[i];
                    }
                    sum /= p->nr;
                    if (sum < L){
                        printf("%d ", ind);
                    }
                }
            }
        }
    }
}

void Dezaloc1 (TLista1 list) {
    TLista1 l = list;
    for (l = list; l;) {
        TVecini1 p = l->vecini;
        for (p = l->vecini; p;) {
            free(p->newt);
            free(p->tronsoane);
            free(p->oras);
            TVecini1 aux = p;
            p = p->urm;
            free(aux);
        }
        free(l->oras);
        TLista1 aux = l;
        l = l->urm;
        free(aux);
    }

}