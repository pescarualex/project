#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTI 100
#define MAX_NUME 50

// Structura pentru un student
typedef struct {
    int id;
    char nume[MAX_NUME];
    float medie;
} Student;

// Declarații de funcții
void adaugaStudent(Student studenti[], int *nrStudenti);
void afiseazaStudenti(const Student studenti[], int nrStudenti);
void stergeStudent(Student studenti[], int *nrStudenti);

int main() {
    Student studenti[MAX_STUDENTI];
    int nrStudenti = 0;
    int optiune;

    do {
        printf("\n--- Sistem de Gestionare a Studentilor ---\n");
        printf("1. Adauga student\n");
        printf("2. Afiseaza lista de studenti\n");
        printf("3. Sterge student\n");
        printf("4. Iesire\n");
        printf("Selecteaza o optiune: ");
        scanf("%d", &optiune);

        switch (optiune) {
            case 1:
                adaugaStudent(studenti, &nrStudenti);
                break;
            case 2:
                afiseazaStudenti(studenti, nrStudenti);
                break;
            case 3:
                stergeStudent(studenti, &nrStudenti);
                break;
            case 4:
                printf("Iesire din program.\n");
                break;
            default:
                printf("Optiune invalida. Incearca din nou.\n");
        }
    } while (optiune != 4);

    return 0;
}

// Funcție pentru adăugarea unui student
void adaugaStudent(Student studenti[], int *nrStudenti) {
    if (*nrStudenti >= MAX_STUDENTI) {
        printf("Lista de studenti este plina.\n");
        return;
    }

    Student nou;
    nou.id = *nrStudenti + 1; // Alocare automată de ID
    printf("Introduceti numele studentului: ");
    scanf(" %[^\n]", nou.nume); // Citire cu spații
    printf("Introduceti media studentului: ");
    scanf("%f", &nou.medie);

    studenti[*nrStudenti] = nou;
    (*nrStudenti)++;
    printf("Student adaugat cu succes!\n");
}

// Funcție pentru afișarea listei de studenți
void afiseazaStudenti(const Student studenti[], int nrStudenti) {
    if (nrStudenti == 0) {
        printf("Nu exista studenti in lista.\n");
        return;
    }

    printf("\n--- Lista Studentilor ---\n");
    for (int i = 0; i < nrStudenti; i++) {
        printf("ID: %d | Nume: %s | Medie: %.2f\n",
               studenti[i].id, studenti[i].nume, studenti[i].medie);
    }
}

// Funcție pentru ștergerea unui student
void stergeStudent(Student studenti[], int *nrStudenti) {
    if (*nrStudenti == 0) {
        printf("Nu exista studenti de sters.\n");
        return;
    }

    int id;
    printf("Introduceti ID-ul studentului de sters: ");
    scanf("%d", &id);

    int index = -1;
    for (int i = 0; i < *nrStudenti; i++) {
        if (studenti[i].id == id) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Studentul cu ID-ul %d nu a fost gasit.\n", id);
        return;
    }

    // Mută elementele pentru a elimina studentul
    for (int i = index; i < *nrStudenti - 1; i++) {
        studenti[i] = studenti[i + 1];
    }

    (*nrStudenti)--;
    printf("Student sters cu succes!\n");
}
