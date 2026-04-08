//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include<malloc.h>
//
//struct Restaurant {
//	char* numeRestaurant;
//	int nrMese;
//	float rating;
//};
//typedef struct Restaurant Restaurant;
//
//struct Nod {
//	struct Restaurant info;
//	struct Nod* next;
//};
//
//typedef struct Nod Nod;
//
//
//Restaurant citireRestaurantDinFisier(FILE* f) {
//
//	char buffer[100];
//	char sep[] = ",\n";
//	Restaurant r;
//
//	fgets(buffer, 100, f);
//
//	char* aux = strtok(buffer, sep);
//	r.numeRestaurant = (char*)malloc(strlen(aux) + 1);
//	strcpy(r.numeRestaurant, aux);
//
//	aux = strtok(NULL, sep);
//	r.nrMese = atoi(aux);
//
//	aux = strtok(NULL, sep);
//	r.rating = (float)atof(aux);
//
//	return r;
//}
//
//
//void afisareRestaurant(Restaurant r) {
//
//	printf("Nume restaurant: %s\n", r.numeRestaurant);
//	printf("Numar mese: %d\n", r.nrMese);
//	printf("Rating: %.2f\n\n", r.rating);
//
//}
//
//
//void inserareFinal(Nod** cap, Restaurant r) {
//
//	Nod* nou = (Nod*)malloc(sizeof(Nod));
//
//	nou->info = r;
//	nou->next = NULL;
//
//	if (*cap == NULL) {
//		*cap = nou;
//	}
//	else {
//
//		Nod* temp = *cap;
//
//		while (temp->next != NULL) {
//			temp = temp->next;
//		}
//
//		temp->next = nou;
//	}
//}
//
//
//void traversareLista(Nod* cap) {
//
//	while (cap != NULL) {
//
//		afisareRestaurant(cap->info);
//
//		cap = cap->next;
//	}
//}
//
//
//char* restaurantMinMese(Nod* cap) {
//
//	if (cap == NULL)
//		return NULL;
//
//	Nod* minim = cap;
//
//	while (cap != NULL) {
//
//		if (cap->info.nrMese < minim->info.nrMese) {
//			minim = cap;
//		}
//
//		cap = cap->next;
//	}
//
//	char* nume = (char*)malloc(strlen(minim->info.numeRestaurant) + 1);
//	strcpy(nume, minim->info.numeRestaurant);
//
//	return nume;
//}
//
//
//Restaurant cautaRestaurant(Nod* cap, const char* nume) {
//
//	Restaurant rezultat;
//	rezultat.numeRestaurant = NULL;
//	rezultat.nrMese = 0;
//	rezultat.rating = 0;
//
//	while (cap != NULL) {
//
//		if (strcmp(cap->info.numeRestaurant, nume) == 0) {
//
//			rezultat.numeRestaurant = (char*)malloc(strlen(cap->info.numeRestaurant) + 1);
//			strcpy(rezultat.numeRestaurant, cap->info.numeRestaurant);
//
//			rezultat.nrMese = cap->info.nrMese;
//			rezultat.rating = cap->info.rating;
//
//			return rezultat;
//		}
//
//		cap = cap->next;
//	}
//
//	return rezultat;
//}
//
//
//void dezalocareLista(Nod** cap) {
//
//	while (*cap != NULL) {
//
//		Nod* temp = *cap;
//
//		*cap = (*cap)->next;
//
//		free(temp->info.numeRestaurant);
//		free(temp);
//	}
//}
//
//
//int main() {
//
//	Nod* cap = NULL;
//
//	FILE* f = fopen("restaurante.txt", "r");
//
//	if (f != NULL) {
//
//		int nr;
//		fscanf(f, "%d", &nr);
//		fgetc(f);
//
//		for (int i = 0; i < nr; i++) {
//
//			Restaurant r = citireRestaurantDinFisier(f);
//
//			inserareFinal(&cap, r);
//		}
//
//		fclose(f);
//	}
//
//
//	printf("Lista restaurantelor:\n\n");
//
//	traversareLista(cap);
//
//
//	printf("\nRestaurantul cu cele mai putine mese:\n");
//
//	char* nume = restaurantMinMese(cap);
//
//	if (nume != NULL) {
//		printf("%s\n", nume);
//		free(nume);
//	}
//
//
//	printf("\nCautare restaurant:\n");
//
//	Restaurant r = cautaRestaurant(cap, "Trattoria");
//
//	if (r.numeRestaurant != NULL) {
//		afisareRestaurant(r);
//		free(r.numeRestaurant);
//	}
//	else {
//		printf("Restaurantul nu a fost gasit.\n");
//	}
//
//
//	dezalocareLista(&cap);
//
//	return 0;
//}