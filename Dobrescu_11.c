#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct StructuraDocument {
	int id;
	int nrPagini;
	float pret;
	char* titlu;
	char* autor;
	unsigned char categorie;
};

typedef struct StructuraDocument Document;

struct Nod {
	Document info;
	struct Nod* st;
	struct Nod* dr;
};

typedef struct Nod Nod;

int calculeazaInaltimeArbore(Nod* rad);
int maxim(int a, int b);

Document initDocument(int id, int nrPagini, float pret, const char* titlu,
	const char* autor, unsigned char categorie) {

	Document d;
	d.id = id;
	d.nrPagini = nrPagini;
	d.pret = pret;
	d.categorie = categorie;

	d.titlu = (char*)malloc(strlen(titlu) + 1);
	strcpy(d.titlu, titlu);

	d.autor = (char*)malloc(strlen(autor) + 1);
	strcpy(d.autor, autor);

	return d;
}

void afisareDocument(Document d) {
	printf("Id: %d\n", d.id);
	printf("Nr. pagini: %d\n", d.nrPagini);
	printf("Pret: %.2f\n", d.pret);
	printf("Titlu: %s\n", d.titlu);
	printf("Autor: %s\n", d.autor);
	printf("Categorie: %c\n\n", d.categorie);
}

int calculDiferentaInaltimi(Nod* rad) {
	if (rad) {
		return calculeazaInaltimeArbore(rad->st) - calculeazaInaltimeArbore(rad->dr);
	}
	return 0;
}

void rotireLaStanga(Nod** rad) {
	Nod* aux = (*rad)->dr;
	(*rad)->dr = aux->st;
	aux->st = (*rad);
	(*rad) = aux;
}

void rotireLaDreapta(Nod** rad) {
	Nod* aux = (*rad)->st;
	(*rad)->st = aux->dr;
	aux->dr = (*rad);
	(*rad) = aux;
}

void adaugaDocumentInArbore(Nod** rad, Document documentNou) {
	if (*rad == NULL) {
		Nod* nod = (Nod*)malloc(sizeof(Nod));
		nod->info = documentNou;
		nod->st = NULL;
		nod->dr = NULL;
		*rad = nod;
	}
	else {
		if ((*rad)->info.id > documentNou.id) {
			adaugaDocumentInArbore(&((*rad)->st), documentNou);
		}
		else if ((*rad)->info.id < documentNou.id) {
			adaugaDocumentInArbore(&((*rad)->dr), documentNou);
		}
		else {
			free(documentNou.titlu);
			free(documentNou.autor);
			return;
		}
	}

	int diferentaInaltimi = calculDiferentaInaltimi(*rad);

	if (diferentaInaltimi == 2) {
		if (calculDiferentaInaltimi((*rad)->st) == -1) {
			rotireLaStanga(&(*rad)->st);
		}
		rotireLaDreapta(rad);
	}

	if (diferentaInaltimi == -2) {
		if (calculDiferentaInaltimi((*rad)->dr) == 1) {
			rotireLaDreapta(&(*rad)->dr);
		}
		rotireLaStanga(rad);
	}
}

void afisareInordine(Nod* rad) {
	if (rad) {
		afisareInordine(rad->st);
		afisareDocument(rad->info);
		afisareInordine(rad->dr);
	}
}

void afisarePreordine(Nod* rad) {
	if (rad) {
		afisareDocument(rad->info);
		afisarePreordine(rad->st);
		afisarePreordine(rad->dr);
	}
}

Document getDocumentByID(Nod* rad, int id) {
	Document d;
	d.id = -1;
	d.nrPagini = 0;
	d.pret = 0;
	d.titlu = NULL;
	d.autor = NULL;
	d.categorie = '-';

	if (rad) {
		if (rad->info.id == id) {
			d.id = rad->info.id;
			d.nrPagini = rad->info.nrPagini;
			d.pret = rad->info.pret;
			d.categorie = rad->info.categorie;

			d.titlu = (char*)malloc(strlen(rad->info.titlu) + 1);
			strcpy(d.titlu, rad->info.titlu);

			d.autor = (char*)malloc(strlen(rad->info.autor) + 1);
			strcpy(d.autor, rad->info.autor);

			return d;
		}

		if (id < rad->info.id) {
			return getDocumentByID(rad->st, id);
		}
		else {
			return getDocumentByID(rad->dr, id);
		}
	}

	return d;
}

int determinaNumarNoduri(Nod* rad) {
	if (rad) {
		return determinaNumarNoduri(rad->st) +
			determinaNumarNoduri(rad->dr) + 1;
	}
	return 0;
}

int maxim(int a, int b) {
	return a > b ? a : b;
}

int calculeazaInaltimeArbore(Nod* rad) {
	if (rad) {
		return maxim(calculeazaInaltimeArbore(rad->st),
			calculeazaInaltimeArbore(rad->dr)) + 1;
	}
	return 0;
}

float calculeazaPretTotal(Nod* rad) {
	if (rad) {
		return rad->info.pret +
			calculeazaPretTotal(rad->st) +
			calculeazaPretTotal(rad->dr);
	}
	return 0;
}

float calculeazaPretDocumenteAutor(Nod* rad, const char* autor) {
	if (rad) {
		float suma = calculeazaPretDocumenteAutor(rad->st, autor) +
			calculeazaPretDocumenteAutor(rad->dr, autor);

		if (strcmp(rad->info.autor, autor) == 0) {
			suma += rad->info.pret;
		}

		return suma;
	}
	return 0;
}

void dezalocareArbore(Nod** rad) {
	if (*rad) {
		dezalocareArbore(&(*rad)->st);
		dezalocareArbore(&(*rad)->dr);

		free((*rad)->info.titlu);
		free((*rad)->info.autor);
		free(*rad);

		*rad = NULL;
	}
}

void citireDocumenteDinFisier(const char* numeFisier, Nod** rad) {
	FILE* f = fopen(numeFisier, "r");

	if (f == NULL) {
		printf("Fisierul nu s-a putut deschide.\n");
		return;
	}

	char buffer[256];

	while (fgets(buffer, sizeof(buffer), f)) {
		int id;
		int nrPagini;
		float pret;
		char titlu[100];
		char autor[100];
		char categorie;

		char* token = strtok(buffer, ",");
		id = atoi(token);

		token = strtok(NULL, ",");
		nrPagini = atoi(token);

		token = strtok(NULL, ",");
		pret = (float)atof(token);

		token = strtok(NULL, ",");
		strcpy(titlu, token);

		token = strtok(NULL, ",");
		strcpy(autor, token);

		token = strtok(NULL, ",\n");
		categorie = token[0];

		Document d = initDocument(id, nrPagini, pret, titlu, autor, categorie);
		adaugaDocumentInArbore(rad, d);
	}

	fclose(f);
}

int main() {
	Nod* rad = NULL;

	citireDocumenteDinFisier("documente.txt", &rad);

	printf("Afisare preordine:\n");
	afisarePreordine(rad);

	printf("Document cautat:\n");
	Document d = getDocumentByID(rad, 3);

	if (d.id != -1) {
		afisareDocument(d);
		free(d.titlu);
		free(d.autor);
	}
	else {
		printf("Documentul nu a fost gasit.\n");
	}

	printf("Numar noduri: %d\n", determinaNumarNoduri(rad));
	printf("Inaltime arbore: %d\n", calculeazaInaltimeArbore(rad));
	printf("Pret total: %.2f\n", calculeazaPretTotal(rad));
	printf("Suma preturilor documentelor unui autor: %.2f\n",
		calculeazaPretDocumenteAutor(rad, "Tufan Daniel"));

	dezalocareArbore(&rad);

	return 0;
}