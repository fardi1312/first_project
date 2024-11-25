////////////////////////////////election.c/////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "election.h"
#include <gtk/gtk.h>
#include "callbacks.h"
#include "interface.h"
#include "support.h"
#include <time.h>

//////////////enum//////////////////
enum
{
                             EM, //   Municipalite[50]
                             EID,
                             ENH, //      Nbre_habitant
                             ECN, //      nbre_Conseillers
                             EDate_ajo,
			                 EDate_ele,			     
                             COLUMNS
};
////////////////////////////////////////////////// Ajouter /////////////////////////////////////////////////
void Ajouter_election(election L)
{

sprintf(L.Date_ajout1,"%d/%d/%d",L.Date_ajout.Jour,L.Date_ajout.Mois,L.Date_ajout.Annee);
sprintf(L.Date_election1,"%d/%d/%d",L.Date_election.Jour,L.Date_election.Mois,L.Date_election.Annee);
                            FILE*file;
                            file=fopen("liste_election.txt","a");
                            if(file!=NULL)
                            {
                                fprintf(file,"%s %s %d %d %s %s \n",L.M,L.ID,L.NH,L.CN,L.Date_ajout1,L.Date_election1);
                                fclose(file);
                            }
}
///////////////////////////////////////////////Afficher///////////////////////////////////////////////
void Afficher_election(GtkWidget*liste)
{
                GtkCellRenderer *renderer;
                GtkTreeViewColumn *column;
                GtkTreeIter  iter;
                GtkListStore *store;
                election L;
                char TM[20];
                char TID[20];
                int TNH;
                int TCN;
                char TDate_ajout1[20];
                char TDate_election1[20];
				store=NULL;
				store=gtk_tree_view_get_model(liste);
                            if (store == NULL)
                            {
                                                    renderer=gtk_cell_renderer_text_new();
                                                    column=gtk_tree_view_column_new_with_attributes("           M          ",renderer,"text", EM,  NULL);
                                                    gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

                                                    renderer=gtk_cell_renderer_text_new();
                                                    column=gtk_tree_view_column_new_with_attributes("         ID      ",renderer,"text", EID ,NULL);
                                                    gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

                                                    renderer=gtk_cell_renderer_text_new();
                                                    column=gtk_tree_view_column_new_with_attributes("       NH       ", renderer, "text", ENH , NULL);
                                                    gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

                                                    renderer=gtk_cell_renderer_text_new();
                                                    column=gtk_tree_view_column_new_with_attributes("      CN      ", renderer, "text", ECN , NULL);
                                                    gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

                                                    renderer=gtk_cell_renderer_text_new();
                                                    column=gtk_tree_view_column_new_with_attributes("    Date D'ajout   ",renderer,"text", EDate_ajo , NULL);
                                                    gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

                                                    renderer=gtk_cell_renderer_text_new();
                                                    column=gtk_tree_view_column_new_with_attributes("   Date election       ",renderer,"text", EDate_ele , NULL);
                                                    gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
                            }
                            FILE *file;
                            file=fopen("liste_election.txt","a+");
                            store = gtk_list_store_new(COLUMNS,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_INT,G_TYPE_INT,G_TYPE_STRING,G_TYPE_STRING);
                            while(fscanf(file,"%s %s %d %d %s %s \n",TM,TID,&TNH,&TCN,TDate_ajout1,TDate_election1)!=EOF)
                            {
                                                    gtk_list_store_append(store, &iter);
                                                    gtk_list_store_set(store, &iter , EM , TM , EID, TID , ENH , TNH , ECN , TCN , EDate_ajo , TDate_ajout1 , EDate_ele , TDate_election1 ,-1);
                            }
                            fclose(file);
                            gtk_tree_view_set_model (GTK_TREE_VIEW(liste),GTK_TREE_MODEL(store));
                            g_object_unref (store);
                            
                                                     
}
////////////////////////////////////////Supprimer_election//////////////////////////////////////
int Supprimer_election(char ID_S[], char*Massoud)
{
          
                            int t=0;
                            election L;    
                            FILE * file=fopen("liste_election.txt","r");
                            FILE * nv_file=fopen("nv_liste_election.txt","a+");
                            if(file==NULL || nv_file==NULL)  return 0;
                            else
                            {
                            while(fscanf(file,"%s %s %d %d %s %s \n",L.M,L.ID,&L.NH,&L.CN,L.Date_ajout1,L.Date_election1)!=EOF)
                            {
                            if(strcmp(L.ID,ID_S)==0) t=1;
                            else
                            fprintf(nv_file,"%s %s %d %d %s %s \n",L.M,L.ID,L.NH,L.CN,L.Date_ajout1,L.Date_election1);
                            }
                            fclose(file);
                            fclose(nv_file);
                            remove(Massoud);
                            rename("nv_liste_election.txt",Massoud);
                            if(t==1)  return 1;
                            else return 0;
                                
                            }
}
//////////////////////////////////////////Modifier/////////////////////////////////////////

void Modifier_election(election L_nv,char ID_R[])
{
election L;

sprintf(L_nv.Date_ajout1,"%d/%d/%d",L_nv.Date_ajout.Jour,L_nv.Date_ajout.Mois,L_nv.Date_ajout.Annee);
sprintf(L_nv.Date_election1,"%d/%d/%d",L_nv.Date_election.Jour,L_nv.Date_election.Mois,L_nv.Date_election.Annee);          
                               
                           
                            FILE * file=fopen("liste_election.txt", "r");
                            FILE * nv_file=fopen("nv_liste_election.txt", "w");

                            if(file!=NULL && nv_file!=NULL)
                            {
                            while(fscanf(file,"%s %s %d %d %s %s \n",L.M,L.ID,&L.NH,&L.CN,L.Date_ajout1,L.Date_election1)!=EOF)
                                {

                                if(strcmp(L.ID,ID_R)==0)
                                {
                                fprintf(nv_file,"%s %s %d %d %s %s \n",L_nv.M,L_nv.ID,L_nv.NH,L_nv.CN,L_nv.Date_ajout1,L_nv.Date_election1);
                                }
                                else
                                fprintf(nv_file,"%s %s %d %d %s %s \n",L.M,L.ID,L.NH,L.CN,L.Date_ajout1,L.Date_election1);
                                } 
                            }
                            fclose(file);
                            fclose(nv_file);
                            remove("liste_election.txt");
                            rename("nv_liste_election.txt","liste_election.txt");
}

election Chercher_election(char ID_R[])
{
 FILE *file_election;
 int x=-1;
                            election L;
                            election L1;
                            file_election=fopen("liste_election.txt","r");


  if (file_election!=NULL)
   {
   while(fscanf(file_election,"%s %s %d %d %s %s \n",L1.M,L1.ID,&L1.NH,&L1.CN,L1.Date_ajout1,L1.Date_election1)!=EOF)
    if (strcmp (L1.ID,ID_R) == 0)
	{
        sprintf(L1.NH1,"%d",L1.NH);
        sprintf(L1.CN1,"%d",L1.CN);
        strcpy(L.NH1,L1.CN1);
        strcpy(L.CN1,L1.NH1); 
        strcpy(L.M,L1.M);
        strcpy(L.ID,L1.ID);
        strcpy(L.Date_ajout1,L1.Date_ajout1);
        sscanf(L1.Date_election1,"%d/%d/%d",&L1.Date_election.Jour,&L1.Date_election.Mois,&L1.Date_election.Annee);
        L.NH=L1.NH;
        L.CN=L1.CN;
        L.Date_election.Jour=L1.Date_election.Jour;
        L.Date_election.Mois=L1.Date_election.Mois;
        L.Date_election.Annee=L1.Date_election.Annee;
        x=1;
    }  
  fclose (file_election);
 }
return(L);
}

//////////////////////////// verf////////////////////////////
int verif_ID(char ID_V[])
{
    
    election L;
    FILE *file=fopen("liste_election.txt","r");
    if(file==NULL) printf("fichier n'existe pas");
    else
    {
       while(fscanf(file,"%s %s %d %d %s %s \n",L.M,L.ID,&L.NH,&L.CN,L.Date_ajout1,L.Date_election1)!=EOF)
        {
        if(strcmp(L.ID,ID_V)==0)
        return 0;
        }
        return 1;
    }
        fclose(file);
}
///////////////////////////////////////////////////////////////////
int verif_Municipalite(char Mun[])
{
    
    election L;
    FILE *file=fopen("liste_election.txt","r");
    if(file==NULL) printf("fichier n'existe pas");
    else
    {
       while(fscanf(file,"%s %s %d %d %s %s \n",L.M,L.ID,&L.NH,&L.CN,L.Date_ajout1,L.Date_election1)!=EOF)
        {
        if(strcmp(L.M,Mun)==0)
        return 0;
        }
        return 1;
    }
        fclose(file);
}
//////////////////////////////////////////////////////////////////
election Chercher_multi(char CHX[])
{
 int chx=0;
 chx=atoi(CHX);
 FILE *file_election;
 int x=-1;
                            election L;
                            election L1;
                            file_election=fopen("liste_election.txt","r");


  if (file_election!=NULL)
   {
   while(fscanf(file_election,"%s %s %d %d %s %s \n",L1.M,L1.ID,&L1.NH,&L1.CN,L1.Date_ajout1,L1.Date_election1)!=EOF)
    if ((strcmp(L1.ID,CHX)==0)||(strcmp(L1.M,CHX)==0)||(strcmp(L1.Date_ajout1,CHX)==0)||(strcmp(L1.Date_ajout1,CHX)==0)||(chx==L1.NH)||(chx==L1.CN) )
	{
        sprintf(L1.NH1,"%d",L1.NH);
        sprintf(L1.CN1,"%d",L1.CN);
        strcpy(L.NH1,L1.CN1);
        strcpy(L.CN1,L1.NH1); 
        strcpy(L.M,L1.M);
        strcpy(L.ID,L1.ID);
        strcpy(L.Date_ajout1,L1.Date_ajout1);
        sscanf(L1.Date_election1,"%d/%d/%d",&L1.Date_election.Jour,&L1.Date_election.Mois,&L1.Date_election.Annee);
        L.NH=L1.NH;
        L.CN=L1.CN;
        L.Date_election.Jour=L1.Date_election.Jour;
        L.Date_election.Mois=L1.Date_election.Mois;
        L.Date_election.Annee=L1.Date_election.Annee;
      x=1;
    }  
  fclose (file_election);
 }
return(L);
}
///////////////////////////////////////////////////////////////
void Afficher_R_election(GtkWidget*liste, char CHX[])
{
                GtkCellRenderer *renderer;
                GtkTreeViewColumn *column;
                GtkTreeIter  iter;
                GtkListStore *store;
                election L;
                election L1;
                int x=0;
                int chx=atoi(CHX);
                char TM[20];
                char TID[20];
                int TNH;
                int TCN;
                char TDate_ajout1[20];
                char TDate_election1[20];
				store=NULL;
				store=gtk_tree_view_get_model(liste);
                            if (store == NULL)
                            {
                                                    renderer=gtk_cell_renderer_text_new();
                                                    column=gtk_tree_view_column_new_with_attributes("           M          ",renderer,"text", EM,  NULL);
                                                    gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

                                                    renderer=gtk_cell_renderer_text_new();
                                                    column=gtk_tree_view_column_new_with_attributes("         ID      ",renderer,"text", EID ,NULL);
                                                    gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

                                                    renderer=gtk_cell_renderer_text_new();
                                                    column=gtk_tree_view_column_new_with_attributes("       NH       ", renderer, "text", ENH , NULL);
                                                    gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

                                                    renderer=gtk_cell_renderer_text_new();
                                                    column=gtk_tree_view_column_new_with_attributes("      CN      ", renderer, "text", ECN , NULL);
                                                    gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

                                                    renderer=gtk_cell_renderer_text_new();
                                                    column=gtk_tree_view_column_new_with_attributes("    Date D'ajout   ",renderer,"text", EDate_ajo , NULL);
                                                    gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

                                                    renderer=gtk_cell_renderer_text_new();
                                                    column=gtk_tree_view_column_new_with_attributes("   Date election       ",renderer,"text", EDate_ele , NULL);
                                                    gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
                            }
                            FILE *file;
                            file=fopen("liste_election.txt","a+");
                            store = gtk_list_store_new(COLUMNS,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_INT,G_TYPE_INT,G_TYPE_STRING,G_TYPE_STRING);
                            while(fscanf(file,"%s %s %d %d %s %s \n",L1.M,L1.ID,&L1.NH,&L1.CN,L1.Date_ajout1,L1.Date_election1)!=EOF)
                               { 
                                if ((strcmp(L1.ID,CHX)==0)||(strcmp(L1.M,CHX)==0)||(strcmp(L1.Date_ajout1,CHX)==0)||(strcmp(L1.Date_ajout1,CHX)==0)||(chx==L1.NH)||(chx==L1.CN) )
                                {
                                    sprintf(L1.NH1,"%d",L1.NH);
                                    sprintf(L1.CN1,"%d",L1.CN);
                                
                                    strcpy(L.NH1,L1.NH1);
                                    strcpy(L.CN1,L1.CN1); 
                                    strcpy(TM,L1.M);
                                    strcpy(TID,L1.ID);
                                    strcpy(TDate_ajout1,L1.Date_ajout1);
                                    strcpy(TDate_election1,L1.Date_election1);
                                    TNH=L1.NH;
                                    TCN=L1.CN;
                                    x=1;
                                      }
                                if (x==1)
                                {
                                    gtk_list_store_append(store, &iter);
                                    gtk_list_store_set(store, &iter , EM , TM , EID, TID , ENH , TNH , ECN , TCN , EDate_ajo , TDate_ajout1 , EDate_ele , TDate_election1 ,-1);
                                }
                                x=0;
                                }
                            fclose(file);
                            gtk_tree_view_set_model (GTK_TREE_VIEW(liste),GTK_TREE_MODEL(store));
                           g_object_unref (store);
                            
                                                     
}
/////////////////////////////////TPEEEEEEEEEEEEEEEEEEEEEEEE////////////////////////////////////////
float TPE(char *file_utilisateur)
{
FILE *file=fopen(file_utilisateur,"r");
utilisateur u;
int NBR_EL=0;
int NBR_V=0;
                        if(file!=0){             
                        while(fscanf(file,"%s %s %s %d %d %d %s %s %d %s %d %s %d %d\n",u.nom,u.prenom,u.genre,&u.ddn.jour,&u.ddn.mois,&u.ddn.annee,u.nationalite,u.mdp,&u.numerotel,u.adresse,&u.cin,u.role,&u.vote,&u.bdv)!=EOF)
                        {
                        NBR_EL++;
                        if(u.vote!=-1)  NBR_V++; 
                        }
                        fclose(file);
                        }
                        return(((float)NBR_V/NBR_EL)*100);
}
///////////////////////////////////////////////////////////////////////////////////////////////////

 void Afficher_gang(GtkWidget*liste)
{
                GtkCellRenderer *renderer;
                GtkTreeViewColumn *column;
                GtkTreeIter  iter;
                GtkListStore *store;
                election L;
                char TM[20];
                char TID[20];
                int TNH;
                int TCN;
				store=NULL;
				store=gtk_tree_view_get_model(liste);
                            if (store == NULL)
                            {
                                                    renderer=gtk_cell_renderer_text_new();
                                                    column=gtk_tree_view_column_new_with_attributes("           M          ",renderer,"text", EM,  NULL);
                                                    gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

                                                    renderer=gtk_cell_renderer_text_new();
                                                    column=gtk_tree_view_column_new_with_attributes("         ID      ",renderer,"text", EID ,NULL);
                                                    gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

                                                    renderer=gtk_cell_renderer_text_new();
                                                    column=gtk_tree_view_column_new_with_attributes("       NH       ", renderer, "text", ENH , NULL);
                                                    gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

                                                    renderer=gtk_cell_renderer_text_new();
                                                    column=gtk_tree_view_column_new_with_attributes("      CN      ", renderer, "text", ECN , NULL);
                                                    gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
 }
                            FILE *file;
                            //file=fopen("liste_election.txt","a+");
                            store = gtk_list_store_new(COLUMNS,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_INT,G_TYPE_INT);
                            while(fscanf(file,"%s %s %d %d %s %s \n",TM,TID,&TNH,&TCN)!=EOF)
                            {
                                                    gtk_list_store_append(store, &iter);
                                                    gtk_list_store_set(store, &iter , EM , TM , EID, TID , ENH , TNH , ECN , TCN ,-1);
                            }
                            fclose(file);
                            gtk_tree_view_set_model (GTK_TREE_VIEW(liste),GTK_TREE_MODEL(store));
                            g_object_unref (store);
                            
                                                     
}                               
                             
                                
                            








