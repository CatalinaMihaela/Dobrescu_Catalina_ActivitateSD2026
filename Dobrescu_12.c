#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct Examen Examen;
typedef struct Nod Nod;
typedef struct HashTable HashTable;

struct Examen {
	char* disciplina;
	int nrCandidati;
	float notaMedie;
};

struct Nod {
	Examen info;
	Nod* next;
};

struct HashTable {
	int dimensiune;
	Nod** vector;
};

Examen initExamen(const char* disciplina, int nrCandidati, float notaMedie) {
	Examen e;
	e.nrCandidati = nrCandidati;
	e.notaMedie = notaMedie;

	e.disciplina = (char*)malloc(sizeof(char) * (strlen(disciplina) + 1));
	strcpy(e.disciplina, disciplina);

	return e;
}

void afisareExamen(Examen e) {
	printf("\nLa examenul de la disciplina %s au participat %d candidati, iar nota medie a fost %.2f!",
		e.disciplina, e.nrCandidati, e.notaMedie);
}

void afisareListaExamene(Nod* cap) {
	while (cap != NULL) {
		afisareExamen(cap->info);
		cap = cap->next;
	}
}

void inserareLaSfarsit(Nod** cap, Examen e) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->next = NULL;
	nou->info = e;

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

HashTable initHashTable(int size) {
	HashTable tabela;
	tabela.dimensiune = size;
	tabela.vector = (Nod**)malloc(sizeof(Nod*) * size);

	for (int i = 0; i < size; i++) {
		tabela.vector[i] = NULL;
	}

	return tabela;
}

int hash(int dim, int nrCandidati) {
	return nrCandidati % dim;
}

void inserareHashTable(HashTable tabela, Examen e) {
	if (tabela.dimensiune > 0) {
		int pozitie = hash(tabela.dimensiune, e.nrCandidati);

		if (pozitie >= 0 && pozitie < tabela.dimensiune) {
			inserareLaSfarsit(&(tabela.vector[pozitie]), e);
		}
	}
}

void afisareHashTable(HashTable tabela) {
	for (int i = 0; i < tabela.dimensiune; i++) {
		printf("\nPozitie: %d", i);
		afisareListaExamene(tabela.vector[i]);
	}
}

int calculNumarCandidatiPrimaLista(HashTable tabela) {
	int nrCandidati = 0;
	Nod* capLista0 = tabela.vector[0];

	while (capLista0 != NULL) {
		nrCandidati += capLista0->info.nrCandidati;
		capLista0 = capLista0->next;
	}

	return nrCandidati;
}

void dezalocareLista(Nod** cap) {
	while ((*cap) != NULL) {
		free((*cap)->info.disciplina);

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

	inserareHashTable(tabela, initExamen("Matematica", 60, 7.25));
	inserareHashTable(tabela, initExamen("Informatica", 75, 8.50));
	inserareHashTable(tabela, initExamen("Romana", 48, 6.80));

	afisareHashTable(tabela);

	printf("\nNumarul candidatilor din prima lista a tabelei este: %d!",
		calculNumarCandidatiPrimaLista(tabela));

	dezalocareHashTable(tabela);

	return 0;
}