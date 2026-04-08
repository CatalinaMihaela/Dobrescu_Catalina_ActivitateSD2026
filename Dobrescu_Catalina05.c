//#define _CRT_SECURE_NO_WARNINGS
//#include<stdio.h>
//#include<stdlib.h>
//#include<string.h>
//
//struct Carte {
//	int id;
//	char* titlu;
//	float pret;
//};
//typedef struct Carte Carte;
//
//struct Nod {
//	Carte info;
//	struct Nod* next;
//	struct Nod* prev;
//};
//typedef struct Nod Nod;
//
//Carte citireCarteDinFisier(FILE* f) {
//	char buffer[100];
//	char sep[] = ",\n";
//	Carte c;
//
//	fgets(buffer, 100, f);
//
//	char* aux = strtok(buffer, sep);
//	c.id = atoi(aux);
//
//	aux = strtok(NULL, sep);
//	c.titlu = (char*)malloc(strlen(aux) + 1);
//	strcpy(c.titlu, aux);
//
//	aux = strtok(NULL, sep);
//	c.pret = (float)atof(aux);
//
//	return c;
//}
//
//
//void afisareCarte(Carte c) {
//	printf("ID: %d\n", c.id);
//	printf("Titlu: %s\n", c.titlu);
//	printf("Pret: %.2f\n\n", c.pret);
//}
//
//// inserare la final (lista dubla)
//void inserareFinal(Nod** cap, Nod** coada, Carte c) {
//
//	Nod* nou = (Nod*)malloc(sizeof(Nod));
//	nou->info = c;
//	nou->next = NULL;
//	nou->prev = NULL;
//
//	if (*cap == NULL) {
//		*cap = *coada = nou;
//	}
//	else {
//		nou->prev = *coada;
//		(*coada)->next = nou;
//		*coada = nou;
//	}
//}
//
//// traversare de la inceput
//void traversareInainte(Nod* cap) {
//	while (cap != NULL) {
//		afisareCarte(cap->info);
//		cap = cap->next;
//	}
//}
//
//
//void traversareInapoi(Nod* coada) {
//	while (coada != NULL) {
//		afisareCarte(coada->info);
//		coada = coada->prev;
//	}
//}
//
//
//char* cartePretMinim(Nod* cap) {
//
//	if (cap == NULL) return NULL;
//
//	Nod* min = cap;
//
//	while (cap != NULL) {
//		if (cap->info.pret < min->info.pret) {
//			min = cap;
//		}
//		cap = cap->next;
//	}
//
//	char* titlu = (char*)malloc(strlen(min->info.titlu) + 1);
//	strcpy(titlu, min->info.titlu);
//
//	return titlu;
//}
//
//
//Carte cautaCarte(Nod* cap, const char* titlu) {
//
//	Carte rez;
//	rez.titlu = NULL;
//
//	while (cap != NULL) {
//		if (strcmp(cap->info.titlu, titlu) == 0) {
//
//			rez.id = cap->info.id;
//			rez.pret = cap->info.pret;
//
//			rez.titlu = (char*)malloc(strlen(cap->info.titlu) + 1);
//			strcpy(rez.titlu, cap->info.titlu);
//
//			return rez;
//		}
//		cap = cap->next;
//	}
//
//	return rez;
//}
//
//
//void dezalocare(Nod** cap) {
//
//	while (*cap != NULL) {
//		Nod* temp = *cap;
//		*cap = (*cap)->next;
//
//		free(temp->info.titlu);
//		free(temp);
//	}
//}
//
//int main() {
//
//	Nod* cap = NULL;
//	Nod* coada = NULL;
//
//	FILE* f = fopen("carte.txt", "r");
//
//	if (f != NULL) {
//
//		int nr;
//		fscanf(f, "%d", &nr);
//		fgetc(f);
//
//		for (int i = 0; i < nr; i++) {
//			Carte c = citireCarteDinFisier(f);
//			inserareFinal(&cap, &coada, c);
//		}
//
//		fclose(f);
//	}
//
//	printf("Lista inainte:\n\n");
//	traversareInainte(cap);
//
//	printf("Lista inapoi:\n\n");
//	traversareInapoi(coada);
//
//	printf("Carte cu pret minim:\n");
//	char* titlu = cartePretMinim(cap);
//	if (titlu) {
//		printf("%s\n", titlu);
//		free(titlu);
//	}
//
//	printf("\nCautare carte:\n");
//	Carte c = cautaCarte(cap, "1984");
//
//	if (c.titlu != NULL) {
//		afisareCarte(c);
//		free(c.titlu);
//	}
//	else {
//		printf("Nu a fost gasita\n");
//	}
//
//	dezalocare(&cap);
//
//	return 0;
//}