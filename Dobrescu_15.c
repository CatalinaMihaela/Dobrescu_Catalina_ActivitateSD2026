#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct Angajat Angajat;
typedef struct Nod Nod;
typedef struct HashTable HashTable;

struct Angajat {
	char* nume;
	int id;
	float salariu;
};

struct Nod {
	Angajat info;
	Nod* next;
};

struct HashTable {
	int dimensiune;
	Nod** vector;
};

Angajat initAngajat(const char* nume, int id, float salariu) {
	Angajat a;

	a.id = id;
	a.salariu = salariu;

	a.nume = (char*)malloc(sizeof(char) * (strlen(nume) + 1));
	strcpy(a.nume, nume);

	return a;
}

void afisareAngajat(Angajat a) {
	printf("\nAngajatul %s are id-ul %d si salariul %.2f lei.",
		a.nume, a.id, a.salariu);
}

void afisareListaAngajati(Nod* cap) {
	while (cap != NULL) {
		afisareAngajat(cap->info);
		cap = cap->next;
	}
}

void inserareLaSfarsit(Nod** cap, Angajat a) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));

	nou->info = a;
	nou->next = NULL;

	if (*cap == NULL) {
		*cap = nou;
	}
	else {
		Nod* aux = *cap;

		while (aux->next != NULL) {
			aux = aux->next;
		}

		aux->next = nou;
	}
}

HashTable initHashTable(int dim) {
	HashTable tabela;

	tabela.dimensiune = dim;

	tabela.vector = (Nod**)malloc(sizeof(Nod*) * dim);

	for (int i = 0; i < dim; i++) {
		tabela.vector[i] = NULL;
	}

	return tabela;
}

int hash(int dim, int id) {
	return id % dim;
}

void inserareHashTable(HashTable tabela, Angajat a) {
	if (tabela.dimensiune > 0) {

		int pozitie = hash(tabela.dimensiune, a.id);

		if (pozitie >= 0 && pozitie < tabela.dimensiune) {
			inserareLaSfarsit(&(tabela.vector[pozitie]), a);
		}
	}
}

void afisareHashTable(HashTable tabela) {
	for (int i = 0; i < tabela.dimensiune; i++) {

		printf("\nPozitie: %d", i);

		afisareListaAngajati(tabela.vector[i]);
	}
}

float calculSalariiPrimaLista(HashTable tabela) {

	float suma = 0;

	Nod* capLista0 = tabela.vector[0];

	while (capLista0 != NULL) {

		suma += capLista0->info.salariu;

		capLista0 = capLista0->next;
	}

	return suma;
}

void dezalocareLista(Nod** cap) {

	while ((*cap) != NULL) {

		free((*cap)->info.nume);

		Nod* copie = *cap;

		*cap = (*cap)->next;

		free(copie);
	}
}

void dezalocareHashTable(HashTable tabela) {

	for (int i = 0; i < tabela.dimensiune; i++) {

		dezalocareLista(&(tabela.vector[i]));
	}

	free(tabela.vector);
}

int main() {

	HashTable tabela = initHashTable(4);

	inserareHashTable(tabela, initAngajat("Andrei", 101, 4500));
	inserareHashTable(tabela, initAngajat("Maria", 205, 5200));
	inserareHashTable(tabela, initAngajat("Elena", 312, 6100));

	afisareHashTable(tabela);

	printf("\nSuma salariilor din prima lista este: %.2f",
		calculSalariiPrimaLista(tabela));

	dezalocareHashTable(tabela);

	return 0;
}