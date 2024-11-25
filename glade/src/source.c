#include <stdio.h>
#include <string.h>
#include "BV.h"

 enum
{
	EID,
	EID_AGENT,
	EGOUVERNORAT,
	ESALLE,
	ECPE,
	ECPO,
	COLUMNS
};
enum
{
	SID,
	SEL,
	SCOLUMNS
};
int ajouter(char * Bv,BV V )
{
    FILE * f=fopen(Bv,"a");
    if(f!=NULL)
    {
        fprintf(f,"%d %d %s %d %d %d\n",V.id,V.agent_BV,V.gouvernorat,V.salle,V.cap_elec,V.cap_ob);
        fclose(f);
        return 1;
    }
    else return 0;
}
int modifier( char * Bv, int id, BV nouv)
{
    int trouve=0;
    BV V ;
    FILE * f=fopen(Bv, "r");
    FILE * f2=fopen("nouv.txt", "w");
    if(f!=NULL && f2!=NULL)
    {
        while(fscanf(f,"%d %d %s %d %d %d\n",&V.id,&V.agent_BV,V.gouvernorat,&V.salle,&V.cap_elec,&V.cap_ob)!=EOF)
        {
            if(V.id== id)
            {
                fprintf(f2,"%d %d %s %d %d %d\n",nouv.id,nouv.agent_BV,nouv.gouvernorat,nouv.salle,nouv.cap_elec,nouv.cap_ob);
                trouve=1;
            }
            else
                fprintf(f2,"%d %d %s %d %d %d\n",V.id,V.agent_BV,V.gouvernorat,V.salle,V.cap_elec,V.cap_ob);

        }
    }
    fclose(f);
    fclose(f2);
    remove(Bv);
    rename("nouv.txt",Bv);
    return trouve;
}
int supprimer(char * Bv, int id)
{
    int trouve=0;
    BV V;
    FILE * f=fopen(Bv,"r");
    FILE * f2=fopen("nouv.txt", "w");
    if(f!=NULL && f2!=NULL)
    {
        while(fscanf(f,"%d %d %s %d %d %d\n",&V.id,&V.agent_BV,V.gouvernorat,&V.salle,&V.cap_elec,&V.cap_ob)!=EOF)
        {
            if(V.id== id)
                trouve=1;
            else
                fprintf(f2,"%d %d %s %d %d %d\n",V.id,V.agent_BV,V.gouvernorat,V.salle,V.cap_elec,V.cap_ob);

        }
    }
    fclose(f);
    fclose(f2);
    remove(Bv);
    rename("nouv.txt",Bv);
    return trouve;
}

BV chercher(char * Bv, int id)
{
   BV V;
 int tr=0;
    FILE * f=fopen(Bv, "r");
 if(f!=NULL )
    {
while(fscanf(f,"%d %d %s %d %d %d\n",&V.id,&V.agent_BV,V.gouvernorat,&V.salle,&V.cap_elec,&V.cap_ob)!=EOF && tr==0)
{if(V.id==id)
tr=1;

}
}
if(tr==0)
V.id=-1;
return  V;
fclose(f);
}
condidat chercher1(char * user, int id)
{
   condidat c;
 int tr=0;
    FILE * f=fopen(user, "r");
 if(f!=NULL )
    {
 while(fscanf(f,"%s %s %d %d %d %s %d %s %d %s %d %s\n",c.prenom,c.nom,&c.id,&c.cin,&c.tel,c.gouvernorat,&c.BDV,c.genre,&c.age,c.role,&c.vote,c.nationalite)!=EOF && tr==0)
{if(c.id==id)
tr=1;

}
}
if(tr==0)
c.id=-1;
return  c;
fclose(f);
}
void afficher_vote(GtkTreeView *liste)
{
GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;
    GtkTreeIter iter ;
    GtkListStore *store;
BV v;
store=NULL;
    FILE *f;
    store=GTK_LIST_STORE(gtk_tree_view_get_model(liste));
    if(store==NULL){
        renderer=gtk_cell_renderer_text_new();
        column=gtk_tree_view_column_new_with_attributes("id",renderer,"text",EID,NULL);
        gtk_tree_view_append_column(liste,column);
 
        
        renderer=gtk_cell_renderer_text_new();
        column=gtk_tree_view_column_new_with_attributes("id agent BV",renderer,"text",EID_AGENT,NULL);
        gtk_tree_view_append_column(liste,column);

        renderer=gtk_cell_renderer_text_new();
        column=gtk_tree_view_column_new_with_attributes("gouvernorat",renderer,"text",EGOUVERNORAT,NULL);
        gtk_tree_view_append_column(liste,column);

	renderer=gtk_cell_renderer_text_new();
        column=gtk_tree_view_column_new_with_attributes("salle",renderer,"text",ESALLE,NULL);
        gtk_tree_view_append_column(liste,column);


        renderer=gtk_cell_renderer_text_new();
        column=gtk_tree_view_column_new_with_attributes("cap_elec",renderer,"text",ECPE,NULL);
        gtk_tree_view_append_column(liste,column);

	renderer=gtk_cell_renderer_text_new();
        column=gtk_tree_view_column_new_with_attributes("cap_ob",renderer,"text",ECPO,NULL);
        gtk_tree_view_append_column(liste,column);

}
          
    store=gtk_list_store_new(COLUMNS,G_TYPE_INT,G_TYPE_INT,G_TYPE_STRING,G_TYPE_INT,G_TYPE_INT,G_TYPE_INT);
    f=fopen("Bv.txt","r");
    if(f==NULL){return;}

 else
    {
                 f=fopen("Bv.txt","a+");
         while(fscanf(f,"%d %d %s %d %d %d ",&v.id,&v.agent_BV,v.gouvernorat,&v.salle,&v.cap_elec,&v.cap_ob)!=EOF)
         {
            gtk_list_store_append(store,&iter);
            gtk_list_store_set(store,&iter,0,v.id,1,v.agent_BV,2,v.gouvernorat,3,v.salle,4,v.cap_elec,5,v.cap_ob,-1);
          
         }
     fclose(f);
     gtk_tree_view_set_model(liste,GTK_TREE_MODEL(store));
     g_object_unref(store);
    }

}
	
void rechercher(int id,GtkTreeView *liste){
GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;
    GtkTreeIter iter ;
    GtkListStore *store;
BV v;
store=NULL;
    FILE *f;
    store=GTK_LIST_STORE(gtk_tree_view_get_model(liste));
    if(store==NULL){
        renderer=gtk_cell_renderer_text_new();
        column=gtk_tree_view_column_new_with_attributes("id",renderer,"text",EID,NULL);
        gtk_tree_view_append_column(liste,column);
 
        
        renderer=gtk_cell_renderer_text_new();
        column=gtk_tree_view_column_new_with_attributes("agent_BV",renderer,"text",EID_AGENT,NULL);
        gtk_tree_view_append_column(liste,column);

        renderer=gtk_cell_renderer_text_new();
        column=gtk_tree_view_column_new_with_attributes("gouvernorat",renderer,"text",EGOUVERNORAT,NULL);
        gtk_tree_view_append_column(liste,column);

       renderer=gtk_cell_renderer_text_new();
        column=gtk_tree_view_column_new_with_attributes("salle",renderer,"text",ESALLE,NULL);
        gtk_tree_view_append_column(liste,column);


        renderer=gtk_cell_renderer_text_new();
        column=gtk_tree_view_column_new_with_attributes("cap_elec",renderer,"text",ECPE,NULL);
        gtk_tree_view_append_column(liste,column);

	renderer=gtk_cell_renderer_text_new();
        column=gtk_tree_view_column_new_with_attributes("cap_ob",renderer,"text",ECPO,NULL);
        gtk_tree_view_append_column(liste,column);

}
          
    store=gtk_list_store_new(COLUMNS,G_TYPE_INT,G_TYPE_INT,G_TYPE_STRING,G_TYPE_INT,G_TYPE_INT,G_TYPE_INT);
    f=fopen("Bv.txt","r");
    if(f==NULL){return;}
    
else
    {
    
         while(fscanf(f,"%d %d %s %d %d %d",&v.id,&v.agent_BV,v.gouvernorat,&v.salle,&v.cap_elec,&v.cap_ob)!=EOF)
         { if(v.id==id){
           gtk_list_store_append(store,&iter);
            gtk_list_store_set(store,&iter,0,v.id,1,v.agent_BV,2,v.gouvernorat,3,v.salle,4,v.cap_elec,5,v.cap_ob,-1);}}

   
  fclose(f);
     gtk_tree_view_set_model(liste,GTK_TREE_MODEL(store));
     g_object_unref(store);
        }
     
    }
void taux (char * user,float *tn, float *te){
    int nbe=0,nbt=0;
     condidat c;
    FILE * f=fopen(user,"r");
    if(f!=NULL){
        while(fscanf(f,"%s %s %d %d %d %s %d %s %d %s %d %s\n",c.prenom,c.nom,&c.id,&c.cin,&c.tel,c.gouvernorat,&c.BDV,c.genre,&c.age,c.role,&c.vote,c.nationalite)!=EOF){
               
              
            if((strcmp(c.nationalite,"etranger")==0)&&(strcmp(c.role,"observateur")==0))
                nbe++;
            
           else if((strcmp(c.nationalite,"tunisien")==0)&&(strcmp(c.role,"observateur")==0))
                nbt++;
            

        }

            *tn=(float)(nbt*100)/(nbe+nbt);
            *te=(float)(nbe*100)/(nbe+nbt);

    fclose(f);
}
}

int nbe_bv( char *user, int id){//nombre delecteurs par bureau de vote
    condidat c;
    int nbe=0;
    FILE * f=fopen("user.txt","r");
      if(f!=NULL){
    while(fscanf(f,"%s %s %d %d %d %s %d %s %d %s %d %s\n",c.prenom,c.nom,&c.id,&c.cin,&c.tel,c.gouvernorat,&c.BDV,c.genre,&c.age,c.role,&c.vote,c.nationalite)!=EOF)
	{
        if((c.BDV==id)&&((strcmp(c.role,"electeur"))==0))
            nbe+=1;
        }
fclose(f);
        }

return nbe;
}
void afficher_stat_ons(GtkTreeView *liste)
{
GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;
    GtkTreeIter iter ;
    GtkListStore *store;
BV v;
int nombre;
store=NULL;
    FILE *f;
    store=GTK_LIST_STORE(gtk_tree_view_get_model(liste));
    if(store==NULL){
        renderer=gtk_cell_renderer_text_new();
        column=gtk_tree_view_column_new_with_attributes("id",renderer,"text",SID,NULL);
        gtk_tree_view_append_column(liste,column);
 
        
        renderer=gtk_cell_renderer_text_new();
        column=gtk_tree_view_column_new_with_attributes("nombre de vote",renderer,"text",SEL,NULL);
        gtk_tree_view_append_column(liste,column);
}
          
    store=gtk_list_store_new(SCOLUMNS,G_TYPE_INT,G_TYPE_INT);
    f=fopen("Bv.txt","r");
    if(f==NULL){return;}

 else
    {

         while(fscanf(f,"%d %d %s %d %d %d ",&v.id,&v.agent_BV,v.gouvernorat,&v.salle,&v.cap_elec,&v.cap_ob)!=EOF)
         {  int x=nbe_bv("user.txt",v.id);
            gtk_list_store_append(store,&iter);
            gtk_list_store_set(store,&iter,SID,v.id,SEL,x,-1);
          
         }
     fclose(f);
     gtk_tree_view_set_model(liste,GTK_TREE_MODEL(store));
     g_object_unref(store);
    }

}
       




      

         
   

