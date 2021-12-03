#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define max 50

typedef struct {
    float tab[max];
    int sommet;
}Pile;

void initialiser(Pile *P) {
    P->sommet = -1;
}

void empiler(Pile *P, float x) {
    if (P->sommet < max - 1)
        P->tab[++P->sommet] = x;
    else
        printf("Pile pleine");
}

float depiler(Pile *P) {
    return P->tab[P->sommet--];
}

int est_expression(char ch) {
    char *exp = "*/+-";
    while(*exp) {
        if (*exp == ch) {
            return 1;
        }
        exp++;
    }
    return 0;
}

float operation(char ch, float a, float b) {
    if (ch == '+') return a+b;
    if (ch == '*') return a*b;
    if (ch == '-') return b - a;
    if (ch == '/') return b/a;
}

void affichage (Pile P) {
    for (int i = 0;i<=P.sommet;i++)
        printf("%f\n", P.tab[P.sommet]);
}

void expression (Pile *P, char *ch) {

    float res = 0;
    float a, b, c;
    while(*ch) {
        if (est_expression(*ch) == 0 && *ch != ' ') {
            res = 0;
            while (est_expression(*ch) == 0 && *ch != ' ') {
                res *= 10;
                res += *ch - '0';
                ch++;
            }
            empiler(P, res);
        } else if(est_expression(*ch) == 1) {
            a = depiler(P);
            b = depiler(P);
            c = operation(*ch, a, b);
            empiler(P, c);
        }
        ch++;
    }
    printf("Le résulat est : %f", depiler(P));

}


void main () {

    Pile p;
    initialiser(&p);
    char str[100];
    printf("Entrer un expression polonaise\n");
    gets(str);
    expression(&p, str);

}
