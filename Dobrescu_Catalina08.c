//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//struct StructuraCarte {
//	int id;
//	int nrPagini;
//	float pret;
//	char* titlu;
//	char* autor;
//	unsigned char categorie;
//};
//typedef struct StructuraCarte Carte;
//
//struct Heap {
//	int lungime;
//	Carte* vector;
//	int nrCarti;
//};
//typedef struct Heap Heap;
//
//Carte citireCarteDinFisier(FILE* file) {
//	char buffer[150];
//	char sep[3] = ",\n";
//	fgets(buffer, 150, file);
//
//	char* aux;
//	Carte c;
//
//	aux = strtok(buffer, sep);
//	c.id = atoi(aux);
//
//	c.nrPagini = atoi(strtok(NULL, sep));
//	c.pret = (float)atof(strtok(NULL, sep));
//
//	aux = strtok(NULL, sep);
//	c.titlu = (char*)malloc(strlen(aux) + 1);
//	strcpy(c.titlu, aux);
//
//	aux = strtok(NULL, sep);
//	c.autor = (char*)malloc(strlen(aux) + 1);
//	strcpy(c.autor, aux);
//
//	c.categorie = *strtok(NULL, sep);
//
//	return c;
//}
//
//void afisareCarte(Carte carte) {
//	printf("Id: %d\n", carte.id);
//	printf("Nr. pagini: %d\n", carte.nrPagini);
//	printf("Pret: %.2f\n", carte.pret);
//	printf("Titlu: %s\n", carte.titlu);
//	printf("Autor: %s\n", carte.autor);
//	printf("Categorie: %c\n\n", carte.categorie);
//}
//
//Heap initializareHeap(int lungime) {
//	Heap heap;
//	heap.lungime = lungime;
//	heap.nrCarti = 0;
//	heap.vector = (Carte*)malloc(sizeof(Carte) * lungime);
//	return heap;
//}
//
//void filtreazaHeap(Heap heap, int pozitieNod) {
//	int pozFiuSt = 2 * pozitieNod + 1;
//	int pozFiuDr = 2 * pozitieNod + 2;
//	int pozMax = pozitieNod;
//
//	if (pozFiuSt < heap.nrCarti && heap.vector[pozMax].pret < heap.vector[pozFiuSt].pret) {
//		pozMax = pozFiuSt;
//	}
//
//	if (pozFiuDr < heap.nrCarti && heap.vector[pozMax].pret < heap.vector[pozFiuDr].pret) {
//		pozMax = pozFiuDr;
//	}
//
//	if (pozMax != pozitieNod) {
//		Carte aux = heap.vector[pozMax];
//		heap.vector[pozMax] = heap.vector[pozitieNod];
//		heap.vector[pozitieNod] = aux;
//
//		if (pozMax <= (heap.nrCarti - 2) / 2) {
//			filtreazaHeap(heap, pozMax);
//		}
//	}
//}
//
//Heap citireHeapDeCartiDinFisier(const char* numeFisier) {
//	FILE* file = fopen(numeFisier, "r");
//	Heap heap = initializareHeap(10);
//
//	while (!feof(file)) {
//		heap.vector[heap.nrCarti++] = citireCarteDinFisier(file);
//	}
//
//	fclose(file);
//
//	for (int i = (heap.nrCarti - 2) / 2; i >= 0; i--) {
//		filtreazaHeap(heap, i);
//	}
//
//	return heap;
//}
//
//void afisareHeap(Heap heap) {
//	for (int i = 0; i < heap.nrCarti; i++) {
//		afisareCarte(heap.vector[i]);
//	}
//}
//
//void afiseazaHeapAscuns(Heap heap) {
//	for (int i = heap.nrCarti; i < heap.lungime; i++) {
//		afisareCarte(heap.vector[i]);
//	}
//}
//
//Carte extrageCarte(Heap* heap) {
//	if (heap->nrCarti > 0) {
//		Carte aux = heap->vector[0];
//		heap->vector[0] = heap->vector[heap->nrCarti - 1];
//		heap->vector[heap->nrCarti - 1] = aux;
//		heap->nrCarti--;
//
//		for (int i = (heap->nrCarti - 2) / 2; i >= 0; i--) {
//			filtreazaHeap(*heap, i);
//		}
//
//		return aux;
//	}
//}
//
//void dezalocareHeap(Heap* heap) {
//	for (int i = 0; i < heap->lungime; i++) {
//		free(heap->vector[i].titlu);
//		free(heap->vector[i].autor);
//	}
//
//	free(heap->vector);
//	heap->vector = NULL;
//	heap->lungime = 0;
//	heap->nrCarti = 0;
//}
//
//int main() {
//	Heap heap = citireHeapDeCartiDinFisier("carti.txt");
//
//	printf("Cartile din heap sunt:\n");
//	afisareHeap(heap);
//
//	printf("Carti extrase:\n");
//	afisareCarte(extrageCarte(&heap));
//	afisareCarte(extrageCarte(&heap));
//	afisareCarte(extrageCarte(&heap));
//	afisareCarte(extrageCarte(&heap));
//	afisareCarte(extrageCarte(&heap));
//	afisareCarte(extrageCarte(&heap));
//	afisareCarte(extrageCarte(&heap));
//	afisareCarte(extrageCarte(&heap));
//	afisareCarte(extrageCarte(&heap));
//	afisareCarte(extrageCarte(&heap));
//
//	printf("Heap-ul ascuns:\n");
//	afiseazaHeapAscuns(heap);
//
//	dezalocareHeap(&heap);
//	return 0;
//}