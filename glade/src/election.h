////////////////////////////election.h////////////////////////////////////////////////////
#ifndef ELECTION_H_INCLUDED
#define ELECTION_H_INCLUDED
#include <gtk/gtk.h>
/////////////////////////////////////STRUCT DATE//////////////////////////////////////////////
typedef struct Date
{
                int Jour;
                int Mois;
                int Annee;
}Date;
///////////////////////////////STRUCT ELECTION///////////////////////////////////////////////
typedef struct election
{
                char M[50]; //   Municipalite[50]
                char ID[50];
                int NH; //      Nbre_habitant
                int CN; //        Conseillers
                Date Date_ajout;
                Date Date_election;
                char Date_election1[20];
                char Date_ajout1[20];
                char NH1[20];
                char CN1[20];
                
}election;
/////////////////////////////////////////FONCTIONS//////////////////////////////////
void Ajouter_election(election L);
void Afficher_election(GtkWidget*liste);
void Modifier_election(election L_nv,char ID_R[]);
election Chercher_election(char ID_R[]);
int Supprimer_election(char ID_S[], char*Massoud);
int verif_ID(char ID_V[]);
int verif_Municipalite(char Mun[]);
election Chercher_multi(char CHX[]);
void Afficher_R_election(GtkWidget*liste, char CHX[]);
///////////////////////////////////////FNCT STATTTTTTTTTTTT//////////////////////////////////////////////
float TPE(char *file_utilisateur);
void Afficher_gang(GtkWidget*liste);
//////////////////////////////////////////utilisateur/////////////////////////////////////////////////////////////
typedef struct 
{
	int jour;
	int mois;
	int annee;
}date;

typedef struct
{	char prenom [20];
	char nom [20];
	char genre[10];
	date ddn; 
	char nationalite[20];
	char mdp [20];
	int numerotel;
	char adresse[30];
	int cin;
	char role[30];
	int vote;
	int bdv;
} utilisateur;
/////////////////////////////////////////////////////////////////////////////////////////////////


#endif //  ELECTION_H_INCLUDED
