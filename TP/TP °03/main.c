#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define max 100

typedef struct Etudiant {
    char nom[max];
    float note;
    struct Etudiant* suivant;
    struct Etudiant* precedant;
}Etudiant;

Etudiant* debut;

void initialisation() {
    debut = NULL;
}

void inserer (Etudiant *E) {

    if (debut == NULL) {
        debut = E;
        debut->precedant = debut;
        debut->suivant = debut;
        return;
    }

    debut->precedant->suivant = E;
    E->precedant = debut->precedant;
    E->suivant = debut;
    debut->precedant = E;

}

void affiche () {

    Etudiant *courant = debut;
    printf("Affichage des etudiants\n");
    if (debut == NULL) {
        printf("La liste des etudiants est vide\n");
        return;
    }

    do {
        printf("Etudiant: %s | note: %.2f\n", courant->nom, courant->note);
        courant = courant->suivant;
    } while(courant != debut);

}

Etudiant* rechercher (char nom[max]) {

    if (debut == NULL)
        return NULL;

    Etudiant *courant = debut;

    do  {
        if (strcmp(courant->nom, nom) == 0)
            return courant;
        courant = courant->suivant;
    } while(courant != debut);

    return NULL;

}

void supprimer (char nom[max]) {

    Etudiant *E = rechercher(nom);
    if (E == NULL) {
        printf("L' etudiant n'existe pas dans la liste\n");
        return;
    }

    E->precedant->suivant = E->suivant;
    E->suivant->precedant = E->precedant;

    if (E == debut)
        debut = debut->suivant;

    free(E);


}

void trier () {

    if (debut == NULL || debut->suivant == debut)
        return;

    Etudiant *A = debut, *B, *min;
    char tmpNom[max];
    float tmpNote;
    for (A = debut; A != debut->precedant;A = A->suivant) {
        min = A;
        for (B = A->suivant;B != debut;B = B->suivant)
            if (B->note < min->note)
                min = B;

        if (min != A) {
            strcpy(tmpNom, min->nom);
            tmpNote = min->note;
            strcpy(min->nom, A->nom);
            min->note = A->note;
            strcpy(A->nom, tmpNom);
            A->note = tmpNote;
        }
    }

}

int main () {

    initialisation();

    Etudiant *E;
    FILE* fl = fopen("etudiants.txt", "r");
    while(!feof(fl)) {
        E = (Etudiant*)malloc(sizeof(Etudiant));
        fscanf(fl, " %s %f", E->nom, &E->note);
        inserer(E);
    }
    fclose(fl);
    affiche();

    printf("-----------------------------------\nTrier\n");
    trier();
    affiche();
    system("pause");
    return 0;

}
