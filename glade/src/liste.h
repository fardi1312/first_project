#ifndef CANDIDAT_H_INCLUDED
#define CANDIDAT_H_INCLUDED

typedef struct
{
int jour;
int mois;
int annee;
}Date;
typedef struct {
  char prenom[10];
   char nom[10] ;
    int id ;
     int cin ;
      int tel;
       char gouvernorat[10];
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
int  tete;
candidat T[9];
int Nb_candidats;
Date date_ajout;
int nbr;
}Liste;

int L_ordre( char *LE, Liste t[20], char * candidat);
int nbe(int id,char *candidat);


#endif // CANDIDAT_H_INCLUDED

