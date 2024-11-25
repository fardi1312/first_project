#ifndef BV_H_INCLUDED
#define BV_H_INCLUDED
#include <gtk/gtk.h>
typedef struct
{   int id ;
   int agent_BV; 
 char gouvernorat[20];
 int salle;
    int cap_elec;
      int cap_ob;
   
}BV;

typedef struct
{ char prenom[30];
  char nom[30];
  int id;
  int cin;
  int tel;
  char gouvernorat[30];
  int BDV;
  char genre[30];
  int age;
  char role[30];
  int vote;
  char nationalite[30];
}condidat;




int ajouter(char *Bv,BV V );
int modifier( char *Bv, int id, BV nouv);
int supprimer(char *Bv, int id);
BV chercher(char *Bv, int id);
//BV chercher1(char *Bv, int cap);
condidat chercher1(char * user, int id);
void afficher_vote(GtkTreeView *liste);
void rechercher(int id,GtkTreeView *liste);
int nbe_bv( char *user, int id);
void affiche_stat(GtkTreeView *liste);
void taux (char * user,float *tn, float *te);
void afficher_stat_ons(GtkTreeView *liste);
#endif // BV_H_INCLUDED
