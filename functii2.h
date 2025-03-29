/*SINTEA Teodora - 314CB*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

// structura pt lista de vecini
typedef struct vecini2 {
    int id; // al catelea traseu este citit
    int cod; // codul orasului
    int dist; // distanta
    char *oras; // numele orasului
    struct vecini2 *urm;
} TV2, *TVecini2;

// structura pt lista de adiacenta
typedef struct lista2 {
    int cod; // codul fiecarui oras
    char *oras;
    TVecini2 vecini;
    struct lista2 *urm;
} TCelula2, *TLista2;

TLista2 AllocCell2 (char *oras, int n);
TVecini2 AllocVecin2 (char *oras, int n, int id);
void InsertVecin2 (TVecini2 *vecini, char *oras, int n, int dist, int id);
int IndiceOras2 (TLista2 list, char *oras);
void Citire2 (int *K, int *M, int *n, TLista2 *list, char **orasStart);
void SelectArce2 (TLista2 list, int n, int *d, int *tata);
void Dijkstra2 (TLista2 list, int codStart, int n, int *d, int *tata);
void Afisare2 (TLista2 list, int M);
void Dezaloc2 (TLista2 list, char *orasStart, int *d, int *tata);