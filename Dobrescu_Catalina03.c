#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Librarie {
	char* numeLibrarie;
	int nrCarti;
	float suprafata;
};
typedef struct Librarie Librarie;

struct Nod {
	struct Librarie info;
	struct Nod* next;
	struct Nod* prev;
};
typedef struct Nod Nod;

struct ListaDubla {
	struct Nod* prim;
	struct Nod* ultim;
};
typedef struct ListaDubla ListaDubla;

void afisareLibrarie(Librarie l) {
	printf("Nume librarie: %s\n", l.numeLibrarie);
	printf("Numar carti: %d\n", l.nrCarti);
	printf("Suprafata: %.2f\n\n", l.suprafata);
}


void inserareLibrarieListaDubla(ListaDubla* lista, Librarie l) {

	Nod* nou = (Nod*)malloc(sizeof(Nod));

	nou->info = l;
	nou->next = NULL;
	nou->prev = lista->ultim;

	if (lista->ultim != NULL) {
		lista->ultim->next = nou;
	}
	else {
		lista->prim = nou;
	}

	lista->ultim = nou;
}
Librarie citireLibrarieDinFisier(FILE* f) {
	char buffer[100];
	char sep[] = ",\n";
	Librarie l;

	fgets(buffer, 100, f);

	char* aux = strtok(buffer, sep);
	l.numeLibrarie = (char*)malloc(strlen(aux) + 1);
	strcpy(l.numeLibrarie, aux);

	aux = strtok(NULL, sep);
	l.nrCarti = atoi(aux);

	aux = strtok(NULL, sep);
	l.suprafata = (float)atof(aux);

	return l;
}


void traversareListaDubla(ListaDubla lista) {

	Nod* temp = lista.prim;

	while (temp != NULL) {

		afisareLibrarie(temp->info);

		temp = temp->next;
	}
}


char* librarieMinCarti(ListaDubla lista) {

	if (lista.prim == NULL)
		return NULL;

	Nod* temp = lista.prim;
	Nod* minim = lista.prim;

	while (temp != NULL) {

		if (temp->info.nrCarti < minim->info.nrCarti) {
			minim = temp;
		}

		temp = temp->next;
	}

	char* nume = (char*)malloc(strlen(minim->info.numeLibrarie) + 1);
	strcpy(nume, minim->info.numeLibrarie);

	return nume;
}


Librarie cautaLibrarie(ListaDubla lista, const char* nume) {

	Nod* temp = lista.prim;

	Librarie rezultat;
	rezultat.numeLibrarie = NULL;
	rezultat.nrCarti = 0;
	rezultat.suprafata = 0;

	while (temp != NULL) {

		if (strcmp(temp->info.numeLibrarie, nume) == 0) {

			rezultat.numeLibrarie = (char*)malloc(strlen(temp->info.numeLibrarie) + 1);
			strcpy(rezultat.numeLibrarie, temp->info.numeLibrarie);

			rezultat.nrCarti = temp->info.nrCarti;
			rezultat.suprafata = temp->info.suprafata;

			return rezultat;
		}

		temp = temp->next;
	}

	return rezultat;
}


void dezalocareLista(ListaDubla* lista) {

	Nod* temp = lista->prim;

	while (temp != NULL) {

		Nod* aux = temp->next;

		free(temp->info.numeLibrarie);
		free(temp);

		temp = aux;
	}

	lista->prim = NULL;
	lista->ultim = NULL;
}


int main() {

	ListaDubla lista;
	lista.prim = NULL;
	lista.ultim = NULL;

	FILE* f = fopen("librarii.txt", "r");

	if (f != NULL) {

		int nr;
		fscanf(f, "%d", &nr);
		fgetc(f);

		for (int i = 0; i < nr; i++) {

			Librarie l = citireLibrarieDinFisier(f);

			inserareLibrarieListaDubla(&lista, l);
		}

		fclose(f);
	}

	printf("Lista librariilor:\n\n");

	traversareListaDubla(lista);


	printf("\nLibraria cu cele mai putine carti:\n");

	char* numeMinim = librarieMinCarti(lista);

	if (numeMinim != NULL) {
		printf("%s\n", numeMinim);
		free(numeMinim);
	}


	printf("\nCautare librarie:\n");

	Librarie l = cautaLibrarie(lista, "Humanitas");

	if (l.numeLibrarie != NULL) {
		afisareLibrarie(l);
		free(l.numeLibrarie);
	}
	else {
		printf("Nu a fost gasita libraria.\n");
	}


	dezalocareLista(&lista);

	return 0;
}