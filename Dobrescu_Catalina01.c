#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
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
void afisare(struct Document d)
{
	if (d.titlu != NULL) {
		printf("%d.Document %s are %d pagini, dimensiunea lor e %.2f \n", d.cod, d.titlu, d.nrPagini, d.dimensiuniPagini);
	}
	else {
		printf("%d.Document are %d pagini, dimensiunea lor e %.2f \n", d.cod, d.nrPagini, d.dimensiuniPagini);
	}
}
void modifcaNrPagini(struct Document*d, int NouNrPagini)
{
	if (NouNrPagini > 0) {
		d->nrPagini = NouNrPagini;
	}

}
void dezalocare(struct Document* d)
{
	if (d->titlu != NULL)
	{
		free(d->titlu);
		d->titlu = NULL;
	}
}



int main() {
	struct Document d;
	d = initializare(1, "Ion", 200, 20);
	afisare(d);
	modifcaNrPagini(&d, 205);
	afisare(d);
	dezalocare(&d);
	afisare(d);

	return 0;
}