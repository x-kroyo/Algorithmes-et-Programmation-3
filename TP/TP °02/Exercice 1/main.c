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
 * Ajouter un enfant à un parent donné par son pointeur au dernier de la LSC
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
 * Compter les parents qui n'ont pas aucun enfants et il retourne ce nombre
 * @return int
 */
int compterParentsSansEnfants () {

    int NB = 0;

    for (Parent* P = head; P != NULL; P = P->suivant)
        if (P->premier == NULL && P->dernier == NULL) NB++;

    return NB;

}

/**
 * Une fonction qui permet de supprimer les enfants agee de 21 ans pour toutes les parents
 * @return void
 */
void supprimer21AnsEnfants () {

    Parent *P;
    Enfant *E, *prev = NULL;
    for (P = head; P != NULL; P = P->suivant){

        E = P->premier;

        while (E != NULL) {
            if (E->age >= 21) {
                // Tester si on est au debut du la liste
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
 * Ajouter un enfant à un parent selon son prenom
 * @return void
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
            printf("%s %s - %d ans - %s\n", E->nom, E->prenom, E->age, E->sexe == 'M' ? "Homme" : "Femme");
            E = E->suivant;
        }
        P = P->suivant;
        printf("\n");
    }

}

int main () {

    FILE *fl = fopen("parents.txt", "r");

    if (fl == NULL) {
        printf("Erreur avec l'ouvertude du fichier parents.txt\n");
        return 0;
    }

    char nom[max], prenom[max];

    // Lire la liste des parents selon le fichier parents.txt
    while (fscanf(fl, " %s %s", nom, prenom) != EOF)
        ajouterParentAuDebut(nom, prenom);

    fclose(fl);

    fl = fopen("enfants.txt", "r");

    if (fl == NULL) {
        printf("Erreur avec l'ouvertude du fichier enfants.txt\n");
        return 0;
    }

    int age;
    char sexe;
    char parentNom[max];

    // Lire la liste des enfants pour chaque parents selon le fichier enfants.txt
    while(fscanf(fl, " %s %s %s %d %c", parentNom, nom, prenom, &age, &sexe) != EOF)
        ajouterEnfantAuParent(parentNom, nom, prenom, age, sexe);

    fclose(fl);

    printf("La liste des parents entrees avec leur enfants \n\n");
    afficherListeParents();
    printf("\n");

    printf("Le nombre des parents qui n'ont pas des enfants: %d\n\n", compterParentsSansEnfants());

    printf("Suppression des enfants pour chaque parent qui ont passée 21 ans ....\n\n");
    supprimer21AnsEnfants();

    printf("La listes des parents apres eliminations des enfants\n\n");
    afficherListeParents();


}
