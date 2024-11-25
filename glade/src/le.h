#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

#include <gtk/gtk.h>
typedef struct
{
int jour;
int mois;
int annee;
}Date1;
typedef struct {
  char prenom[10];
   char nom[10] ;
    int id ;
     int cin ;
      int tel;
       char gouvernorat[10];   ////
       int BDV ;
        char genre[10];
         int age;
         char role[10];
         int vote;
         char nationalite[20];

}candidat;

typedef struct
{
int id;
char NomLE[20];
int Nb_candidats;
char orientation[20];
int id_cand1;
int id_cand2;
int id_cand3;
int jour;
int mois;
int annee;
int nbr;

}LE;

int L_ordre( char *Le, LE t[20], char * candidat);
int nbe(int id,char *candidat);


int Ajouter_LE(char* le, LE L);
void Modifier_LE(int idr,LE L1);
int supprimer_LE(int ids, char * le);
LE Chercher_LE(int idr);
void afficher_LE(GtkWidget *liste);
int verif_ID1(int idr1,int idr2,int idr3,int idr4);
void rechercher_LE(GtkTreeView *liste,int id1 );






#endif // HEADER_H_INCLUDED
