/*SINTEA Teodora - 314CB*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// structura pt lista de vecini
typedef struct vecini1 {
    int id; // al catelea traseu este citit
    int cod; // codul orasului
    int nr; // nr de tronsoane
    float *tronsoane; // gradul de uzura al tronsoanelor
    float *newt; // auxiliar pentru calcularea uzurii dupa 1 an
    char *oras; // numele orasului
    struct vecini1 *urm;
} TV1, *TVecini1;

// structura pt lista de adiacenta
typedef struct lista1 {
    int cod; // codul fiecarui oras
    char *oras;
    TVecini1 vecini;
    struct lista1 *urm;
} TCelula1, *TLista1;

TLista1 AllocCell1 (char *oras, int n);
TVecini1 AllocVecin1 (char *oras, int n, int id);
void InsertVecin1 (TVecini1 *vecini, char *oras, int n, int nr, float *tronsoane, int id);
int IndiceOras1 (TLista1 list, char *oras);
void swap1 (float *a, float *b);
void Reverse1 (int n, float *tronsoane);
void Citire1 (int *R, int *K, float *L, int *n, TLista1 *list);
void Afisare1 (TLista1 list, int R);
void ModifPrim1 (TLista1 list, int cod, float *tronson, float *newt);
void ModifUltim1 (TLista1 list, int cod, float *tronson, float *newt, int n);
void TreceUnAn1 (TLista1 list);
void VerifUzura1 (TLista1 list, float L, int R);
void Dezaloc1 (TLista1 list);