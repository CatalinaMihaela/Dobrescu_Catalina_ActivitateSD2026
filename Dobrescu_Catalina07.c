#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Carte Carte;
typedef struct Nod Nod;
typedef struct HashTable HashTable;

struct Carte
{
	char* titlu;
	int nrPagini;
	float pret;
};

struct Nod
{
	Carte info;
	Nod* next;
};

struct HashTable
{
	int dimensiune;
	Nod** vector;
};

Carte initCarte(const char* titlu, int nrPagini, float pret)
{
	Carte c;
	c.nrPagini = nrPagini;
	c.pret = pret;

	c.titlu = (char*)malloc((strlen(titlu) + 1) * sizeof(char));
	strcpy(c.titlu, titlu);

	return c;
}

void afisareCarte(Carte c)
{
	printf("\nCartea %s are %d pagini si costa %.2f lei.",
		c.titlu, c.nrPagini, c.pret);
}

void afisareListaCarti(Nod* cap)
{
	while (cap != NULL)
	{
		afisareCarte(cap->info);
		cap = cap->next;
	}
}

void inserareLaSfarsit(Nod** cap, Carte c)
{
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = c;
	nou->next = NULL;

	if (*cap == NULL)
	{
		*cap = nou;
	}
	else
	{
		Nod* aux = *cap;
		while (aux->next != NULL)
		{
			aux = aux->next;
		}
		aux->next = nou;
	}
}

HashTable initHashTable(int size)
{
	HashTable tabela;
	tabela.dimensiune = size;
	tabela.vector = (Nod**)malloc(size * sizeof(Nod*));

	for (int i = 0; i < size; i++)
	{
		tabela.vector[i] = NULL;
	}

	return tabela;
}

int hash(int dim, int nrPagini)
{
	return nrPagini % dim;
}

void inserareHashTable(HashTable tabela, Carte c)
{
	if (tabela.dimensiune > 0)
	{
		int pozitie = hash(tabela.dimensiune, c.nrPagini);
		if (pozitie >= 0 && pozitie < tabela.dimensiune)
		{
			inserareLaSfarsit(&(tabela.vector[pozitie]), c);
		}
	}
}

void afisareHashTable(HashTable tabela)
{
	for (int i = 0; i < tabela.dimensiune; i++)
	{
		printf("\n\nPozitie: %d", i);
		afisareListaCarti(tabela.vector[i]);
	}
}

int calculNrPaginiPrimaLista(HashTable tabela)
{
	int total = 0;
	Nod* capLista0 = tabela.vector[0];

	while (capLista0 != NULL)
	{
		total += capLista0->info.nrPagini;
		capLista0 = capLista0->next;
	}

	return total;
}

void dezalocareLista(Nod** cap)
{
	while (*cap != NULL)
	{
		free((*cap)->info.titlu);
		Nod* aux = *cap;
		*cap = (*cap)->next;
		free(aux);
	}
}

void dezalocareHashTable(HashTable tabela)
{
	for (int i = 0; i < tabela.dimensiune; i++)
	{
		dezalocareLista(&(tabela.vector[i]));
	}
	free(tabela.vector);
}

int main()
{
	HashTable tabela = initHashTable(4);

	inserareHashTable(tabela, initCarte("Morometii", 350, 45.5f));
	inserareHashTable(tabela, initCarte("Ion", 420, 50.0f));
	inserareHashTable(tabela, initCarte("Baltagul", 200, 35.0f));

	afisareHashTable(tabela);

	printf("\n\nNumarul total de pagini din prima lista este: %d",
		calculNrPaginiPrimaLista(tabela));

	dezalocareHashTable(tabela);

	return 0;
}