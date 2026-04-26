#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct StructuraStudent {
    int id;
    int varsta;
    float medie;
    char* nume;
    char* facultate;
    unsigned char grupa;
};
typedef struct StructuraStudent Student;

struct Nod {
    Student info;
    struct Nod* stanga;
    struct Nod* dreapta;
};
typedef struct Nod Nod;

Student citireStudentDinFisier(FILE* file) {
    char buffer[100];
    char sep[3] = ",\n";
    Student s;

    fgets(buffer, 100, file);

    char* aux = strtok(buffer, sep);
    s.id = atoi(aux);

    s.varsta = atoi(strtok(NULL, sep));
    s.medie = atof(strtok(NULL, sep));

    aux = strtok(NULL, sep);
    s.nume = malloc(strlen(aux) + 1);
    strcpy(s.nume, aux);

    aux = strtok(NULL, sep);
    s.facultate = malloc(strlen(aux) + 1);
    strcpy(s.facultate, aux);

    s.grupa = *strtok(NULL, sep);

    return s;
}

void afisareStudent(Student s) {
    printf("Id: %d\n", s.id);
    printf("Varsta: %d\n", s.varsta);
    printf("Medie: %.2f\n", s.medie);
    printf("Nume: %s\n", s.nume);
    printf("Facultate: %s\n", s.facultate);
    printf("Grupa: %c\n\n", s.grupa);
}

void adaugaStudentInArbore(Nod** rad, Student studentNou) {
    if (*rad == NULL) {
        Nod* nod = malloc(sizeof(Nod));
        nod->info = studentNou;
        nod->stanga = NULL;
        nod->dreapta = NULL;
        *rad = nod;
    }
    else {
        if (studentNou.id < (*rad)->info.id) {
            adaugaStudentInArbore(&(*rad)->stanga, studentNou);
        }
        else if (studentNou.id > (*rad)->info.id) {
            adaugaStudentInArbore(&(*rad)->dreapta, studentNou);
        }
    }
}

Nod* citireArboreStudentiDinFisier(const char* numeFisier) {
    Nod* rad = NULL;
    FILE* f = fopen(numeFisier, "r");

    if (f) {
        while (!feof(f)) {
            Student s = citireStudentDinFisier(f);
            adaugaStudentInArbore(&rad, s);
        }
        fclose(f);
    }

    return rad;
}

void afisareInordine(Nod* rad) {
    if (rad) {
        afisareInordine(rad->stanga);
        afisareStudent(rad->info);
        afisareInordine(rad->dreapta);
    }
}

void afisarePreordine(Nod* rad) {
    if (rad) {
        afisareStudent(rad->info);
        afisarePreordine(rad->stanga);
        afisarePreordine(rad->dreapta);
    }
}

void afisarePostordine(Nod* rad) {
    if (rad) {
        afisarePostordine(rad->stanga);
        afisarePostordine(rad->dreapta);
        afisareStudent(rad->info);
    }
}

Student getStudentByID(Nod* rad, int id) {
    Student s;
    s.id = -1;
    s.nume = NULL;
    s.facultate = NULL;

    if (rad) {
        if (rad->info.id == id) {
            s = rad->info;

            s.nume = malloc(strlen(rad->info.nume) + 1);
            strcpy(s.nume, rad->info.nume);

            s.facultate = malloc(strlen(rad->info.facultate) + 1);
            strcpy(s.facultate, rad->info.facultate);

            return s;
        }
        else if (id < rad->info.id) {
            return getStudentByID(rad->stanga, id);
        }
        else {
            return getStudentByID(rad->dreapta, id);
        }
    }

    return s;
}

int determinaNumarNoduri(Nod* rad) {
    if (rad) {
        return 1 + determinaNumarNoduri(rad->stanga)
            + determinaNumarNoduri(rad->dreapta);
    }
    return 0;
}

int maxim(int a, int b) {
    return a > b ? a : b;
}

int calculeazaInaltimeArbore(Nod* rad) {
    if (rad) {
        return 1 + maxim(
            calculeazaInaltimeArbore(rad->stanga),
            calculeazaInaltimeArbore(rad->dreapta)
        );
    }
    return 0;
}

float calculeazaSumaMediilor(Nod* rad) {
    if (rad) {
        return rad->info.medie
            + calculeazaSumaMediilor(rad->stanga)
            + calculeazaSumaMediilor(rad->dreapta);
    }
    return 0;
}

float calculeazaMediaGenerala(Nod* rad) {
    int nr = determinaNumarNoduri(rad);
    if (nr > 0) {
        return calculeazaSumaMediilor(rad) / nr;
    }
    return 0;
}

int numaraStudentiDinFacultate(Nod* rad, const char* facultate) {
    if (rad) {
        int nr = numaraStudentiDinFacultate(rad->stanga, facultate)
            + numaraStudentiDinFacultate(rad->dreapta, facultate);

        if (strcmp(rad->info.facultate, facultate) == 0) {
            nr++;
        }

        return nr;
    }
    return 0;
}

void dezalocareArbore(Nod** rad) {
    if (*rad) {
        dezalocareArbore(&(*rad)->stanga);
        dezalocareArbore(&(*rad)->dreapta);

        free((*rad)->info.nume);
        free((*rad)->info.facultate);
        free(*rad);

        *rad = NULL;
    }
}

int main() {
    Nod* rad = citireArboreStudentiDinFisier("studenti.txt");

    printf("Afisare inordine:\n");
    afisareInordine(rad);

    printf("Afisare preordine:\n");
    afisarePreordine(rad);

    printf("Afisare postordine:\n");
    afisarePostordine(rad);

    printf("Student cautat:\n");
    Student s = getStudentByID(rad, 10);

    if (s.id != -1) {
        afisareStudent(s);
        free(s.nume);
        free(s.facultate);
    }
    else {
        printf("Studentul nu a fost gasit.\n");
    }

    printf("Numar noduri: %d\n", determinaNumarNoduri(rad));
    printf("Inaltime arbore: %d\n", calculeazaInaltimeArbore(rad));
    printf("Media generala: %.2f\n", calculeazaMediaGenerala(rad));
    printf("Studenti de la Informatica: %d\n",
        numaraStudentiDinFacultate(rad, "Informatica"));

    dezalocareArbore(&rad);

    return 0;
}