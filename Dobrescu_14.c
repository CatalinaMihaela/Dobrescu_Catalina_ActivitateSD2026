#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct StructuraStudent {
	int id;
	int varsta;
	float medie;
	char* nume;
	char* specializare;
	unsigned char grupa;
};
typedef struct StructuraStudent Student;

struct Nod {
	Student info;
	struct Nod* st;
	struct Nod* dr;
};
typedef struct Nod Nod;

int maxim(int a, int b) {
	return (a > b ? a : b);
}

int calculeazaInaltimeArbore(Nod* rad) {
	if (rad) {
		return maxim(calculeazaInaltimeArbore(rad->st),
			calculeazaInaltimeArbore(rad->dr)) + 1;
	}
	return 0;
}

int calculDiferentaInaltimi(Nod* rad) {
	if (rad != NULL) {
		return calculeazaInaltimeArbore(rad->st) - calculeazaInaltimeArbore(rad->dr);
	}
	else {
		return 0;
	}
}

void afisareStudent(Student student) {
	printf("Id: %d\n", student.id);
	printf("Varsta: %d\n", student.varsta);
	printf("Medie: %.2f\n", student.medie);
	printf("Nume: %s\n", student.nume);
	printf("Specializare: %s\n", student.specializare);
	printf("Grupa: %c\n\n", student.grupa);
}

Student initStudent(int id, int varsta, float medie, const char* nume,
	const char* specializare, unsigned char grupa) {
	Student s;
	s.id = id;
	s.varsta = varsta;
	s.medie = medie;
	s.grupa = grupa;
	s.nume = (char*)malloc(strlen(nume) + 1);
	strcpy(s.nume, nume);
	s.specializare = (char*)malloc(strlen(specializare) + 1);
	strcpy(s.specializare, specializare);

	return s;
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

void adaugaStudentInArbore(Nod** rad, Student studentNou) {
	if (*rad == NULL) {
		Nod* nod = malloc(sizeof(Nod));
		nod->info = studentNou;
		nod->dr = NULL;
		nod->st = NULL;
		*rad = nod;
	}
	else {
		if ((*rad)->info.id > studentNou.id) {
			adaugaStudentInArbore(&((*rad)->st), studentNou);
		}
		if ((*rad)->info.id < studentNou.id) {
			adaugaStudentInArbore(&((*rad)->dr), studentNou);
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

void afisareStudentiDinArbore(Nod* rad) {
	if (rad) {
		afisareStudentiDinArbore(rad->st);
		afisareStudent(rad->info);
		afisareStudentiDinArbore(rad->dr);
	}
}

void afisarePreordine(Nod* rad) {
	if (rad) {
		afisareStudent(rad->info);
		afisarePreordine(rad->st);
		afisarePreordine(rad->dr);
	}
}

void dezalocareArboreDeStudenti(Nod** rad) {
	if (*rad) {
		dezalocareArboreDeStudenti(&(*rad)->st);
		dezalocareArboreDeStudenti(&(*rad)->dr);
		free((*rad)->info.nume);
		free((*rad)->info.specializare);
		free(*rad);
		*rad = NULL;
	}
}

Student getStudentByID(Nod* rad, int id) {
	Student s;
	s.id = -1;
	s.nume = NULL;
	s.specializare = NULL;

	if (rad) {
		if (rad->info.id == id) {
			s = rad->info;
			s.nume = malloc(sizeof(char) * (strlen(rad->info.nume) + 1));
			strcpy(s.nume, rad->info.nume);
			s.specializare = malloc(sizeof(char) * (strlen(rad->info.specializare) + 1));
			strcpy(s.specializare, rad->info.specializare);
		}
		if (id < rad->info.id) {
			s = getStudentByID(rad->st, id);
		}
		if (id > rad->info.id) {
			s = getStudentByID(rad->dr, id);
		}
	}
	return s;
}

int determinaNumarNoduri(Nod* rad) {
	if (rad) {
		return determinaNumarNoduri(rad->st) +
			+determinaNumarNoduri(rad->dr) + 1;
	}
	return 0;
}

float calculeazaSumaMediilor(Nod* rad) {
	if (rad) {
		return rad->info.medie +
			+calculeazaSumaMediilor(rad->st) +
			+calculeazaSumaMediilor(rad->dr);
	}
	return 0;
}

float calculeazaSumaMediilorUneiSpecializari(Nod* rad, const char* specializare) {
	if (rad) {
		float suma = calculeazaSumaMediilorUneiSpecializari(rad->st, specializare) +
			+calculeazaSumaMediilorUneiSpecializari(rad->dr, specializare);
		if (strcmp(rad->info.specializare, specializare) == 0) {
			suma += rad->info.medie;
		}
		return suma;
	}
	return 0;
}

int main() {
	Nod* rad = NULL;

	adaugaStudentInArbore(&rad, initStudent(1, 21, 8.50, "Ion", "Marketing", 'A'));
	adaugaStudentInArbore(&rad, initStudent(2, 22, 9.20, "Maria", "Informatica", 'B'));
	adaugaStudentInArbore(&rad, initStudent(3, 20, 7.80, "Andrei", "Marketing", 'A'));
	adaugaStudentInArbore(&rad, initStudent(4, 23, 9.70, "Elena", "Contabilitate", 'C'));
	adaugaStudentInArbore(&rad, initStudent(5, 21, 8.90, "Mihai", "Marketing", 'B'));

	afisarePreordine(rad);

	printf("Student cautat:");
	Student s = getStudentByID(rad, 4);
	afisareStudent(s);

	free(s.nume);
	free(s.specializare);

	printf("Numar noduri:%d\n", determinaNumarNoduri(rad));
	printf("Inaltime arbore:%d\n", calculeazaInaltimeArbore(rad));
	printf("Suma mediilor:%.2f\n", calculeazaSumaMediilor(rad));
	printf("Suma mediilor unei specializari:%.2f\n",
		calculeazaSumaMediilorUneiSpecializari(rad, "Marketing"));

	dezalocareArboreDeStudenti(&rad);
	return 0;
}