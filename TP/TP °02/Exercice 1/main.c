#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define max 50

typedef struct Enfant {
    char nom[max];
    char prenom[max];
    int age;
    char sexe;
    struct Enfant* suivant;
}Enfant;

typedef struct Parent {
    char nom[max];
    char prenom[max];
    struct Parent* suivant;
    Enfant* premier;
    Enfant* dernier;
}Parent;

Parent* head;

/**
 * Ajouter un parent au debut de la liste des parents
 * @return void
 */
void ajouterParentAuDebut(char nom[max], char prenom[max]) {

    Parent* P = (Parent*)malloc(sizeof(Parent));

    if (P == NULL) {
        printf("Espace insuffisant pour la reservation\n");
        return;
    }

    strcpy(P->nom, nom);
    strcpy(P->prenom, prenom);
    P->suivant = NULL; // L'element suivant de la liste chainee des parent
    P->premier = P->dernier = NULL; // Le premier enfant et le dernier enfant du parent

    if (head != NULL)
        P->suivant = head;

    head = P;

}

/**
 * Ajouter un enfant à un parent donné au dernier
 * @return void
 */
void ajouterEnfant(Parent* P, char nom[max], char prenom[max], int age, char sexe) {

    Enfant* E = (Enfant*)malloc(sizeof(Enfant));

    if (E == NULL) {
        printf("Espace insuffisant pour la reservation\n");
        return;
    }

    strcpy(E->nom, nom);
    strcpy(E->prenom, prenom);
    E->age = age;
    E->sexe = sexe;
    E->suivant = NULL;

    if (P->premier == NULL && P->dernier == NULL) {
        P->premier = P->dernier = E;
    } else {
        P->dernier->suivant = E;
        P->dernier = E;
    }

}

/**
 *
 */
int compterParentsSansEnfants () {

    int NB = 0;

    Parent* P = head;

    while (P != NULL){
        if (P->premier == NULL && P->dernier == NULL) NB++;
        P = P->suivant;
    }

    return NB;

}

/**
 * Une fonction qui permet de supprimer les enfants agee de 21 ans pour toutes les parents
 */
void supprimer21AnsEnfants () {

    Parent *P;
    Enfant *E, *prev = NULL;
    for (P = head; P != NULL; P = P->suivant){

        E = P->premier;

        while (E != NULL) {
            if (E->age >= 21) {
                if (prev == NULL) {
                    P->premier = E->suivant;
                    free(E);
                    E = P->premier;
                } else {
                    prev->suivant = E->suivant;
                    free(E);
                    E = prev->suivant;
                }
            } else {
                prev = E;
                E = E->suivant;
            }
        }
    }

}

/**
 *
 *
 */
void ajouterEnfantAuParent(char pnom[max], char nom[max], char prenom[max], int age , char sexe) {

    Parent* P = head;
    while(P != NULL) {
        if (strcmp(pnom, P->nom) == 0) {
            ajouterEnfant(P, nom, prenom, age, sexe);
            break;
        }
        P = P->suivant;
    }

}

/**
 * Afficher la liste des parents et les enfants pour chaque parent
 * @return void
 */

void afficherListeParents () {

    if (head == NULL) {
        printf("Liste vide\n");
        return;
    }

    Parent* P = head;
    Enfant* E;
    while(P != NULL) {
        printf("Les enfants du monsieur: %s %s\n", P->nom, P->prenom);
        printf("-------------------------------------------\n");
        E = P->premier;
        if (E == NULL) {
            printf("Ce monsieur n'a pas d'enfants\n");
        }
        while(E != NULL) {
            printf("%s %s - %d ans - %c\n", E->nom, E->prenom, E->age, E->sexe);
            E = E->suivant;
        }
        P = P->suivant;
        printf("\n");
    }

}


int main () {

    ajouterParentAuDebut("Essaoudi", "Abderrahman");
    ajouterParentAuDebut("Marghad", "Mohamed");
    ajouterParentAuDebut("Bennani", "Ali");
    ajouterParentAuDebut("Mouyain", "Zouhair");

    ajouterEnfantAuParent("Essaoudi", "Essaoudi", "Oussama", 19, 'M');
    ajouterEnfantAuParent("Essaoudi", "Essaoudi", "Mouhsin", 23, 'M');
    ajouterEnfantAuParent("Essaoudi", "Essaoudi", "Fatima-Ezzahra", 12, 'F');
    ajouterEnfantAuParent("Essaoudi", "Essaoudi", "Islam", 15, 'M');

    ajouterEnfantAuParent("Marghad", "Marghad", "Hassna", 31, 'F');
    ajouterEnfantAuParent("Marghad", "Marghad", "Ghizlane", 20, 'F');
    ajouterEnfantAuParent("Marghad", "Marghad", "Ayoub", 19, 'M');

    ajouterEnfantAuParent("Bennani", "Bennani", "Hassan", 23, 'M');

    printf("La liste des parents entrees avec leur enfants \n\n");
    afficherListeParents();
    printf("\n");

    printf("Le nombre des parents qui n'ont pas des enfants: %d\n\n", compterParentsSansEnfants());

    printf("Suppression des enfants pour chaque parent qui ont passée 21 ans ....\n\n");
    supprimer21AnsEnfants();

    printf("La listes des parents apres eliminations des enfants\n\n");
    afficherListeParents();


}
