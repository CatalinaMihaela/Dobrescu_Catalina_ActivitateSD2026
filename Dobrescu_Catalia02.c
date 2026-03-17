#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include<string.h>

struct Document {
	int cod;
	char* titlu;
	int nrPagini;
	float dimensiuniPagini;

};
struct Document initializare(int cod, const char* titlu, int nrPagini, float dimensiuniPagini)
{
	struct Document d;
	d.cod = cod;
	d.titlu = (char*)malloc(sizeof(char) * (strlen(titlu) + 1));
	strcpy_s(d.titlu, strlen(titlu) + 1, titlu);
	d.nrPagini = nrPagini;
	d.dimensiuniPagini = dimensiuniPagini;
	return d;

}
void afisare(struct Document d) {
	if (d.titlu != NULL)
	{
		printf("%d.Document %s are %d pagini, dimensiunea lor e %.2f \n", d.cod, d.titlu, d.nrPagini, d.dimensiuniPagini);
	}
	else {
				printf("%d.Document are %d pagini, dimensiunea lor e %.2f \n", d.cod, d.nrPagini, d.dimensiuniPagini);
		}
	

}
void afisareVector(struct Document*vector, int nrElemente) {
	for (int i = 0; i < nrElemente; i++) {
		afisare (vector[i]);
	}

}
struct Document* copiazaPrimeleNElemente(struct Document* vector, int nrElemente, int nrElementeCopiate) {
	struct Document* vectorNou = NULL;
	vectorNou = (struct Document*)malloc(sizeof(struct Document) * nrElementeCopiate);
	for (int i = 0; i < nrElementeCopiate; i++) {
		vectorNou[i] = vector[i];
		vectorNou[i].titlu = (char*)malloc(strlen(vector[i].titlu) + 1);
		strcpy_s(vectorNou[i].titlu, strlen(vector[i].titlu) + 1, vector[i].titlu);
	}
	return vectorNou;

}
void dezalocare(struct Document** vector, int* nrElemente) {
	for (int i = 0; i < (*nrElemente); i++) {
		if((*vector)[i].titlu != NULL){
			free((*vector)[i].titlu);
		}
	}
	free(*vector);
	*vector = NULL;
	*nrElemente=0;

}
void copiazaDocumentedimensiuneMare(struct Document*vector, char nrElemente, float dimensiuniPaginiMin, struct Document**vectorNou, int*dimensiune) {
	*dimensiune = 0;
	for (int i = 0; i < nrElemente; i++) {
		if (vector[i].dimensiuniPagini >= dimensiuniPaginiMin) {
			(*dimensiune)++;
		}
	}
	if ((*vectorNou) != NULL) {
		free(*vectorNou);
	}
	*vectorNou = (struct Document*)malloc(sizeof(struct Document) * (*dimensiune));
	int k = 0;
	for (int i = 0; i < nrElemente;i++) {
		if (vector[i].dimensiuniPagini >= dimensiuniPaginiMin) {
			(*vectorNou)[k] = vector[i];
			(*vectorNou)[k].titlu = (char*)malloc(strlen(vector[i].titlu) + 1);
			strcpy_s((*vectorNou)[k].titlu, strlen(vector[i].titlu) + 1, vector[i].titlu);
			k++;
		}

	}

}
struct Document getPrimulTitlu(struct Document* vector, int nrElemente, const char* titlu) {
	struct Document d;
	d.titlu = NULL;
	for (int i = 0;i < nrElemente;i++) {
		if (strcmp(vector[i].titlu,titlu)==0) {
			d = vector[i];
			d.titlu = (char*)malloc(strlen(vector[i].titlu) + 1);
			strcpy_s(d.titlu, strlen(vector[i].titlu) + 1, vector[i].titlu);
			return d;


		}
	}
	
	return d;
}



int main() {
	struct Document * documente=NULL;
	int nrDocumente = 3;
	documente = (struct Document*)malloc(sizeof(struct Document) * nrDocumente);
	documente[0] = initializare(1, "Doc2", 3, 1.0);
	documente[1] = initializare(2, "Doc3", 4, 2.0);
	documente[2] = initializare(3, "Doc4", 5, 3.0);
	afisareVector(documente, nrDocumente);

	struct Document* PrimeleDocumente = NULL;
	int nrPRimeleDocumente = 2;
	PrimeleDocumente = copiazaPrimeleNElemente(documente, nrDocumente, nrPRimeleDocumente);
	printf("\n\nPrimele documente:\n");
	afisareVector(PrimeleDocumente, nrPRimeleDocumente);
	
	dezalocare(&PrimeleDocumente, &nrPRimeleDocumente);
	afisareVector(PrimeleDocumente, nrPRimeleDocumente);

	//copiaza documente dimensiune mare
	struct Document* dimensiunemare = NULL;
	int nrDocumenteDimensiuneMare = 0;
	copiazaDocumentedimensiuneMare(documente, nrDocumente, 2.0, &dimensiunemare, & nrDocumenteDimensiuneMare);
	printf("\nDocumente dimensiune mare:\n");
	afisareVector(dimensiunemare, nrDocumenteDimensiuneMare);
	dezalocare(&dimensiunemare, &nrDocumenteDimensiuneMare);
	struct Document document = getPrimulTitlu(documente, nrDocumente, "Doc2");
	printf("\nTitlu:\n");
	afisare(document);
	if (document.titlu != NULL) {
		free ( document.titlu);
		document.titlu = NULL;
	}
	dezalocare(&documente, &nrDocumente);

	return 0;

}