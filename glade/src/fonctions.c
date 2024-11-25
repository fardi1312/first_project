#include<stdio.h>
#include"le.h"

 enum
{
	CID,
	CNOMLE,
	CNB_CANDIDATS,
	CORIENTATION,
	CJOUR,
	CMOIS,
	CANNEE,
	CID_CAND1,
	CID_CAND2,
	CID_CAND3,
	COLUMNS
};
enum
{
	SID,
	SNB,
       COLUMNS1
};
int Ajouter_LE(char* le,LE L)
{  
    FILE * f=fopen(le,"a+");
  
    if (f!=NULL){
      fprintf(f,"%d %s %d %s %d %d %d %d %d %d\n ",L.id,L.NomLE,L.Nb_candidats,L.orientation,L.jour,L.mois,L.annee,L.id_cand1,L.id_cand2,L.id_cand3);
 
      
 fclose(f);

        return 1;
    }
    else return 0;
}
void Modifier_LE(int idr,LE L1)
{   
    int test=0;
    LE L; 
    FILE * f=fopen("le.txt", "r");
    FILE * v=fopen("new.txt", "w+");
    if (f!=NULL && v!=NULL)
    {    
        while (fscanf(f,"%d %s %d %s %d %d %d %d %d %d\n",&L.id,L.NomLE,&L.Nb_candidats,L.orientation,&L.jour,&L.mois,&L.annee,&L.id_cand1,&L.id_cand2,&L.id_cand3) != EOF )
       {    
           if(L.id==idr)
           { 
fprintf(v,"%d %s %d %s %d %d %d %d %d %d\n" ,L1.id,L1.NomLE,L1.Nb_candidats,L1.orientation,L1.jour,L1.mois,L1.annee,L1.id_cand1,L1.id_cand2,L1.id_cand3);
test=1;
           }
           else
           { fprintf(v,"%d %s %d %s %d %d %d %d %d %d\n" ,L.id,L.NomLE,L.Nb_candidats,L.orientation,L.jour,L.mois,L.annee,L.id_cand1,L.id_cand2,L.id_cand3);}
}
    fclose(f);
    fclose(v);
    remove("le.txt");
    rename("new.txt","le.txt");
    return test;
}
}

int supprimer_LE(int ids, char * le)
{
LE L;
int t=0;
    FILE * f=fopen("le.txt", "r");
    FILE * f2 =fopen("new.txt", "a+");
    if(f==NULL || f2==NULL)
return 0;
else
    {
while(fscanf(f,"%d %s %d %s %d %d %d %d %d %d",&L.id,L.NomLE,&L.Nb_candidats,L.orientation,&L.jour,&L.mois,&L.annee,&L.id_cand1,&L.id_cand2,&L.id_cand3)!=EOF)
{
if(L.id==ids) t=1;
else
fprintf(f2,"%d %s %d %s %d %d %d %d %d %d\n",L.id,L.NomLE,L.Nb_candidats,L.orientation,L.jour,L.mois,L.annee,L.id_cand1,L.id_cand2,L.id_cand3);
}
        fclose(f);
        fclose(f2);
remove(le);
rename("new.txt", le);
if(t==1)
        return 1;
else
	return 0;
    }
}

LE Chercher_LE(int idr)
{
   LE L;
   LE L1;
   int rep=0;
   FILE * f=fopen("le.txt", "r");
   if (f!=NULL)
       {
       while(fscanf(f ,"%d %s %d %s %d %d %d %d %d %d\n" ,&L1.id,L1.NomLE,&L1.Nb_candidats,L1.orientation,&L1.jour,&L1.mois,&L1.annee,&L1.id_cand1,&L1.id_cand2,&L1.id_cand3)!= EOF )
         
         if(L1.id==idr)
         {
        strcpy(L.NomLE,L1.NomLE);
        strcpy(L.orientation,L1.orientation);
        L.id=L1.id;
	L.Nb_candidats=L1.Nb_candidats;
	L.jour=L1.jour;
	L.mois=L1.mois;
	L.annee=L1.annee;
	L.id_cand1=L1.id_cand1;
	L.id_cand2=L1.id_cand2;
	L.id_cand3=L1.id_cand3;


  	}  
 	 fclose (f);
 	}
       
return(L);
}


void afficher_LE(GtkWidget *liste)
{
GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;
    GtkTreeIter iter ;
    GtkListStore *store;
    int Mid;
    char MNomLE[20];
    int MNb_candidats;
    char Morientation[20];
    int Mid_cand1;
    int Mid_cand2;
    int Mid_cand3;
    int Mjour;
    int Mmois;
    int Mannee;
    store=NULL;
    LE L;
    FILE *f;
    store=gtk_tree_view_get_model(liste);
    if(store==NULL){
        
        renderer=gtk_cell_renderer_text_new();
        column=gtk_tree_view_column_new_with_attributes("id",renderer,"text",CID,NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

        renderer=gtk_cell_renderer_text_new();
        column=gtk_tree_view_column_new_with_attributes("NomLE",renderer,"text",CNOMLE,NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

        renderer=gtk_cell_renderer_text_new();
        column=gtk_tree_view_column_new_with_attributes("Nb_candidats",renderer,"text",CNB_CANDIDATS,NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);  


	 renderer=gtk_cell_renderer_text_new();
        column=gtk_tree_view_column_new_with_attributes("orientation",renderer,"text",CORIENTATION,NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

	renderer=gtk_cell_renderer_text_new();
        column=gtk_tree_view_column_new_with_attributes("jour",renderer,"text",CJOUR,NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

	renderer=gtk_cell_renderer_text_new();
        column=gtk_tree_view_column_new_with_attributes("mois",renderer,"text",CMOIS,NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

	renderer=gtk_cell_renderer_text_new();
        column=gtk_tree_view_column_new_with_attributes("annee",renderer,"text",CANNEE,NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);


 
        renderer=gtk_cell_renderer_text_new();
        column=gtk_tree_view_column_new_with_attributes("id_cand1",renderer,"text",CID_CAND1,NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
     
        renderer=gtk_cell_renderer_text_new();
        column=gtk_tree_view_column_new_with_attributes("id_cand2",renderer,"text",CID_CAND2,NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

        renderer=gtk_cell_renderer_text_new();
        column=gtk_tree_view_column_new_with_attributes("id_cand3",renderer,"text",CID_CAND3,NULL);
       gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);



         
    }
          
    store=gtk_list_store_new(COLUMNS,G_TYPE_INT,G_TYPE_STRING,G_TYPE_INT,G_TYPE_STRING,G_TYPE_INT,G_TYPE_INT,G_TYPE_INT,G_TYPE_INT,G_TYPE_INT,G_TYPE_INT);
    f=fopen("le.txt","r");
    if(f==NULL)
      return;
    else
    {
                 f=fopen("le.txt","a+");
         while(fscanf(f ,"%d %s %d %s %d %d %d %d %d %d\n" ,&Mid,MNomLE,&MNb_candidats,Morientation,&Mjour,&Mmois,&Mannee,&Mid_cand1,&Mid_cand2,&Mid_cand3)!=EOF)
         {
            gtk_list_store_append(store,&iter);
            gtk_list_store_set(store,&iter,CID,Mid,CNOMLE,MNomLE,CNB_CANDIDATS,MNb_candidats,CORIENTATION,Morientation,CJOUR,Mjour,CMOIS,Mmois,CANNEE,Mannee,CID_CAND1,Mid_cand1,CID_CAND2,Mid_cand2,CID_CAND3,Mid_cand3,-1);
         }
     fclose(f);
     gtk_tree_view_set_model(GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));
     g_object_unref(store);
    }
}




int verif_ID1(int idr1,int idr2,int idr3,int idr4)
{
    
    LE L;
    FILE *file=fopen("le.txt","r");
    if(file==NULL) printf("fichier n'existe pas");
    else
    {
while(fscanf(file ,"%d %s %d %s %d %d %d %d %d %d\n" ,&L.id,L.NomLE,&L.Nb_candidats,L.orientation,&L.jour,&L.mois,&L.annee,&L.id_cand1,&L.id_cand2,&L.id_cand3)!= EOF )
        {
        if((L.id==idr1)||(L.id_cand1==idr2)||(L.id_cand2==idr3)||(L.id_cand3==idr4))
        return 0;
        }
        return 1;
    }
        fclose(file);
}


















/*void rechercher_LE(GtkTreeView *liste,int id1 )
{
GtkCellRenderer *renderer;
GtkTreeViewColumn *column;
GtkTreeIter iter;
GtkListStore *store;


store=NULL;
FILE *f;
store=gtk_tree_view_get_model(liste);
if (store==NULL)
{



renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("ID",
                                                            renderer,
                                                            "text", ID,
                                                            NULL);
       
gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
       


        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("NOMLE",
                                                            renderer,
                                                            "text", NOMLE,
                                                            NULL);

gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);


renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("NB_CANDIDATS",
                                                            renderer,
                                                            "text", NB_CANDIDATS,
                                                            NULL);

gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);





        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("ORIENTATION",
                                                            renderer,
                                                            "text", ORIENTATION,
                                                            NULL);

gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);





        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("JOUR",
                                                            renderer,
                                                            "text", JOUR,
                                                            NULL);
       
gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);



        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("MOIS",
                                                            renderer,
                                                            "text", MOIS,
                                                            NULL);
       
gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("ANNEE",
                                                            renderer,
                                                            "text", ANNEE,
                                                            NULL);

gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);




renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("ID_CAND1",
                                                            renderer,
                                                            "text", ID_CAND1,
                                                            NULL);

gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("ID_CAND2",
                                                            renderer,
                                                            "text", ID_CAND2,
                                                            NULL);

gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);


renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("ID_CAND3",
                                                            renderer,
                                                            "text", ID_CAND3,
                                                            NULL);

gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);






}
store=gtk_list_store_new(COLUMNS,G_TYPE_INT,G_TYPE_STRING,G_TYPE_INT,G_TYPE_STRING,G_TYPE_INT,G_TYPE_INT,G_TYPE_INT,G_TYPE_INT,G_TYPE_INT,G_TYPE_INT);
f=fopen("le.txt","r");
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



{
f=fopen("le.txt","a+");
while(fscanf(f,"%d %s %d %s %d %d %d %d %d %d",&id,NomLE,&Nb_candidats,orientation,&jour,&mois,&annee,&id_cand1,&id_cand2,&id_cand3)!=EOF)
{ if(id==id1) {
gtk_list_store_append(store,&iter);
gtk_list_store_set(store,&iter,ID,id,NOMLE,NomLE,NBCANDIDATS,Nb_candidats,ORIENTATION,orientation,JOUR,jour,MOIS,mois,ANNEE,annee,IDCAND1,id_cand1,IDCAND2,id_cand2,IDCAND3,id_cand3,-1);
}}
fclose(f);
gtk_tree_view_set_model(GTK_TREE_VIEW(liste),GTK_TREE_MODEL(store));
g_object_unref(store);
}
}*/

/////////////////////////////////////////////////////////////// STAT /////////////////
#include <stdio.h>
#include <stdlib.h>
#include "le.h"
int L_ordre( char *Le,LE t[20], char * condidat){
   int permut,i;
  
  LE L,aux;
 
int n=0;

  FILE *f1=fopen(Le,"r");
    if(f1!=NULL){
        while (fscanf(f1,"%d %s %d %s %d %d %d %d %d %d %d\n ",&L.id,L.NomLE,&L.Nb_candidats,L.orientation,&L.jour,&L.mois,&L.annee,&L.id_cand1,&L.id_cand2,&L.id_cand3,&L.nbr)!=EOF)

{t[n]=L;
n++;

}
    }
   
  for(int i=0;i<n;i++){
   t[i].nbr=nbe(t[i].id,"condidat.txt");
}
for (int i=0; i<n;i++)
        {
do
{
    permut= 0;

       for(i =0 ; i <n-1;i++)
{
         if (t[i].nbr < t[i+1].nbr )
{
         aux=t[i];

         t[i]= t[i+1];

         t[i+1]= aux ;
         permut =1;
}

}

}
          while (permut == 1);
        }

for(int i=0;i<n;i++){
    printf("%d %d \t",t[i].id,t[i].nbr);
}
return n;
fclose(f1);



}
int nbe(int id,char * condidat){
    FILE * f=fopen(condidat,"r");
int nbliste;
candidat c ;
 int nombre=0;
if(f!=NULL){
    while(fscanf(f,"%s %s %d %s %d %s %d %s %d %s",c.prenom,c.nom,&c.cin,c.gouvernorat,&c.BDV,c.genre,&c.age,c.role,&c.vote,c.nationalite)!=EOF){
        if(c.vote==id){
            nombre+=1;
        }
    }
}
fclose(f);
return nombre;
}

//////////////////stat///////////////////

void afficher_LE_stat(GtkWidget *liste)
{
GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;
    GtkTreeIter iter ;
    GtkListStore *store;
    int Mid;
    char MNomLE[20];
    int MNb_candidats;
    char Morientation[20];
    int Mid_cand1;
    int Mid_cand2;
    int Mid_cand3;
    int Mjour;
    int Mmois;
    int Mannee;
    store=NULL;
    LE t[20];
    LE L;
    FILE *f;
    store=gtk_tree_view_get_model(liste);
    if(store==NULL){
        
        renderer=gtk_cell_renderer_text_new();
        column=gtk_tree_view_column_new_with_attributes("id",renderer,"text",SID,NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

        renderer=gtk_cell_renderer_text_new();
        column=gtk_tree_view_column_new_with_attributes("nombre de vote",renderer,"text",SNB,NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
         
    }store=gtk_list_store_new(COLUMNS1,G_TYPE_INT,G_TYPE_INT);
    f=fopen("le.txt","r");
    if(f==NULL)
      return;
    else
    {
                 
         while(fscanf(f ,"%d %s %d %s %d %d %d %d %d %d\n" ,&Mid,MNomLE,&MNb_candidats,Morientation,&Mjour,&Mmois,&Mannee,&Mid_cand1,&Mid_cand2,&Mid_cand3)!=EOF)
         {int x=nbe(Mid,"condidat.txt");
            gtk_list_store_append(store,&iter);
            gtk_list_store_set(store,&iter,0,Mid,1,x,-1);
        }

     fclose(f);
     gtk_tree_view_set_model(GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));
     g_object_unref(store);
    }
}






