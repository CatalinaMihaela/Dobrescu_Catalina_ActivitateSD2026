#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct StructuraCarte {
	int id;
	int nrPagini;
	float pret;
	char* titlu;
	char* autor;
	unsigned char categorie;
};
typedef struct StructuraCarte Carte;


struct Nod {
	Carte info;
	struct Nod* stanga;
	struct Nod* dreapta;
};
typedef struct Nod Nod;

Carte citireCarteDinFisier(FILE* file) {
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, file);
	char* aux;
	Carte c1;
	aux = strtok(buffer, sep);
	c1.id = atoi(aux);
	c1.nrPagini = atoi(strtok(NULL, sep));
	c1.pret = atof(strtok(NULL, sep));
	aux = strtok(NULL, sep);
	c1.titlu = malloc(strlen(aux) + 1);
	strcpy_s(c1.titlu, strlen(aux) + 1, aux);

	aux = strtok(NULL, sep);
	c1.autor = malloc(strlen(aux) + 1);
	strcpy_s(c1.autor, strlen(aux) + 1, aux);

	c1.categorie = *strtok(NULL, sep);
	return c1;
}

void afisareCarte(Carte carte) {
	printf("Id: %d\n", carte.id);
	printf("Nr. pagini: %d\n", carte.nrPagini);
	printf("Pret: %.2f\n", carte.pret);
	printf("Titlu: %s\n", carte.titlu);
	printf("Autor: %s\n", carte.autor);
	printf("Categorie: %c\n\n", carte.categorie);
}

Carte copiazaCarte(Carte c) {
	Carte copie;
	copie.id = c.id;
	copie.nrPagini = c.nrPagini;
	copie.pret = c.pret;

	copie.titlu = (char*)malloc(strlen(c.titlu) + 1);
	strcpy_s(copie.titlu, strlen(c.titlu) + 1, c.titlu);

	copie.autor = (char*)malloc(strlen(c.autor) + 1);
	strcpy_s(copie.autor, strlen(c.autor) + 1, c.autor);

	copie.categorie = c.categorie;

	return copie;
}

Nod* creareNod(Carte carteNoua) {
	Nod* nod = (Nod*)malloc(sizeof(Nod));
	nod->info = copiazaCarte(carteNoua);
	nod->stanga = NULL;
	nod->dreapta = NULL;
	return nod;
}

Nod* adaugaCarteInArbore(Nod* radacina, Carte carteNoua) {


	if (radacina == NULL) {
		return creareNod(carteNoua);
	}

	if (carteNoua.id < radacina->info.id) {
		radacina->stanga = adaugaCarteInArbore(radacina->stanga, carteNoua);
	}
	else if (carteNoua.id > radacina->info.id) {
		radacina->dreapta = adaugaCarteInArbore(radacina->dreapta, carteNoua);
	}

	return radacina;
}

Nod* citireArboreDeCartiDinFisier(const char* numeFisier) {

	FILE* f = fopen(numeFisier, "r");
	if (f == NULL) {
		printf("Fisierul nu a putut fi deschis.\n");
		return NULL;
	}

	Nod* radacina = NULL;

	while (!feof(f)) {
		Carte c = citireCarteDinFisier(f);

		if (c.id != -1) {
			radacina = adaugaCarteInArbore(radacina, c);

			free(c.titlu);
			free(c.autor);
		}
	}

	fclose(f);
	return radacina;
}


void afisareInordine(Nod* radacina) {
	if (radacina != NULL) {
		afisareInordine(radacina->stanga);
		afisareCarte(radacina->info);
		afisareInordine(radacina->dreapta);
	}
}


void afisarePreordine(Nod* radacina) {
	if (radacina != NULL) {
		afisareCarte(radacina->info);
		afisarePreordine(radacina->stanga);
		afisarePreordine(radacina->dreapta);
	}
}

void afisarePostordine(Nod* radacina) {
	if (radacina != NULL) {
		afisarePostordine(radacina->stanga);
		afisarePostordine(radacina->dreapta);
		afisareCarte(radacina->info);
	}
}

void afisareCartiDinArbore(Nod* radacina) {

	printf("----- Afisare INORDINE -----\n");
	afisareInordine(radacina);

	printf("----- Afisare PREORDINE -----\n");
	afisarePreordine(radacina);

	printf("----- Afisare POSTORDINE -----\n");
	afisarePostordine(radacina);
}

void dezalocareArboreDeCarti(Nod** radacina) {


	if (*radacina != NULL) {
		dezalocareArboreDeCarti(&((*radacina)->stanga));
		dezalocareArboreDeCarti(&((*radacina)->dreapta));

		free((*radacina)->info.titlu);
		free((*radacina)->info.autor);
		free(*radacina);
		*radacina = NULL;
	}
}

Carte getCarteByID(Nod* radacina, int id) {
	Carte c;
	c.id = -1;
	c.nrPagini = 0;
	c.pret = 0;
	c.titlu = NULL;
	c.autor = NULL;
	c.categorie = '-';

	if (radacina == NULL) {
		return c;
	}

	if (id == radacina->info.id) {
		return copiazaCarte(radacina->info);
	}
	else if (id < radacina->info.id) {
		return getCarteByID(radacina->stanga, id);
	}
	else {
		return getCarteByID(radacina->dreapta, id);
	}
}

int determinaNumarNoduri(Nod* radacina) {


	if (radacina == NULL) {
		return 0;
	}

	return 1 + determinaNumarNoduri(radacina->stanga) + determinaNumarNoduri(radacina->dreapta);
}

int calculeazaInaltimeArbore(Nod* radacina) {


	if (radacina == NULL) {
		return 0;
	}

	int inaltimeStanga = calculeazaInaltimeArbore(radacina->stanga);
	int inaltimeDreapta = calculeazaInaltimeArbore(radacina->dreapta);

	if (inaltimeStanga > inaltimeDreapta) {
		return 1 + inaltimeStanga;
	}
	else {
		return 1 + inaltimeDreapta;
	}
}

float calculeazaPretTotal(Nod* radacina) {


	if (radacina == NULL) {
		return 0;
	}

	return radacina->info.pret + calculeazaPretTotal(radacina->stanga) + calculeazaPretTotal(radacina->dreapta);
}

float calculeazaPretulCartilorUnuiAutor(Nod* radacina, const char* autor) {


	if (radacina == NULL) {
		return 0;
	}

	float suma = 0;

	if (strcmp(radacina->info.autor, autor) == 0) {
		suma = radacina->info.pret;
	}

	return suma
		+ calculeazaPretulCartilorUnuiAutor(radacina->stanga, autor)
		+ calculeazaPretulCartilorUnuiAutor(radacina->dreapta, autor);
}

int main() {

	Nod* arbore = citireArboreDeCartiDinFisier("carti.txt");

	printf("----AFISARE ARBORE -----\n");
	afisareCartiDinArbore(arbore);

	printf("Numar noduri: %d\n", determinaNumarNoduri(arbore));
	printf("Inaltime arbore: %d\n", calculeazaInaltimeArbore(arbore));
	printf("Pret total: %.2f\n", calculeazaPretTotal(arbore));

	printf("Pret total pentru autorul Popescu: %.2f\n",
		calculeazaPretulCartilorUnuiAutor(arbore, "Popescu"));

	Carte c = getCarteByID(arbore, 2);
	if (c.id != -1) {
		printf("\nCartea gasita dupa ID:\n");
		afisareCarte(c);
		free(c.titlu);
		free(c.autor);
	}
	else {
		printf("\nNu exista carte cu acest ID.\n");
	}

	dezalocareArboreDeCarti(&arbore);

	return 0;
}