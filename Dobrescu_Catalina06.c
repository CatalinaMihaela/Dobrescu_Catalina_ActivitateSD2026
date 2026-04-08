//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//typedef struct Carte Carte;
//typedef struct Nod Nod;
//
//struct Carte {
//    char* titlu;
//    int nrPagini;
//    float pret;
//};
//
//struct Nod {
//    Carte info;
//    Nod* next;
//};
//
//Carte initCarte(const char* titlu, int nrPagini, float pret) {
//    Carte c;
//    c.nrPagini = nrPagini;
//    c.pret = pret;
//
//    c.titlu = (char*)malloc((strlen(titlu) + 1) * sizeof(char));
//    strcpy(c.titlu, titlu);
//
//    return c;
//}
//
//void afisareCarte(Carte c) {
//    printf("\nCartea \"%s\" are %d pagini si costa %.2f lei.",
//        c.titlu, c.nrPagini, c.pret);
//}
//
//void push(Nod** varf, Carte c) {
//    Nod* nou = (Nod*)malloc(sizeof(Nod));
//    nou->info = c;
//    nou->next = *varf;
//    *varf = nou;
//}
//
//Carte pop(Nod** varf) {
//    if (*varf == NULL) {
//        return initCarte("Necunoscuta", 0, 0);
//    }
//
//    Nod* aux = *varf;
//    Carte c = aux->info;
//    *varf = aux->next;
//    free(aux);
//
//    return c;
//}
//
//void put(Nod** coada, Carte c) {
//    Nod* nou = (Nod*)malloc(sizeof(Nod));
//    nou->info = c;
//    nou->next = NULL;
//
//    if (*coada == NULL) {
//        *coada = nou;
//    }
//    else {
//        Nod* aux = *coada;
//        while (aux->next != NULL) {
//            aux = aux->next;
//        }
//        aux->next = nou;
//    }
//}
//
//int main() {
//    Nod* stiva = NULL;
//
//    push(&stiva, initCarte("Morometii", 350, 45.5f));
//    push(&stiva, initCarte("Baltagul", 220, 30.0f));
//    push(&stiva, initCarte("Ion", 410, 50.0f));
//
//    Carte c;
//
//    printf("Traversare stiva:");
//    while (stiva != NULL) {
//        c = pop(&stiva);
//        afisareCarte(c);
//        free(c.titlu);
//    }
//
//    Nod* coada = NULL;
//
//    put(&coada, initCarte("Morometii", 350, 45.5f));
//    put(&coada, initCarte("Baltagul", 220, 30.0f));
//    put(&coada, initCarte("Ion", 410, 50.0f));
//
//    printf("\n\nTraversare coada:");
//    while (coada != NULL) {
//        c = pop(&coada);
//        afisareCarte(c);
//        free(c.titlu);
//    }
//
//    return 0;
//}