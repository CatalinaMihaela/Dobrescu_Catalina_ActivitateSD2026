#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct StructuraProgramare {
	int id;
	int ora;
	float costEstimativ;
	char* numeClient;
	char* tipProblema;
	unsigned char codUrgenta;
};
typedef struct StructuraProgramare Programare;

struct Heap {
	int lungime;
	Programare* programari;
	int nrElemente;
};
typedef struct Heap Heap;

Programare citireProgramareDinFisier(FILE* file) {
	char buffer[100];
	char sep[3] = ",\n";

	fgets(buffer, 100, file);

	char* aux;
	Programare p;

	aux = strtok(buffer, sep);
	p.id = atoi(aux);

	p.ora = atoi(strtok(NULL, sep));
	p.costEstimativ = atof(strtok(NULL, sep));

	aux = strtok(NULL, sep);
	p.numeClient = malloc(strlen(aux) + 1);
	strcpy(p.numeClient, aux);

	aux = strtok(NULL, sep);
	p.tipProblema = malloc(strlen(aux) + 1);
	strcpy(p.tipProblema, aux);

	p.codUrgenta = *strtok(NULL, sep);

	return p;
}

void afisareProgramare(Programare p) {
	printf("Id: %d\n", p.id);
	printf("Ora: %d\n", p.ora);
	printf("Cost estimativ: %.2f\n", p.costEstimativ);
	printf("Nume client: %s\n", p.numeClient);
	printf("Tip problema: %s\n", p.tipProblema);
	printf("Cod urgenta: %c\n\n", p.codUrgenta);
}

Heap initializareHeap(int lungime) {
	Heap heap;
	heap.lungime = lungime;
	heap.programari = malloc(sizeof(Programare) * lungime);
	heap.nrElemente = 0;
	return heap;
}

void filtreazaHeap(Heap heap, int pozitieNod) {
	int pozSt = 2 * pozitieNod + 1;
	int pozDr = 2 * pozitieNod + 2;
	int pozMin = pozitieNod;

	if (pozSt < heap.nrElemente &&
		heap.programari[pozMin].ora > heap.programari[pozSt].ora) {
		pozMin = pozSt;
	}

	if (pozDr < heap.nrElemente &&
		heap.programari[pozMin].ora > heap.programari[pozDr].ora) {
		pozMin = pozDr;
	}

	if (pozMin != pozitieNod) {
		Programare aux = heap.programari[pozMin];
		heap.programari[pozMin] = heap.programari[pozitieNod];
		heap.programari[pozitieNod] = aux;

		filtreazaHeap(heap, pozMin);
	}
}

Heap citireHeapProgramariDinFisier(const char* numeFisier) {
	Heap heap = initializareHeap(10);

	FILE* f = fopen(numeFisier, "r");

	if (f) {
		while (!feof(f)) {
			heap.programari[heap.nrElemente++] =
				citireProgramareDinFisier(f);
		}

		fclose(f);
	}

	for (int i = (heap.nrElemente - 2) / 2; i >= 0; i--) {
		filtreazaHeap(heap, i);
	}

	return heap;
}

void afisareHeap(Heap heap) {
	for (int i = 0; i < heap.nrElemente; i++) {
		afisareProgramare(heap.programari[i]);
	}
}

void afisareHeapAscuns(Heap heap) {
	for (int i = heap.nrElemente; i < heap.lungime; i++) {
		afisareProgramare(heap.programari[i]);
	}
}

Programare extrageProgramare(Heap* heap) {
	Programare p;

	p.id = -1;
	p.ora = -1;
	p.costEstimativ = 0;
	p.numeClient = NULL;
	p.tipProblema = NULL;
	p.codUrgenta = '-';

	if (heap->nrElemente > 0) {
		p = heap->programari[0];

		heap->programari[0] =
			heap->programari[heap->nrElemente - 1];

		heap->programari[heap->nrElemente - 1] = p;

		heap->nrElemente--;

		filtreazaHeap(*heap, 0);
	}

	return p;
}

char* getNextProblema(Heap heap) {
	for (int i = 0; i < 6; i++) {
		extrageProgramare(&heap);
	}

	if (heap.nrElemente > 0) {
		return heap.programari[0].tipProblema;
	}

	return "";
}

void dezalocareHeap(Heap* heap) {
	for (int i = 0; i < heap->lungime; i++) {
		free(heap->programari[i].numeClient);
		free(heap->programari[i].tipProblema);
	}

	free(heap->programari);

	heap->programari = NULL;
	heap->lungime = 0;
	heap->nrElemente = 0;
}

int main() {

	Heap heap =
		citireHeapProgramariDinFisier("programari.txt");

	printf("Heap initial:\n");
	afisareHeap(heap);

	printf("Urmatoarea problema: %s\n\n",
		getNextProblema(heap));

	printf("Extrageri:\n");

	afisareProgramare(extrageProgramare(&heap));
	afisareProgramare(extrageProgramare(&heap));
	afisareProgramare(extrageProgramare(&heap));

	printf("Heap ramas:\n");
	afisareHeap(heap);

	printf("Elemente ascunse:\n");
	afisareHeapAscuns(heap);

	dezalocareHeap(&heap);

	return 0;
}