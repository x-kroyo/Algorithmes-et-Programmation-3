/**
 * Algorithmes et Programmation 3
 * TP °01 - Exercice 2
 * Ayoub Marghad
 * Group 8
 */

#include<stdio.h>
#include<string.h>
#define max 50

/**
 * Construction de la file
 */
typedef struct {
    int tab[max];
    int av, ar;
}File;

/**
 * Une fonction qui affiche une file donnée
 * @return void
 */

void initialisation(File *F) {
    F->av = F->ar = -1;
}

/**
 * Une fonction qui vérifie si une file donnée est vide ou non
 * @return 1 si le file est vide, sinon elle retroune 0
 */

int fileVide (File F) {
    return F.av == -1 && F.ar == -1;
}

/**
 * Une fonction qui affiche une file donnée
 * @return void
 */

int filePleine(File F) {
    return (F.ar + 1) % max == F.av;
}

/**
 * Une fonction qui enfiler un élement {x} dans un file {F}
 * @return void
 */
void enfiler(File *F, int x) {

    if (filePleine(*F)) {
        printf("Erreur: File pleine\n");
        return;
    }

    F->ar = ++F->ar % max;
    F->tab[F->ar] = x;
    if(F->av == -1) F->av = 0;

}

/**
 * Une fonction qui defiler la file {F}
 * @return int (l'element defiler qui est le premier element du tableau de la fil)
 */
int defiler(File *F) {

    int x;
    if (fileVide(*F)) printf("Erreur: File vide\n");
    else {
        x = F->tab[F->av];
        if (F->av == F->ar)
            F->av = F->ar = -1;
        else
            F->av = (F->av + 1) % max;
        return x;
    }
}

/**
 * Une fonction qui affiche une file donnée
 * @return void
 */
void afficheFile(File F) {

    if (fileVide(F)) {
        printf("File est vide\n");
        return;
    }

    if (F.ar >= F.av)
        for (int i = F.av;i <= F.ar;i++)
            printf("%d\n", F.tab[i]);
    else
        for (int i = F.av;i != F.ar + 1;i = ++i % max)
            printf("%d\n", F.tab[i]);

    printf("\n");

}

/**
 * La fonction main
 */

int main () {


    FILE *fl = fopen("test.txt", "r");

    // Tester si le fichier il y a un problème avec l'ouverture du fichier
    if (fl == NULL) {
        printf("Erreur avec l'ouverture du fichier test.txt");
        return 0;
    }

    File F;
    initialisation(&F);

    int k = 0, // Countour du nombre totales des entiers dans le fichiers
        x; // Variable à lire chaque entier dans le fichiers

    float moy = 0; // Moyenne du nombre

    while(fscanf(fl, "%d", &x) != EOF) {
        enfiler(&F, x);
        moy += x;
        k++;
    }

    fclose(fl);

    printf("Les %d entiers du fichier test.txt\n", k);
    afficheFile(F);

    moy /= k;

    while(k--) {
        x = defiler(&F);
        if (x >= moy) enfiler(&F, x);
    };


    printf("Les entiers qui sont supérieurs à la moyenne %f sont: \n", moy);
    afficheFile(F);

    return 0;
}
