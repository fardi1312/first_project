#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif
#include <gtk/gtk.h>
#include "callbacks.h"
#include "interface.h"
#include "support.h"
#include <time.h>
#include "election.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "le.h"
#include "BV.h" 





///////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////MASSOUD FARDI///////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void
on_MF_Ajouter_Election_button3_clicked (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{   
    char ID_V[20];
    election L;
    GtkWidget*MF_M;
    GtkWidget*MF_ID;
    GtkWidget*MF_NH;
    GtkWidget*MF_CN;
    GtkWidget*MF_C;
    GtkWidget *MF_Time;
    GtkWidget*MF_Date_election;

//////////////////////////////strut my_time and struct tm///////////////////////////////////////
    time_t my_time;
    struct tm * timeinfo;
    time (&my_time);
    timeinfo = localtime (&my_time);

    struct tm* ptr;
    time_t t;
    t = time(NULL);
    ptr = localtime(&t);
////////////////////////////////////////////////////////////////////////////////////////////////   

MF_C=lookup_widget(objet_graphique,"MF_A1_controle");
MF_M=lookup_widget(objet_graphique,"MF_M_Ajouter_comboboxentry1");
MF_ID=lookup_widget(objet_graphique,"MF_ID_Ajouter_entry1");
MF_NH=lookup_widget(objet_graphique, "MF_NH_Ajouter_spinbutton1");
MF_Date_election= lookup_widget(objet_graphique, "MF_Date_A_Ajouter_calendar");
gtk_calendar_get_date(GTK_CALENDAR(MF_Date_election),&L.Date_election.Annee,&L.Date_election.Mois,&L.Date_election.Jour);
strcpy(L.M,gtk_combo_box_get_active_text(GTK_COMBO_BOX(MF_M)));
strcpy(L.ID,gtk_entry_get_text(GTK_ENTRY(MF_ID)));
L.Date_ajout.Annee = timeinfo->tm_year+1900;
L.Date_ajout.Mois = timeinfo->tm_mon+1;
L.Date_ajout.Jour = timeinfo->tm_mday;
L.NH=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON (MF_NH)) ;
                                if(L.NH>0 && L.NH<=5000)                  L.CN=10;
                                else if(L.NH>5000   && L.NH<=10000)       L.CN=12;
                                else if(L.NH>10000  && L.NH<=25000)       L.CN=16;
                                else if(L.NH>25000  && L.NH<=50000)       L.CN=22;
                                else if(L.NH>50000  && L.NH<=100000)      L.CN=30;
                                else if(L.NH>100000 && L.NH<=500000)      L.CN=40;
                                else if(L.NH>500000)                      L.CN=60;
                                else                                      L.CN=-1;
char M[20];
strcpy(ID_V,L.ID);
strcpy(M,L.M);

    if((strlen(L.ID))==0 || (strlen(L.M))==0 )
    {
               MF_Time=gtk_message_dialog_new(GTK_WINDOW(user_data),GTK_DIALOG_MODAL,GTK_MESSAGE_INFO,GTK_BUTTONS_OK,"Remplir tout les champs !!!");
              switch(gtk_dialog_run(GTK_DIALOG(MF_Time)))
              {
              case GTK_RESPONSE_OK:
              gtk_widget_destroy(MF_Time);
              break;
              }     
              }
    else if (((L.Date_election.Annee*356+L.Date_election.Mois*30 + L.Date_election.Jour) - (L.Date_ajout.Annee*356 + L.Date_ajout.Mois*30+L.Date_ajout.Jour))<0)
                    {
                                          
              MF_Time=gtk_message_dialog_new(GTK_WINDOW(user_data),GTK_DIALOG_MODAL,GTK_MESSAGE_INFO,GTK_BUTTONS_OK,"la date n'est pas possible !!!");
              switch(gtk_dialog_run(GTK_DIALOG(MF_Time)))
              {
              case GTK_RESPONSE_OK:
              gtk_widget_destroy(MF_Time);
              break;
              }
                    } 
    else if(verif_ID(ID_V)==0)
                  {
                    gtk_entry_set_text(GTK_ENTRY(MF_ID), "");
                    
                  MF_Time=gtk_message_dialog_new(GTK_WINDOW(user_data),GTK_DIALOG_MODAL,GTK_MESSAGE_INFO,GTK_BUTTONS_OK,"ID deja utilisee !!!");
                  switch(gtk_dialog_run(GTK_DIALOG(MF_Time)))
                  {
                  case GTK_RESPONSE_OK:
                  gtk_widget_destroy(MF_Time);
                  break;
                  }
                  }
    else if(verif_Municipalite(M)==0)
                  {                    
                  MF_Time=gtk_message_dialog_new(GTK_WINDOW(user_data),GTK_DIALOG_MODAL,GTK_MESSAGE_INFO,GTK_BUTTONS_OK,"Municipalite deja ajoutee !!!");
                  switch(gtk_dialog_run(GTK_DIALOG(MF_Time)))
                  {
                  case GTK_RESPONSE_OK:
                  gtk_widget_destroy(MF_Time);
                  break;
                  }   
                  } 
else
                  {    
                  Ajouter_election(L);
                  gtk_spin_button_set_value(GTK_SPIN_BUTTON(MF_NH),0);
                  gtk_entry_set_text(MF_ID,"");  
                  gtk_calendar_select_month(GTK_CALENDAR(MF_Date_election), (L.Date_ajout.Mois-1),L.Date_ajout.Annee);
                  gtk_calendar_select_day(GTK_CALENDAR(MF_Date_election), L.Date_ajout.Jour);
                  char ch[100];
                  sprintf(ch, "Ajouté avec succès le : %s ", asctime(ptr));
                  MF_Time=gtk_message_dialog_new(GTK_WINDOW(user_data),GTK_DIALOG_MODAL,GTK_MESSAGE_INFO,GTK_BUTTONS_OK,ch);
                                switch(gtk_dialog_run(GTK_DIALOG(MF_Time)))
                                {
                                case GTK_RESPONSE_OK:
                                gtk_widget_destroy(MF_Time);
                                break;
                                }
                  }    
}




void
on_MF_A_Afficher_button_clicked        (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_MF_10CN_radiobutton_toggled         (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

}


void
on_MF_12CN_radiobutton_toggled         (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

}


void
on_MF_16CN_radiobutton_toggled         (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

}


void
on_MF_22CN_radiobutton_toggled         (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

}


void
on_MF_30CN_radiobutton_toggled         (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

}


void
on_MF_40CN_radiobutton_toggled         (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

}


void
on_MF_60CN_radiobutton_toggled         (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

}


void
on_MF_verf_checkbutton1_toggled        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
int NH,CN;

GtkWidget*MF_NH;
MF_NH=lookup_widget(togglebutton, "MF_NH_Ajouter_spinbutton1");
NH=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON (MF_NH)) ;
                                if(NH>0 && NH<=5000)                  CN=10;
                                else if(NH>5000   && NH<=10000)       CN=12;
                                else if(NH>10000  && NH<=25000)       CN=16;
                                else if(NH>25000  && NH<=50000)       CN=22;
                                else if(NH>50000  && NH<=100000)      CN=30;
                                else if(NH>100000 && NH<=500000)      CN=40;
                                else if (NH>500000)                   CN=60; 
                                else                                  CN=-1;

GtkWidget *MF_10CN;
GtkWidget *MF_12CN;
GtkWidget *MF_16CN;
GtkWidget *MF_22CN;
GtkWidget *MF_30CN;
GtkWidget *MF_40CN;
GtkWidget *MF_60CN;
MF_10CN= lookup_widget(togglebutton, "MF_10CN_radiobutton");
MF_12CN= lookup_widget(togglebutton, "MF_12CN_radiobutton");
MF_16CN= lookup_widget(togglebutton, "MF_16CN_radiobutton");
MF_22CN= lookup_widget(togglebutton, "MF_22CN_radiobutton");
MF_30CN= lookup_widget(togglebutton, "MF_30CN_radiobutton");
MF_40CN= lookup_widget(togglebutton, "MF_40CN_radiobutton");
MF_60CN= lookup_widget(togglebutton, "MF_60CN_radiobutton");
if (CN==10)  gtk_toggle_button_set_active(GTK_RADIO_BUTTON(MF_10CN),1);    
else if (CN==12)  gtk_toggle_button_set_active(GTK_RADIO_BUTTON(MF_12CN),1);     
else if (CN==16)  gtk_toggle_button_set_active(GTK_RADIO_BUTTON(MF_16CN),1);
else if (CN==22) gtk_toggle_button_set_active(GTK_RADIO_BUTTON(MF_22CN),1);
else if (CN==30) gtk_toggle_button_set_active(GTK_RADIO_BUTTON(MF_30CN),1);
else if (CN==40)  gtk_toggle_button_set_active(GTK_RADIO_BUTTON(MF_40CN),1);     
else if (CN==60)gtk_toggle_button_set_active(GTK_RADIO_BUTTON(MF_60CN),1);     
}

void
on_MF_Actualiser_afficher_button1_clicked
                                        (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
GtkWidget *treeview;
treeview=lookup_widget(objet_graphique,"MF_Afficher_treeview");
Afficher_election(treeview);
}

void
on_MF_Afficher_treeview_row_activated  (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{
GtkWidget*MF_Afficher_treeview;
election L;
GtkTreeIter iter;
gchar* TM;
gchar* TID;
gint* TNH;
gint* TCN;
gchar* TDate_ajout1;
gchar* TDate_election1;

GtkTreeModel *model = gtk_tree_view_get_model(treeview);
if (gtk_tree_model_get_iter(model, &iter, path))
{
gtk_tree_model_get (GTK_LIST_STORE(model),&iter,0,&TM, 1 ,&TID, 2 , &TNH, 3 ,&TCN, 4 ,&TDate_ajout1, 5 ,&TDate_election1 ,-1);
}
}


void
on_Modifier_Election_button3_clicked   (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
//////////////////////////////strut my_time and struct tm///////////////////////////////////////
    time_t my_time;
    struct tm * timeinfo;
    time (&my_time);
    timeinfo = localtime (&my_time);

    struct tm* ptr;
    time_t t;
    t = time(NULL);
    ptr = localtime(&t);
////////////////////////////////////////////////////////////////////////////////////////////////  /
election L_nv;
char ID_V[20];
char ID_R[20];
GtkWidget*MF_M;
GtkWidget*MF_ID,*MF_R;
GtkWidget*MF_NH;
GtkWidget*MF_CN;
GtkWidget*MF_Date_election;
GtkWidget*MF_C;
GtkWidget*MF_Time;
MF_R=lookup_widget(objet_graphique,"entry1");
strcpy(ID_R,gtk_entry_get_text(GTK_ENTRY(MF_R)));
MF_C=lookup_widget(objet_graphique,"MF_M_controle");
MF_M=lookup_widget(objet_graphique,"MF_M_Modifier_comboboxentry1");
MF_ID=lookup_widget(objet_graphique,"MF_ID_Modifier_entry1");
MF_NH=lookup_widget(objet_graphique, "MF_NH_MOD_spinbutton1");
MF_Date_election= lookup_widget(objet_graphique, "MF_Date_A_Modifier_calendar");
gtk_calendar_get_date(GTK_CALENDAR(MF_Date_election),&L_nv.Date_election.Annee,&L_nv.Date_election.Mois,&L_nv.Date_election.Jour);
strcpy(L_nv.M,gtk_combo_box_get_active_text(GTK_COMBO_BOX(MF_M)));
strcpy(L_nv.ID,gtk_entry_get_text(GTK_ENTRY(MF_ID)));
L_nv.Date_ajout.Annee = timeinfo->tm_year+1900;
L_nv.Date_ajout.Mois = timeinfo->tm_mon+1;
L_nv.Date_ajout.Jour = timeinfo->tm_mday;
L_nv.NH=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON (MF_NH));
                               
                                if(L_nv.NH>0 && L_nv.NH<=5000)                  L_nv.CN=10;
                                else if(L_nv.NH>5000   && L_nv.NH<=10000)       L_nv.CN=12;
                                else if(L_nv.NH>10000  && L_nv.NH<=25000)       L_nv.CN=16;
                                else if(L_nv.NH>25000  && L_nv.NH<=50000)       L_nv.CN=22;
                                else if(L_nv.NH>50000  && L_nv.NH<=100000)      L_nv.CN=30;
                                else if(L_nv.NH>100000 && L_nv.NH<=500000)      L_nv.CN=40;
                                else if(L_nv.NH>500000)                         L_nv.CN=60;
                                else                                            L_nv.CN=-1;

strcpy(ID_V,L_nv.ID); 
        if((strlen(L_nv.ID))==0 || (strlen(L_nv.M))==0 )
        {
                  MF_Time=gtk_message_dialog_new(GTK_WINDOW(user_data),GTK_DIALOG_MODAL,GTK_MESSAGE_INFO,GTK_BUTTONS_OK,"Remplir tout les champs !!!");
                  switch(gtk_dialog_run(GTK_DIALOG(MF_Time)))
                  {
                  case GTK_RESPONSE_OK:
                  gtk_widget_destroy(MF_Time);
                  break;
                  }     
                  }
        else if (((L_nv.Date_election.Annee*356+L_nv.Date_election.Mois*30 + L_nv.Date_election.Jour) - (L_nv.Date_ajout.Annee*356 + L_nv.Date_ajout.Mois*30+L_nv.Date_ajout.Jour))<0)
                  {                          
                  MF_Time=gtk_message_dialog_new(GTK_WINDOW(user_data),GTK_DIALOG_MODAL,GTK_MESSAGE_INFO,GTK_BUTTONS_OK,"la date n'est pas possible !!!");
                  switch(gtk_dialog_run(GTK_DIALOG(MF_Time)))
                  {
                  case GTK_RESPONSE_OK:
                  gtk_widget_destroy(MF_Time);
                  break;
                  }
                  } 
    else if(verif_ID(ID_V)!=0)
                  {
                  gtk_entry_set_text(GTK_ENTRY(MF_ID), "");     
                  MF_Time=gtk_message_dialog_new(GTK_WINDOW(user_data),GTK_DIALOG_MODAL,GTK_MESSAGE_INFO,GTK_BUTTONS_OK,"ID non changable !!!");
                  switch(gtk_dialog_run(GTK_DIALOG(MF_Time)))
                  {
                  case GTK_RESPONSE_OK:
                  gtk_widget_destroy(MF_Time);
                  break;
                  }
                  } 
    else
                  {    
                  Modifier_election(L_nv,ID_R);
                  gtk_spin_button_set_value(GTK_SPIN_BUTTON(MF_NH),0);
                  gtk_entry_set_text(MF_ID,"");  
                  gtk_calendar_select_month(GTK_CALENDAR(MF_Date_election), (L_nv.Date_ajout.Mois-1),L_nv.Date_ajout.Annee);
                  gtk_calendar_select_day(GTK_CALENDAR(MF_Date_election), L_nv.Date_ajout.Jour);
                  char ch[100];
                  sprintf(ch, "Modifieé avec succès le : %s ", asctime(ptr));
                  MF_Time=gtk_message_dialog_new(GTK_WINDOW(user_data),GTK_DIALOG_MODAL,GTK_MESSAGE_INFO,GTK_BUTTONS_OK,ch);
                                switch(gtk_dialog_run(GTK_DIALOG(MF_Time)))
                                {
                                case GTK_RESPONSE_OK:
                                gtk_widget_destroy(MF_Time);
                                break;
                                }
                  }    
}









void
on_MF_R_MOD_Election_button3_clicked   (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
int x=-1;
char ID_R[20];
char ID[20];
election L;
GtkWidget*MF_M;
GtkWidget*MF_ID1;
GtkWidget*MF_NH;
GtkWidget*MF_CN;
GtkWidget*MF_R;
GtkWidget *MF_Time;
GtkWidget*MF_Date_election;
MF_R=lookup_widget(objet_graphique,"entry1");
strcpy(ID_R,gtk_entry_get_text(GTK_ENTRY(MF_R)));
MF_M=lookup_widget(objet_graphique,"MF_M_Modif1er_comboboxentry1");
MF_ID1=lookup_widget(objet_graphique,"MF_ID_Modifier_entry1");
MF_NH=lookup_widget(objet_graphique, "MF_NH_MOD_spinbutton1");
MF_Date_election=lookup_widget(objet_graphique, "MF_Date_A_Modifier_calendar");
FILE *file_election=fopen("liste_election.txt","r+");
if(file_election!=NULL)
                            {
                            while(fscanf(file_election,"%s %s %d %d %s %s\n",L.M,L.ID,&L.NH,&L.CN,L.Date_ajout1,L.Date_election1)!=EOF)
                                {
                                if(strcmp(ID_R,L.ID)==0) x=1;                                
                                }
fclose(file_election); 
                            }                              
if(x==1)
{  
                                election L1 = Chercher_election(ID_R); 
                                gtk_spin_button_set_value(GTK_SPIN_BUTTON(MF_NH), L1.NH);
                                gtk_entry_set_text(MF_ID1,L1.ID);  
                                gtk_calendar_select_month(GTK_CALENDAR(MF_Date_election), (L1.Date_election.Mois-1),L1.Date_election.Annee);
                                gtk_calendar_select_day(GTK_CALENDAR(MF_Date_election), L1.Date_election.Jour);
                                }
else
{
                                MF_Time=gtk_message_dialog_new(GTK_WINDOW(user_data),GTK_DIALOG_MODAL,GTK_MESSAGE_INFO,GTK_BUTTONS_OK,"Cet identifiant n'existe pas");
                                switch(gtk_dialog_run(GTK_DIALOG(MF_Time)))
                                {
                                case GTK_RESPONSE_OK:
                                gtk_widget_destroy(MF_Time);
                                break;
                                }
}
                         

}

void
on_MF_verf_MOD_checkbutton1_toggled    (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
int NH,CN;
GtkWidget*MF_NH;
MF_NH=lookup_widget(togglebutton, "MF_NH_MOD_spinbutton1");
NH=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON (MF_NH)) ;
                                   
                                if(NH>0 && NH<=5000)                  CN=10;
                                else if(NH>5000   && NH<=10000)       CN=12;
                                else if(NH>10000  && NH<=25000)       CN=16;
                                else if(NH>25000  && NH<=50000)       CN=22;
                                else if(NH>50000  && NH<=100000)      CN=30;
                                else if(NH>100000 && NH<=500000)      CN=40;
                                else if (NH>500000)                   CN=60;
GtkWidget *MF_10CN;
GtkWidget *MF_12CN;
GtkWidget *MF_16CN;
GtkWidget *MF_22CN;
GtkWidget *MF_30CN;
GtkWidget *MF_40CN;
GtkWidget *MF_60CN;
MF_10CN= lookup_widget(togglebutton, "MF_10CN_MOD_radiobutton");
MF_12CN= lookup_widget(togglebutton, "MF_12CN_MOD_radiobutton");
MF_16CN= lookup_widget(togglebutton, "MF_16CN_MOD_radiobutton");
MF_22CN= lookup_widget(togglebutton, "MF_22CN_MOD_radiobutton");
MF_30CN= lookup_widget(togglebutton, "MF_30CN_MOD_radiobutton");
MF_40CN= lookup_widget(togglebutton, "MF_40CN_MOD_radiobutton");
MF_60CN= lookup_widget(togglebutton, "MF_50CN_MOD_radiobutton");
 if (CN==10)
    {
      gtk_toggle_button_set_active(GTK_RADIO_BUTTON(MF_10CN),1);  
    }
  else if (CN==12)
    {
      gtk_toggle_button_set_active(GTK_RADIO_BUTTON(MF_12CN),1);     
    }
   else if (CN==16)
    { 
      gtk_toggle_button_set_active(GTK_RADIO_BUTTON(MF_16CN),1);
    }
   else if (CN==22)
    {
      gtk_toggle_button_set_active(GTK_RADIO_BUTTON(MF_22CN),1);
    }
  else if (CN==30)
    {
      gtk_toggle_button_set_active(GTK_RADIO_BUTTON(MF_30CN),1);
    }
   else if (CN==40)
    {
      gtk_toggle_button_set_active(GTK_RADIO_BUTTON(MF_40CN),1);      
    }
  else if (CN==60)
    {
      gtk_toggle_button_set_active(GTK_RADIO_BUTTON(MF_60CN),1);   
    }

}











void
on_MF_R_R_button_clicked               (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
time_t my_time;
struct tm * timeinfo;
time (&my_time);
timeinfo = localtime (&my_time);
int x=-1;
char ID_R[20];
char ID[20];
election L;
GtkWidget*MF_M;
GtkWidget*MF_ID;
GtkWidget*MF_NH;
GtkWidget*MF_CN;
GtkWidget*MF_R;
GtkWidget*MF_D_A;
GtkWidget*MF_Date_election;
GtkWidget *MF_Time;
MF_R=lookup_widget(objet_graphique,"entry2");
strcpy(ID_R,gtk_entry_get_text(GTK_ENTRY(MF_R)));
MF_M= lookup_widget(objet_graphique, "MF_R_M");
MF_ID= lookup_widget(objet_graphique, "MF_R_ID");
MF_NH= lookup_widget(objet_graphique, "MF_R_NH");
MF_CN= lookup_widget(objet_graphique, "MF_R_CN");
MF_D_A= lookup_widget(objet_graphique, "MF_R_DA");
MF_Date_election=lookup_widget(objet_graphique, "MF_Date_R_R_calendar");

FILE *file_election=fopen("liste_election.txt","r+");
if(file_election!=NULL)
                            {
                            while(fscanf(file_election,"%s %s %d %d %s %s\n",L.M,L.ID,&L.NH,&L.CN,L.Date_ajout1,L.Date_election1)!=EOF)
                                {
                                if(strcmp(ID_R,L.ID)==0) x=1;                                
                                }
                            fclose(file_election);
                            }
election L1 = Chercher_election(ID_R);                              
if(x==1)
{
gtk_calendar_select_month(GTK_CALENDAR(MF_Date_election), (L1.Date_election.Mois-1),L1.Date_election.Annee);
gtk_calendar_select_day(GTK_CALENDAR(MF_Date_election), L1.Date_election.Jour);
gtk_label_set_text(GTK_LABEL(MF_M),L1.M);
gtk_label_set_text(GTK_LABEL(MF_ID),L1.ID);
gtk_label_set_text(GTK_LABEL(MF_NH),L1.NH1);
gtk_label_set_text(GTK_LABEL(MF_CN),L1.CN1);
gtk_label_set_text(GTK_LABEL(MF_D_A),L1.Date_ajout1);
}
else
{
                                MF_Time=gtk_message_dialog_new(GTK_WINDOW(user_data),GTK_DIALOG_MODAL,GTK_MESSAGE_INFO,GTK_BUTTONS_OK,"Cet identifiant n'existe pas");
                                switch(gtk_dialog_run(GTK_DIALOG(MF_Time)))
                                {
                                case GTK_RESPONSE_OK:
                                gtk_widget_destroy(MF_Time);
                                break;
                                }
}
}


void
on_VERF_Sup_checkbutton_toggled        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

}


void
on_MF_S_S_button_clicked               (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
time_t my_time;
struct tm * timeinfo;
time (&my_time);
timeinfo = localtime (&my_time);
int x=-1;
char ID_R[20];
char ID[20];
election L;
GtkWidget*MF_M;
GtkWidget*MF_ID;
GtkWidget*MF_NH;
GtkWidget*MF_CN;
GtkWidget*MF_R;
GtkWidget*MF_D_A;
GtkWidget*MF_Date_election;
GtkWidget *MF_Time;
MF_R=lookup_widget(objet_graphique,"entry3_R_sup");
strcpy(ID_R,gtk_entry_get_text(GTK_ENTRY(MF_R)));
MF_M= lookup_widget(objet_graphique, "MF_S_M");
MF_ID= lookup_widget(objet_graphique, "MF_S_ID");
MF_NH= lookup_widget(objet_graphique, "MF_S_NH");
MF_CN= lookup_widget(objet_graphique, "MF_S_CN");
MF_D_A= lookup_widget(objet_graphique, "MF_S_DA");
MF_Date_election=lookup_widget(objet_graphique, "MF_Date_S_S_calendar");
election L1 = Chercher_election(ID_R);
FILE *file_election=fopen("liste_election.txt","r+");
if(file_election!=NULL)
                            {
                            while(fscanf(file_election,"%s %s %d %d %s %s\n",L.M,L.ID,&L.NH,&L.CN,L.Date_ajout1,L.Date_election1)!=EOF)
                                {
                                if(strcmp(ID_R,L.ID)==0) x=1;                                
                                }
                            fclose(file_election);
                            }                              
if(x==1)
{
gtk_calendar_select_month(GTK_CALENDAR(MF_Date_election), (L1.Date_election.Mois-1),L1.Date_election.Annee);
gtk_calendar_select_day(GTK_CALENDAR(MF_Date_election), L1.Date_election.Jour);
gtk_label_set_text(GTK_LABEL(MF_M),L1.M);
gtk_label_set_text(GTK_LABEL(MF_ID),L1.ID);
gtk_label_set_text(GTK_LABEL(MF_NH),L1.NH1);
gtk_label_set_text(GTK_LABEL(MF_CN),L1.CN1);
gtk_label_set_text(GTK_LABEL(MF_D_A),L1.Date_ajout1);
}
else
{
                                MF_Time=gtk_message_dialog_new(GTK_WINDOW(user_data),GTK_DIALOG_MODAL,GTK_MESSAGE_INFO,GTK_BUTTONS_OK,"Cet identifiant n'existe pas");
                                switch(gtk_dialog_run(GTK_DIALOG(MF_Time)))
                                {
                                case GTK_RESPONSE_OK:
                                gtk_widget_destroy(MF_Time);
                                break;
                                }
}
}


void
on_Supprimer_Election_button3_clicked  (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
GtkWidget *MF_S;
GtkWidget *MF_Q;
char ID_S[20] ;
int bbj=0;
MF_S=lookup_widget(objet_graphique,"entry3_R_sup");
MF_Q=lookup_widget(objet_graphique,"MF_S_controle");
strcpy(ID_S,gtk_entry_get_text(GTK_ENTRY(MF_S)));
                                  bbj =Supprimer_election(ID_S,"liste_election.txt");
                                  if(bbj==1)
                                  gtk_label_set_text(GTK_LABEL(MF_Q),"ID supprimee");
                                  else 
                                  gtk_label_set_text(GTK_LABEL(MF_Q),"error");                
}




void
on_button_R_multi_clicked              (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
GtkWidget *MF_T;
GtkWidget *treeview;
char CHX[20] ;
int chx=0;
MF_T=lookup_widget(objet_graphique,"entry_multi");
strcpy(CHX,gtk_entry_get_text(GTK_ENTRY(MF_T)));
chx=atoi(CHX);
treeview=lookup_widget(objet_graphique,"MF_Afficher_treeview");
Afficher_R_election(treeview,CHX);
}


void
on_MF_Multi_R_button_clicked           (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
time_t my_time;
struct tm * timeinfo;
time (&my_time);
timeinfo = localtime (&my_time);
int x=-1;
char CHX[20];
char ID[20];
int chx=0;
election L;
GtkWidget*MF_M;
GtkWidget*MF_ID;
GtkWidget*MF_NH;
GtkWidget*MF_CN;
GtkWidget*MF_R;
GtkWidget*MF_D_A;
GtkWidget *MF_Time;
GtkWidget*MF_Date_election;
MF_R=lookup_widget(objet_graphique,"entry2");
strcpy(CHX,gtk_entry_get_text(GTK_ENTRY(MF_R)));
MF_M= lookup_widget(objet_graphique, "MF_R_M");
MF_ID= lookup_widget(objet_graphique, "MF_R_ID");
MF_NH= lookup_widget(objet_graphique, "MF_R_NH");
MF_CN= lookup_widget(objet_graphique, "MF_R_CN");
MF_D_A= lookup_widget(objet_graphique, "MF_R_DA");
MF_Date_election=lookup_widget(objet_graphique, "MF_Date_R_R_calendar");
chx=atoi(CHX);
election L1 = Chercher_multi(CHX);
FILE *file_election=fopen("liste_election.txt","r+");
if(file_election!=NULL)
                            {
                            while(fscanf(file_election,"%s %s %d %d %s %s\n",L.M,L.ID,&L.NH,&L.CN,L.Date_ajout1,L.Date_election1)!=EOF)
                                {
                                 if ((strcmp(L.ID,CHX)==0)||(strcmp(L.M,CHX)==0)||(strcmp(L.Date_ajout1,CHX)==0)||(strcmp(L.Date_ajout1,CHX)==0)||(chx==L.NH)||(chx==L1.CN) ) x=1;
                                }
                            fclose(file_election);
                            }                              
if(x==1)
{
gtk_calendar_select_month(GTK_CALENDAR(MF_Date_election), (L1.Date_election.Mois-1),L1.Date_election.Annee);
gtk_calendar_select_day(GTK_CALENDAR(MF_Date_election), L1.Date_election.Jour);
gtk_label_set_text(GTK_LABEL(MF_M),L1.M);
gtk_label_set_text(GTK_LABEL(MF_ID),L1.ID);
gtk_label_set_text(GTK_LABEL(MF_NH),L1.NH1);
gtk_label_set_text(GTK_LABEL(MF_CN),L1.CN1);
gtk_label_set_text(GTK_LABEL(MF_D_A),L1.Date_ajout1);
}
else
{
                                MF_Time=gtk_message_dialog_new(GTK_WINDOW(user_data),GTK_DIALOG_MODAL,GTK_MESSAGE_INFO,GTK_BUTTONS_OK,"Cet caractere n'existe pas");
                                switch(gtk_dialog_run(GTK_DIALOG(MF_Time)))
                                {
                                case GTK_RESPONSE_OK:
                                gtk_widget_destroy(MF_Time);
                                break;
                                }
}
}


void
on_Conseillers_button_clicked          (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
GtkWidget *treeview;
treeview=lookup_widget(objet_graphique,"treeview_stat");
Afficher_gang(treeview);
}


void
on_TPE_button_clicked                  (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
  void
on_TPE_button_clicked                  (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{

//////////////////////////////strut my_time and struct tm///////////////////////////////////////
    time_t my_time;
    struct tm * timeinfo;
    time (&my_time);
    timeinfo = localtime (&my_time);

    struct tm* ptr;
    time_t t;
    t = time(NULL);
    ptr = localtime(&t);
///////////////////////////////////////////////////////////////////////////////////////////////  

GtkWidget *MF_TPE;
char ch[100];

float x = TPE("utilisateur.txt");

sprintf(ch, "Taux de participation : %.2f a l'heure %s, ", x ,asctime(ptr));
MF_TPE=gtk_message_dialog_new(GTK_WINDOW(user_data),GTK_DIALOG_MODAL,GTK_MESSAGE_INFO,GTK_BUTTONS_OK,ch);
              switch(gtk_dialog_run(GTK_DIALOG(MF_TPE)))
              {
              case GTK_RESPONSE_OK:
              gtk_widget_destroy(MF_TPE);
              break;
              }
}
GtkWidget *MF_TPE;
char ch[100];
float x = TPE("utilisateur.txt");
sprintf(ch, "Taux de participation : %.2f a l'heure %s, ", x);
MF_TPE=gtk_message_dialog_new(GTK_WINDOW(user_data),GTK_DIALOG_MODAL,GTK_MESSAGE_INFO,GTK_BUTTONS_OK,ch);
              switch(gtk_dialog_run(GTK_DIALOG(MF_TPE)))
              {
              case GTK_RESPONSE_OK:
              gtk_widget_destroy(MF_TPE);
              break;
              }
}


void
on_treeview_stat_row_activated         (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{
GtkWidget*MF_Afficher_treeview;
election L;
GtkTreeIter iter;
gchar* TM;
gchar* TID;
gint* TNH;
gint* TCN;
GtkTreeModel *model = gtk_tree_view_get_model(treeview);
if (gtk_tree_model_get_iter(model, &iter, path))
{
gtk_tree_model_get (GTK_LIST_STORE(model),&iter,0,&TM, 1 ,&TID, 2 , &TNH, 3 ,&TCN, 4 ,-1);
}
}


void
on_MF_Annuler_b_clicked                (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
    election L;
    GtkWidget*MF_M;
    GtkWidget*MF_ID;
    GtkWidget*MF_NH;
    GtkWidget*MF_CN;
    GtkWidget*MF_C;
    GtkWidget *MF_Time;
    GtkWidget*MF_Date_election;
    MF_C=lookup_widget(objet_graphique,"MF_A1_controle");
    MF_M=lookup_widget(objet_graphique,"MF_M_Ajouter_comboboxentry1");
    MF_ID=lookup_widget(objet_graphique,"MF_ID_Ajouter_entry1");
    MF_NH=lookup_widget(objet_graphique, "MF_NH_Ajouter_spinbutton1");
    MF_Date_election= lookup_widget(objet_graphique, "MF_Date_A_Ajouter_calendar");
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(MF_NH),0);
    gtk_entry_set_text(MF_ID,"");  
    gtk_calendar_select_month(GTK_CALENDAR(MF_Date_election), (L.Date_ajout.Mois-1),L.Date_ajout.Annee);
    gtk_calendar_select_day(GTK_CALENDAR(MF_Date_election), L.Date_ajout.Jour);
}


void
on_MF_Afficher_window_activate_current_link
                                        (GtkLabel        *label,
                                        gpointer         user_data)
{
GtkLabel *treeview;
treeview=lookup_widget(label,"treeview_stat");
Afficher_gang(treeview);
}




///////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////AMINE BEN AFIA///////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int nb_cand=1;
char robot[30];
void
on_button_valider1_AB_clicked      (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
GtkWidget *entry_id_l;
GtkWidget *entry_nom_l;
GtkWidget *combo_ori;
GtkWidget *spin_jour_c;
GtkWidget *spin_mois_c;
GtkWidget *spin_annee_c;
GtkWidget *entry_id_c1;
GtkWidget *entry_id_c2;
GtkWidget *entry_id_c3;
GtkWidget *label;
GtkWidget *label1;
char id0[10];
char id1[10];
char id2[10];
char id3[10];
LE l;
int rep=1;

entry_id_l=lookup_widget(objet_graphique, "entry_id_AB");
strcpy(id0,gtk_entry_get_text(GTK_ENTRY(entry_id_l)));
l.id=atoi(id0);
entry_nom_l=lookup_widget(objet_graphique, "entry_nom_AB");
strcpy(l.NomLE,gtk_entry_get_text(GTK_ENTRY(entry_nom_l)));
combo_ori=lookup_widget(objet_graphique, "combo_orien_AB");
strcpy(l.orientation,gtk_combo_box_get_active_text(GTK_COMBO_BOX(combo_ori)));
l.Nb_candidats=nb_cand;
spin_jour_c=lookup_widget(objet_graphique, "spin_jour_AB");
l.jour=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_jour_c));
spin_mois_c=lookup_widget(objet_graphique, "spin_mois_AB");
l.mois=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_mois_c));
spin_annee_c=lookup_widget(objet_graphique, "spin_annee_AB");
l.annee=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_annee_c));
entry_id_c1=lookup_widget(objet_graphique, "entry_id_can1_AB");
strcpy(id1,gtk_entry_get_text(GTK_ENTRY(entry_id_c1)));
l.id_cand1=atoi(id1);
entry_id_c2=lookup_widget(objet_graphique, "entry_id_can2_AB");
strcpy(id2,gtk_entry_get_text(GTK_ENTRY(entry_id_c2)));
l.id_cand2=atoi(id2);
entry_id_c3=lookup_widget(objet_graphique, "entry_id_can3_AB");
strcpy(id3,gtk_entry_get_text(GTK_ENTRY(entry_id_c3)));
l.id_cand3=atoi(id3);

label=lookup_widget(objet_graphique,"label24");
label1=lookup_widget(objet_graphique,"label27");



GtkWidget *existe;
existe=lookup_widget(objet_graphique,"dialog1");
if((strlen(id0))==0 || (strlen(id1))==0|| (strlen(id2))==0|| (strlen(id3))==0||(strlen(gtk_entry_get_text(GTK_ENTRY(entry_nom_l))))==0|| (strlen(gtk_combo_box_get_active_text(GTK_COMBO_BOX(combo_ori))))==0)
    {
        existe=gtk_message_dialog_new(GTK_WINDOW(user_data),GTK_DIALOG_MODAL,GTK_MESSAGE_INFO,GTK_BUTTONS_OK,"remplir les champs");
	switch(gtk_dialog_run(GTK_DIALOG(existe)))
	{
	case GTK_RESPONSE_OK:
	gtk_widget_destroy(existe);
	break;
	}      
    }

else if(verif_ID1(atoi(id0),atoi(id1),atoi(id2),atoi(id3))==0)
{
	existe=gtk_message_dialog_new(GTK_WINDOW(user_data),GTK_DIALOG_MODAL,GTK_MESSAGE_INFO,GTK_BUTTONS_OK,"ID  existe déjà!");
	switch(gtk_dialog_run(GTK_DIALOG(existe)))
	{
	case GTK_RESPONSE_OK:
	gtk_widget_destroy(existe);
	break;

	}
}

else 
{
if(nb_cand==3){
int test=Ajouter_LE("le.txt",l);
gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_jour_c),01);
gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_mois_c),01);
gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_annee_c),2022);
gtk_entry_set_text(entry_id_c1,""); 
gtk_entry_set_text(entry_nom_l,""); 
gtk_entry_set_text(entry_id_c2,""); 
gtk_entry_set_text(entry_id_c3,""); 
gtk_entry_set_text(entry_id_l,""); 

if(test==1)
{
	existe=gtk_message_dialog_new(GTK_WINDOW(user_data),GTK_DIALOG_MODAL,GTK_MESSAGE_INFO,GTK_BUTTONS_OK,"ajout avec succes!");
	switch(gtk_dialog_run(GTK_DIALOG(existe)))
	{
	case GTK_RESPONSE_OK:
	gtk_widget_destroy(existe);
	break;
}
}

}
}
}


void
on_radio_nb_cand_AB_toggled        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(togglebutton)))
nb_cand=3;
}


void
on_button_retour_ges2_AB_clicked   (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
GtkWidget*n;
GtkWidget*p;
n=lookup_widget(objet_graphique, "ajout_liste");
p=lookup_widget(objet_graphique, "menu");
p= create_menu();
gtk_widget_destroy(n);
}


void
on_button_valider2_AB_clicked      (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
int idr=0;
char IDR[20];
GtkWidget *idR;
GtkWidget *entry_id_l;
GtkWidget *entry_nom_l;
GtkWidget *combo_ori;
GtkWidget *spin_jour_c;
GtkWidget *spin_mois_c;
GtkWidget *spin_annee_c;
GtkWidget *entry_id_c1;
GtkWidget *entry_id_c2;
GtkWidget *entry_id_c3;
GtkWidget *label;
GtkWidget *label1;
char id0[10];
char id1[10];
char id2[10];
char id3[10];


LE L1;

idR=lookup_widget(objet_graphique, "entry_chercher_liste_AB");
strcpy(IDR,gtk_entry_get_text(GTK_ENTRY(idR)));
idr=atoi(IDR);


entry_id_l=lookup_widget(objet_graphique, "entry_id_liste1_AB");
strcpy(id0,gtk_entry_get_text(GTK_ENTRY(entry_id_l)));
L1.id=atoi(id0);
entry_nom_l=lookup_widget(objet_graphique, "entry_nom_liste1_AB");
strcpy(L1.NomLE,gtk_entry_get_text(GTK_ENTRY(entry_nom_l)));
combo_ori=lookup_widget(objet_graphique, "combo_ori1_AB");
strcpy(L1.orientation,gtk_combo_box_get_active_text(GTK_COMBO_BOX(combo_ori)));
L1.Nb_candidats=nb_cand;
spin_jour_c=lookup_widget(objet_graphique, "spin_jour1_AB");
L1.jour=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_jour_c));
spin_mois_c=lookup_widget(objet_graphique, "spin_mois1_AB");
L1.mois=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_mois_c));
spin_annee_c=lookup_widget(objet_graphique, "spin_annee1_AB");
L1.annee=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_annee_c));
entry_id_c1=lookup_widget(objet_graphique, "entry_id1_can1_AB");
strcpy(id1,gtk_entry_get_text(GTK_ENTRY(entry_id_c1)));
L1.id_cand1=atoi(id1);
entry_id_c2=lookup_widget(objet_graphique, "entry_id2_can2_AB");
strcpy(id2,gtk_entry_get_text(GTK_ENTRY(entry_id_c2)));
L1.id_cand2=atoi(id2);
entry_id_c3=lookup_widget(objet_graphique, "entry_id3_can3_AB");
strcpy(id3,gtk_entry_get_text(GTK_ENTRY(entry_id_c3)));
L1.id_cand3=atoi(id3);
label=lookup_widget(objet_graphique,"label29");
label1=lookup_widget(objet_graphique,"label28");

int test=0;

GtkWidget *existe;
existe=lookup_widget(objet_graphique,"dialog1");

if((strlen(id0))==0 || (strlen(id1))==0|| (strlen(id2))==0|| (strlen(id3))==0||(strlen(gtk_entry_get_text(GTK_ENTRY(entry_nom_l))))==0|| (strlen(gtk_combo_box_get_active_text(GTK_COMBO_BOX(combo_ori))))==0)
    {
        existe=gtk_message_dialog_new(GTK_WINDOW(user_data),GTK_DIALOG_MODAL,GTK_MESSAGE_INFO,GTK_BUTTONS_OK,"remplir les champs");
	switch(gtk_dialog_run(GTK_DIALOG(existe)))
	{
	case GTK_RESPONSE_OK:
	gtk_widget_destroy(existe);
	break;
	}      
    }

else 
{if(nb_cand==4)
{
Modifier_LE(idr,L1);
gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_jour_c),01);
gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_mois_c),01);
gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_annee_c),2022);
gtk_entry_set_text(entry_id_c1,""); 
gtk_entry_set_text(entry_nom_l,""); 
gtk_entry_set_text(entry_id_c2,""); 
gtk_entry_set_text(entry_id_c3,""); 
gtk_entry_set_text(entry_id_l,""); 

	existe=gtk_message_dialog_new(GTK_WINDOW(user_data),GTK_DIALOG_MODAL,GTK_MESSAGE_INFO,GTK_BUTTONS_OK,"les donnees sont changees!");
	switch(gtk_dialog_run(GTK_DIALOG(existe)))
	{
	case GTK_RESPONSE_OK:
	gtk_widget_destroy(existe);
	break;

}
}
}











}




void
on_button_chercher_liste_AB_clicked
                                        (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
char id1[20];
char id2[20];
char id3[20];
char id4[20];
GtkWidget *idR;
GtkWidget *label;
GtkWidget *entry_id_l;
GtkWidget *entry_nom_l;
GtkWidget *combo_ori;
GtkWidget *spin_jour_c;
GtkWidget *spin_mois_c;
GtkWidget *spin_annee_c;
GtkWidget *entry_id_c1;
GtkWidget *entry_id_c2;
GtkWidget *entry_id_c3;
GtkWidget *label1;
char IDR[20];
int x=-1;
LE L;
int idr=0;

entry_id_l=lookup_widget(objet_graphique, "entry_id_liste1_AB");
entry_nom_l=lookup_widget(objet_graphique, "entry_nom_liste1_AB");
combo_ori=lookup_widget(objet_graphique, "combo_ori1_AB");
entry_id_c1=lookup_widget(objet_graphique, "entry_id1_can1_AB");
entry_id_c2=lookup_widget(objet_graphique, "entry_id2_can2_AB");
entry_id_c3=lookup_widget(objet_graphique, "entry_id3_can3_AB");
label=lookup_widget(objet_graphique,"label29");
label1=lookup_widget(objet_graphique,"label28");
spin_jour_c=lookup_widget(objet_graphique, "spin_jour1_AB");
spin_mois_c=lookup_widget(objet_graphique, "spin_mois1_AB");
spin_annee_c=lookup_widget(objet_graphique, "spin_annee1_AB");
idR=lookup_widget(objet_graphique, "entry_chercher_liste_AB");
strcpy(IDR,gtk_entry_get_text(GTK_ENTRY(idR)));
idr=atoi(IDR);

FILE *f=fopen("le.txt","r+");
if(f!=NULL)
{
while (fscanf(f,"%d %s %d %s %d %d %d %d %d %d",&L.id,L.NomLE,&L.Nb_candidats,L.orientation,&L.jour,&L.mois,&L.annee,&L.id_cand1,&L.id_cand2,&L.id_cand3) != EOF )
                                {
                                if(idr==L.id) x=1;                                
                                }
				fclose(f);
                                }  


if(x==1)
{




LE L1=Chercher_LE(idr);

sprintf(id1,"%d",L1.id);
sprintf(id2,"%d",L1.id_cand1);
sprintf(id3,"%d",L1.id_cand2);
sprintf(id4,"%d",L1.id_cand3);



gtk_entry_set_text(entry_id_l,id1);
gtk_entry_set_text(entry_nom_l,L1.NomLE);





gtk_entry_set_text(entry_id_c1,id2); 
gtk_entry_set_text(entry_id_c2,id3); 
gtk_entry_set_text(entry_id_c3,id4); 
 
gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_jour_c), L1.jour);
gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_mois_c), L1.mois);
gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_annee_c), L1.annee);
}
else gtk_label_set_text(GTK_LABEL(label),"ID non trouve");
}














void
on_button_afficher_AB_clicked      (GtkWidget     *objet_graphique,
                                        gpointer         user_data)
{
GtkWidget*n;
GtkWidget*p;
n=lookup_widget(objet_graphique, "affichage_liste");
p=lookup_widget(objet_graphique, "menu");
n= create_affichage_liste ();
gtk_widget_show(n);

}


void
on_button_ajouter_AB_clicked       (GtkWidget     *objet_graphique,
                                        gpointer         user_data)
{GtkWidget*n;
GtkWidget*p;
n=lookup_widget(objet_graphique, "ajout_liste");
p=lookup_widget(objet_graphique, "menu");
n= create_ajout_liste ();
gtk_widget_show(n);


}


void
on_button_modifier_AB_clicked      (GtkWidget     *objet_graphique,
                                        gpointer         user_data)
{
GtkWidget*n;
GtkWidget*p;
n=lookup_widget(objet_graphique, "modification_liste");
p=lookup_widget(objet_graphique, "menu");
n= create_modification_liste ();
gtk_widget_show(n);

}


void
on_button_supprimer_AB_clicked     (GtkWidget     *objet_graphique,
                                        gpointer         user_data)
{GtkWidget*n;
GtkWidget*p;
n=lookup_widget(objet_graphique, "suppression_liste");
p=lookup_widget(objet_graphique, "menu");
n= create_suppression_liste ();
gtk_widget_show(n);


}


void
on_button_retour_ges1_AB_clicked   (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
GtkWidget*n;
GtkWidget*p;
n=lookup_widget(objet_graphique, "affichage_liste");
p=lookup_widget(objet_graphique, "menu");
p= create_menu();
gtk_widget_destroy(n);

}


void
on_button_retour_ges4_AB_clicked   (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
GtkWidget*n;
GtkWidget*p;
n=lookup_widget(objet_graphique, "suppression_liste");
p=lookup_widget(objet_graphique, "menu");
p= create_menu();
gtk_widget_destroy(n);

}


void
on_button_retour_ges5_AB_clicked   (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
GtkWidget*n;
GtkWidget*p;
n=lookup_widget(objet_graphique, "statistique_liste");
p=lookup_widget(objet_graphique, "menu");
p= create_menu();
gtk_widget_destroy(n);
}


void
on_button_ges3_AB_clicked          (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
GtkWidget*n;
GtkWidget*p;
n=lookup_widget(objet_graphique, "modification_liste");
p=lookup_widget(objet_graphique, "menu");
p= create_menu();
gtk_widget_destroy(n);
}




void
on_button_valider3_AB_clicked      (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{

GtkWidget *l;
GtkWidget *sortie;
char ch[10] ;
int id1,test2=0;
l=lookup_widget(objet_graphique,"entry_id_liste2_AB");
sortie=lookup_widget(objet_graphique,"label91");
strcpy(ch,gtk_entry_get_text(GTK_ENTRY(l)));
id1=atoi(ch);
test2 =supprimer_LE(id1,"le.txt");
if(test2==1)
gtk_label_set_text(GTK_LABEL(sortie),"ID  supprimee");
else 
gtk_label_set_text(GTK_LABEL(sortie),"error");

}


void
on_button_stat_liste_AB_clicked           (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
GtkWidget*n;
GtkWidget*p;
n=lookup_widget(objet_graphique, "statistique_liste");
p=lookup_widget(objet_graphique, "menu");
n= create_statistique_liste ();
gtk_widget_show(n);

}


void
on_radio_nb_cand1_AB_toggled       (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(togglebutton)))
nb_cand=4;
}


void
on_treeview_liste_AB_row_activated (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{
GtkTreeIter iter;
gint *Mid;
gchar *MNomLE;
gint *MNb_candidats;
gchar *Morientation;
gint *Mjour;
gint *Mmois;
gint *Mannee;
gint *Mid_cand1;
gint *Mid_cand2;
gint *Mid_cand3;




LE l2;
int t;
GtkTreeModel *model=gtk_tree_view_get_model(treeview);
if (gtk_tree_model_get_iter(model,&iter,path))
{ gtk_tree_model_get(GTK_TREE_MODEL(model),&iter,0,&Mid,1,&MNomLE,2,&MNb_candidats,3,&Morientation,4,&Mjour,5,&Mmois,6,&Mannee,7,&Mid_cand1,8,&Mid_cand2,9,&Mid_cand3,-1);
/*
strcpy(l2.NomLE,NomLE);
strcpy(l2.orientation,orientation);

l2.id=id;
l2.Nb_candidats=Nb_candidats;
l2.jour=jour;
l2.mois=mois;
l2.annee=annee;
l2.id_cand1=id_cand1;
id_cand2l2.id_cand2;
id_cand3=l2.id_cand3;*/


//if(t=Supprimer_LE("le.txt",l2.id)==1)
//afficher_LE(treeview);
}
}


void
on_button_afficher_liste_AB_clicked
                                        (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{

GtkWidget *treeview;
treeview=lookup_widget(objet_graphique,"treeview_liste_AB");
afficher_LE(treeview);
}










void
on_checkbutton_liste_AB_toggled    (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if (gtk_toggle_button_get_active(togglebutton))
strcpy( robot , "3" );
}


void
on_checkbutton_liste2_AB_toggled   (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if (gtk_toggle_button_get_active(togglebutton))
strcpy( robot , "3" );
}


void
on_button1_chercher_liste_AB_clicked
                                        (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
char id1[20];
char id2[20];
char id3[20];
char id4[20];
char date[20];
char nb_C[20];

GtkWidget *idR;
GtkWidget *A,*B,*C,*D,*E,*G,*F,*H;

char IDR[20];
int x=-1;
LE L;
int idr=0;

A=lookup_widget(objet_graphique, "A");
B=lookup_widget(objet_graphique, "B");
C=lookup_widget(objet_graphique, "C");
D=lookup_widget(objet_graphique, "D");
E=lookup_widget(objet_graphique, "E");
F=lookup_widget(objet_graphique, "F");
G=lookup_widget(objet_graphique, "G");
H=lookup_widget(objet_graphique, "H");


idR=lookup_widget(objet_graphique, "entry1_chercher_liste_AB1");
strcpy(IDR,gtk_entry_get_text(GTK_ENTRY(idR)));
idr=atoi(IDR);

FILE *f=fopen("le.txt","r+");
if(f!=NULL)
{
        while (fscanf(f,"%d %s %d %s %d %d %d %d %d %d\n",&L.id,L.NomLE,&L.Nb_candidats,L.orientation,&L.jour,&L.mois,&L.annee,&L.id_cand1,&L.id_cand2,&L.id_cand3) != EOF )
                                {
                                if(idr==L.id) x=1;                                
                                }
				fclose(f);
                                }  







LE L1=Chercher_LE(idr);
sprintf(id1,"%d",L1.id);
sprintf(id2,"%d",L1.id_cand1);
sprintf(id3,"%d",L1.id_cand2);
sprintf(id4,"%d",L1.id_cand3);
sprintf(nb_C,"%d",L1.Nb_candidats);
sprintf(date,"%d/%d/%d",L1.jour,L1.mois,L1.annee);

if(x==1)
{


gtk_label_set_text(GTK_LABEL(A),id1);
gtk_label_set_text(GTK_LABEL(B),L1.NomLE);
gtk_label_set_text(GTK_LABEL(F),id2);
gtk_label_set_text(GTK_LABEL(G),id3);
gtk_label_set_text(GTK_LABEL(H),id4);
gtk_label_set_text(GTK_LABEL(E),date);
gtk_label_set_text(GTK_LABEL(D),L1.orientation);
gtk_label_set_text(GTK_LABEL(C),nb_C);
}
else gtk_label_set_text(GTK_LABEL(A),"ID introuvable"); 



}


void
on_button_cherche_liste_AB_clicked (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
GtkWidget*n;
GtkWidget*p;
n=lookup_widget(objet_graphique, "cherche_liste");
p=lookup_widget(objet_graphique, "menu");
n= create_cherche_liste ();
gtk_widget_show(n);
}






void
on_button_rech_retour_AB_clicked       (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
GtkWidget*n;
GtkWidget*p;
n=lookup_widget(objet_graphique, "cherche_liste");
p=lookup_widget(objet_graphique, "menu");
p= create_menu();
gtk_widget_destroy(n);

}


void
on_button_stat_AB_clicked              (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
GtkWidget *treeview;
treeview=lookup_widget(objet_graphique,"treeview_stat_AB");
afficher_LE_stat(treeview);

}


void
on_radio_nb_cand3_AB_toggled           (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(togglebutton)))
nb_cand=1;


}


void
on_radio_nb_cand5_AB_toggled           (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(togglebutton)))
nb_cand=6;


}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////ONS BEN OTHMEN///////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int cc=1,ok=0,okk=0;
int cp_ob=1;
int cp_ob2=1;
int id;

void on_bv_ajouter_affiche_clicked (GtkWidget  *objet,gpointer  user_data)
{
GtkWidget*n;
GtkWidget*p;
n=lookup_widget(objet,"bv_affichage");
p=lookup_widget(objet, "bv_ajouter");
p=create_bv_ajouter();
gtk_widget_show(p);


}


void
on_bv_modifier_affiche_clicked         (GtkWidget  *objet,
                                        gpointer         user_data)
{
GtkWidget*n;
GtkWidget*p;
n=lookup_widget(objet,"bv_affichage");
p=lookup_widget(objet, "bv_modifier");
p=create_bv_modifier();
gtk_widget_show(p);


}


void
on_bv_supprimer_affiche_clicked        (GtkWidget  *objet,gpointer user_data)
{int t;
GtkWidget *tree;
tree=lookup_widget(objet,"treeview1");
if(t=supprimer("Bv.txt",id)==1)
afficher_vote(tree);


}


void
on_bv_retour_affiche_clicked  (GtkWidget  *objet,
                                        gpointer         user_data)
{
  /*
GtkWidget*n;
GtkWidget*p;
n=lookup_widget(objet,"bv_affichage");
p=lookup_widget(objet, "Page1");
p=create_Page1();
gtk_widget_show(p);
gtk_widget_destroy(n);*/
}


void
on_bv_help_affiche_clicked (GtkWidget  *objet, gpointer user_data)
{
GtkWidget*n;
GtkWidget*p;
n=lookup_widget(objet,"bv_affichage");
p=lookup_widget(objet, "dialog3");
p=create_dialog3();
gtk_widget_show(p);

}


void
on_bv_enregisster_ajouter_clicked      (GtkWidget *objet,
                                        gpointer         user_data)
{GtkWidget*id;
GtkWidget*idag;
GtkWidget*combobox;//combobox
GtkWidget*s;
GtkWidget*capE;
GtkWidget *sortie;
GtkWidget *existe;
GtkWidget *ajout;
char idd[10];
char idag1[10];
BV v,nouveau;
condidat nouveau1;
ajout=lookup_widget(objet,"dialog5");
existe=lookup_widget(objet,"dialog4");
id=lookup_widget(objet,"entry1");
strcpy(idd,gtk_entry_get_text(GTK_ENTRY(id)));
v.id=atoi(idd);
idag=lookup_widget(objet,"entry2");
strcpy(idag1,gtk_entry_get_text(GTK_ENTRY(idag)));
v.agent_BV=atoi(idag1);
combobox=lookup_widget(objet,"combobox1");
strcpy(v.gouvernorat,gtk_combo_box_get_active_text(GTK_COMBO_BOX(combobox)));
s=lookup_widget(objet,"salle");
v.salle=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(s));
capE=lookup_widget(objet,"cape");
v.cap_elec=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(capE));
v.cap_ob=cp_ob;
sortie=lookup_widget(objet,"sortie");
nouveau=chercher("Bv.txt",v.id);
nouveau1=chercher1("user.txt",v.agent_BV);
/*if(nouveau.id!=-1)
gtk_label_set_text(GTK_LABEL(sortie),"id_deja_utilise");*/
//else{
if (nouveau.id!=-1){
existe=gtk_message_dialog_new(GTK_WINDOW(user_data),GTK_DIALOG_MODAL,GTK_MESSAGE_INFO,GTK_BUTTONS_OK,"ID  existe déjà!");
switch(gtk_dialog_run(GTK_DIALOG(existe)))
{ case GTK_RESPONSE_OK:
gtk_widget_destroy(existe);
break;}}
else if (nouveau1.id==-1){
existe=gtk_message_dialog_new(GTK_WINDOW(user_data),GTK_DIALOG_MODAL,GTK_MESSAGE_INFO,GTK_BUTTONS_OK,"ID n' existe pas!");
switch(gtk_dialog_run(GTK_DIALOG(existe)))
{ case GTK_RESPONSE_OK:
gtk_widget_destroy(existe);
break;}}
else if ((strcmp(idd,"")!=0) && (strcmp(idag1,"")!=0) && (strcmp(v.gouvernorat,"")!=0) && (ok==1)){
int x=ajouter("Bv.txt",v);
if (x==1){
ajout=gtk_message_dialog_new(GTK_WINDOW(user_data),GTK_DIALOG_MODAL,GTK_MESSAGE_INFO,GTK_BUTTONS_OK,"Bureau ajoutée avec succés!");
switch(gtk_dialog_run(GTK_DIALOG(ajout)))
{
case GTK_RESPONSE_OK:
gtk_widget_destroy(ajout);
break;
}}
}
else if ((strcmp(idd,"")==0) && (strcmp(idag1,"")!=0) && (strcmp(v.gouvernorat,"")!=0)){
existe=gtk_message_dialog_new(GTK_WINDOW(user_data),GTK_DIALOG_MODAL,GTK_MESSAGE_INFO,GTK_BUTTONS_OK,"veuillez remplir l'id");
switch(gtk_dialog_run(GTK_DIALOG(existe)))
{ case GTK_RESPONSE_OK:
gtk_widget_destroy(existe);
break;}}
else if ((strcmp(idd,"")!=0) && (strcmp(idag1,"")==0) && (strcmp(v.gouvernorat,"")!=0)){
existe=gtk_message_dialog_new(GTK_WINDOW(user_data),GTK_DIALOG_MODAL,GTK_MESSAGE_INFO,GTK_BUTTONS_OK,"veuillez remplir l'id du votre agent de bureau vote");
switch(gtk_dialog_run(GTK_DIALOG(existe)))
{ case GTK_RESPONSE_OK:
gtk_widget_destroy(existe);
break;}}
else if ((strcmp(idd,"")!=0) && (strcmp(idag1,"")!=0) && (strcmp(v.gouvernorat,"")==0)){
existe=gtk_message_dialog_new(GTK_WINDOW(user_data),GTK_DIALOG_MODAL,GTK_MESSAGE_INFO,GTK_BUTTONS_OK,"veuillez remplir votre gouvernorat");
switch(gtk_dialog_run(GTK_DIALOG(existe)))
{ case GTK_RESPONSE_OK:
gtk_widget_destroy(existe);
break;}}
else if ((strcmp(idd,"")==0) && (strcmp(idag1,"")==0) && (strcmp(v.gouvernorat,"")==0)){
existe=gtk_message_dialog_new(GTK_WINDOW(user_data),GTK_DIALOG_MODAL,GTK_MESSAGE_INFO,GTK_BUTTONS_OK,"veuillez remplir vos champs");
switch(gtk_dialog_run(GTK_DIALOG(existe)))
{ case GTK_RESPONSE_OK:
gtk_widget_destroy(existe);
break;}}


}


void
on_bv_retour_ajouter_clicked (GtkWidget  *objet,
                                        gpointer         user_data)
{
GtkWidget*n;
GtkWidget*p;
n=lookup_widget(objet,"bv_affichage");
p=lookup_widget(objet, "bv_ajouter");
n=create_bv_affichage();
gtk_widget_show(n);
gtk_widget_destroy(p);
gtk_widget_destroy(n);



}


void
on_radiobutton1_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(togglebutton)))
cp_ob=3;
}


void
on_radiobutton2_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(togglebutton)))
cp_ob=5;
}


void
on_radiobutton3_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(togglebutton)))
cp_ob=7;

}









void
on_bv_recherche_modif_clicked  (GtkWidget *objet,
                                        gpointer         user_data)
{

GtkWidget*idrecherchebv;
GtkWidget*s;
int id;
char ch[20];
BV v;
s=lookup_widget(objet,"sortiemodif");
idrecherchebv=lookup_widget(objet, "entry4");
strcpy(ch,gtk_entry_get_text(GTK_ENTRY(idrecherchebv)));
id=atoi(ch);
v=chercher("Bv.txt",id);
if (v.id==-1)
gtk_label_set_text(GTK_LABEL(s),"id non trouvé");
else
{
GtkWidget *idmodif;
GtkWidget*idagmodif;
GtkWidget*combo2;
GtkWidget*s1;
GtkWidget*cap1;
GtkWidget*r4;
GtkWidget*r5;
GtkWidget*r6;
char ch1[10],ch2[10];
int x,y;
r4=lookup_widget(objet, "radiobutton4");
r5=lookup_widget(objet, "radiobutton5");
r6=lookup_widget(objet, "radiobutton6");
idmodif=lookup_widget(objet, "entry5");
idagmodif=lookup_widget(objet, "entry6");
combo2=lookup_widget(objet, "combobox2");
s1=lookup_widget(objet, "salle1");
cap1=lookup_widget(objet, "cape1");
sprintf(ch1,"%d",v.id);
sprintf(ch2,"%d",v.agent_BV);
gtk_entry_set_text(GTK_ENTRY(idmodif),ch1);
gtk_entry_set_text(GTK_ENTRY(idagmodif),ch2);
x=v.cap_elec;
gtk_spin_button_set_value(GTK_SPIN_BUTTON(cap1),x);
y=v.salle;
gtk_spin_button_set_value(GTK_SPIN_BUTTON(s1),y);
if((strcmp(v.gouvernorat,"Ariana")==0))
gtk_combo_box_set_active(GTK_COMBO_BOX(combo2),1);
else if((strcmp(v.gouvernorat,"Beja")==0))
gtk_combo_box_set_active(GTK_COMBO_BOX(combo2),2);
else if((strcmp(v.gouvernorat,"Ben_Arous")==0))
gtk_combo_box_set_active(GTK_COMBO_BOX(combo2),3);
else if((strcmp(v.gouvernorat,"Bizerte")==0))
gtk_combo_box_set_active(GTK_COMBO_BOX(combo2),4);
else if((strcmp(v.gouvernorat,"Gabes")==0))
gtk_combo_box_set_active(GTK_COMBO_BOX(combo2),5);
else if((strcmp(v.gouvernorat,"Gafsa")==0))
gtk_combo_box_set_active(GTK_COMBO_BOX(combo2),6);
else if((strcmp(v.gouvernorat,"Jendouba")==0))
gtk_combo_box_set_active(GTK_COMBO_BOX(combo2),7);
else if((strcmp(v.gouvernorat,"Kairouan")==0))
gtk_combo_box_set_active(GTK_COMBO_BOX(combo2),8);
else if((strcmp(v.gouvernorat,"Kasserine")==0))
gtk_combo_box_set_active(GTK_COMBO_BOX(combo2),9);
else if((strcmp(v.gouvernorat,"Kebili")==0))
gtk_combo_box_set_active(GTK_COMBO_BOX(combo2),10);
if(v.cap_ob==3)
gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(r4),TRUE);
else if(v.cap_ob==5)
gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(r5),TRUE);
else if(v.cap_ob==7)
gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(r6),TRUE);
}
}


void
on_bv_retour_modif_clicked  (GtkWidget *objet,
                                        gpointer         user_data)
{
GtkWidget*n;
GtkWidget*p;
n=lookup_widget(objet,"bv_affichage");
p=lookup_widget(objet, "bv_modifier");
n=create_bv_affichage();
gtk_widget_show(n);
gtk_widget_destroy(p);

}




void
on_radiobutton6_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(togglebutton)))
cp_ob2=7;

}


void
on_radiobutton5_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(togglebutton)))
cp_ob2=5;

}


void
on_radiobutton4_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(togglebutton)))
cp_ob2=3;

}


void
on_bv_enregister_modif_clicked         (GtkWidget *objet,
                                        gpointer         user_data)
{
GtkWidget *idmodif;
GtkWidget*idagmodif;
GtkWidget*combo2;
GtkWidget*sal;
GtkWidget*cap1;
GtkWidget*sortie1;
GtkWidget*ajout;
char id[10],idag1[10];
BV v;
int t;
idmodif=lookup_widget(objet, "entry5");
strcpy(id,gtk_entry_get_text(GTK_ENTRY(idmodif)));
v.id=atoi(id);
idagmodif=lookup_widget(objet, "entry6");
strcpy(idag1,gtk_entry_get_text(GTK_ENTRY(idagmodif)));

v.agent_BV=atoi(idag1);
combo2=lookup_widget(objet, "combobox2");
strcpy(v.gouvernorat,gtk_combo_box_get_active_text(GTK_COMBO_BOX(combo2)));
v.cap_ob=cp_ob;
sal=lookup_widget(objet, "salle1");
v.salle=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(sal));
cap1=lookup_widget(objet, "cape1");
v.cap_elec=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(cap1));
ajout=lookup_widget(objet, "dialog5");
t=modifier("Bv.txt",v.id,v);
if (t==1 && okk==2){
ajout=gtk_message_dialog_new(GTK_WINDOW(user_data),GTK_DIALOG_MODAL,GTK_MESSAGE_INFO,GTK_BUTTONS_OK,"Bureau modifiee avec succés!");
switch(gtk_dialog_run(GTK_DIALOG(ajout)))
{
case GTK_RESPONSE_OK:
gtk_widget_destroy(ajout);
break;
}}
else if (t!=1){
ajout=gtk_message_dialog_new(GTK_WINDOW(user_data),GTK_DIALOG_MODAL,GTK_MESSAGE_INFO,GTK_BUTTONS_OK,"error!");
switch(gtk_dialog_run(GTK_DIALOG(ajout)))
{
case GTK_RESPONSE_OK:
gtk_widget_destroy(ajout);
break;
}}

}


void
on_bv_actualiser_affiche_clicked       (GtkWidget *objet,
                                        gpointer         user_data)
{
GtkWidget *treeview;

treeview=lookup_widget(objet,"treeview1");
afficher_vote(GTK_TREE_VIEW(treeview));
}


void
on_treeview1_row_activated             (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{
GtkTreeIter iter;

BV v;
int t;

GtkTreeModel *model=gtk_tree_view_get_model(treeview);
if (gtk_tree_model_get_iter(model,&iter,path))
{ gtk_tree_model_get(GTK_TREE_MODEL(model),&iter,0,&id,-1);
}
}


void
on_cancelbutton2_clicked               (GtkWidget *objet,
                                        gpointer         user_data)
{
GtkWidget*n;
GtkWidget*p;
n=lookup_widget(objet,"bv_affichage");
p=lookup_widget(objet, "dialog3");
n=create_bv_affichage();

gtk_widget_destroy(p);
}


void
on_okbutton2_clicked                   (GtkWidget *objet,
                                        gpointer         user_data)
{
GtkWidget*n;
GtkWidget*p;
n=lookup_widget(objet,"bv_affichage");
p=lookup_widget(objet, "dialog3");
n=create_bv_affichage();

gtk_widget_destroy(p);
}


void
on_checkbutton1_clicked                (GtkWidget *objet,
                                        gpointer         user_data)
{
GtkWidget *entry;
GtkWidget *s;
GtkWidget *treeview;
treeview=lookup_widget(objet,"treeview2");
int id;
BV v;
char ch[10];
entry=lookup_widget(objet,"entryrecherche");
s=lookup_widget(objet,"sortie2");
strcpy(ch,gtk_entry_get_text(GTK_ENTRY(entry)));
id=atoi(ch);
v=chercher("Bv.txt",id);
if (v.id==-1)
gtk_label_set_text(GTK_LABEL(s),"id non trouvé");
else
rechercher(id,treeview);

}


void
on_bv_retour_recherche_clicked         (GtkWidget *objet,
                                        gpointer         user_data)
{
GtkWidget*n;
GtkWidget*p;
n=lookup_widget(objet,"bv_recherche");
p=lookup_widget(objet, "bv_affichage");
p=create_bv_affichage();
gtk_widget_show(p);
gtk_widget_destroy(n);

}





void
on_bv_recherche_affiche_clicked        (GtkWidget *objet,
                                        gpointer         user_data)
{
GtkWidget*n;
GtkWidget*p;
n=lookup_widget(objet,"bv_affichage");
p=lookup_widget(objet, "bv_recherche");
p=create_bv_recherche();
gtk_widget_show(p);

}











void
on_bv_recherche_checkbutton2_toggled   (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(togglebutton)))
cc=1;
}


void
on_bv_recherche_final_clicked          (GtkWidget      *objet,
                                        gpointer         user_data)
{
/*GtkWidget *treeview;
treeview=lookup_widget(objet,"treeview2");
GtkWidget *cape;
s=lookup_widget(objet,"sortie2");
GtkWidget *s;
BV v,r;
int cap;
if(c==1){
cape=lookup_widget(objet, "spinbutton1");
cap=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(cape));
v=chercher1("Bv.txt",cap);
if (v.id==-1)
gtk_label_set_text(GTK_LABEL(s)," non trouvé");
else
rechercher1(v,treeview);
}*/
}





void
on_bv_stat_affiche_clicked             (GtkWidget *objet,
                                        gpointer         user_data)
{

GtkWidget*n;
GtkWidget*p;
n=lookup_widget(objet,"bv_affichage");
p=lookup_widget(objet, "bv_statistique");
p=create_bv_statistique();
gtk_widget_show(p);

}





void
on_bv_reload_stat_clicked              (GtkButton       *button,
                                        gpointer         user_data)
{
float tn,te;
char tnh[10],teh[10],ch1[10];

GtkWidget*l1;
GtkWidget*l2,*tree;
l1=lookup_widget(button,"labelstat1");
l2=lookup_widget(button,"labelstat2");
tree=lookup_widget(button,"treeview3");
taux("user.txt",&tn,&te);
sprintf(tnh,"%.2f",tn);
sprintf(teh,"%.2f",te);


gtk_label_set_text(GTK_LABEL(l1),tnh);
gtk_label_set_text(GTK_LABEL(l2),teh);
afficher_stat_ons(tree);
}


void
on_ons_okay_stat_clicked  (GtkWidget      *objet,
                                        gpointer         user_data)
{
int id=0;
GtkWidget *input,*s1;
char ch[40];
char liste[10];

input=lookup_widget(objet,"entrystatons");
s1=lookup_widget(objet,"ons");
strcpy(liste,gtk_entry_get_text(GTK_ENTRY(input)));
id=atoi(liste);
/////////////////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////////////////




int x=nbe("user.txt",id);

 sprintf(ch,"%d",x);
 gtk_label_set_text(GTK_LABEL(s1),ch); 


}












void
on_bv_retour_statistique_clicked       (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget*n;
GtkWidget*p;
n=lookup_widget(button,"bv_statistique");
p=lookup_widget(button,"bv_affichage");
p=create_bv_affichage();
//gtk_widget_show(p);
gtk_widget_hide(n);

}


void
on_bv_chech_ajout_toggled (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(togglebutton)))
ok=1;
}


void
on_bv_chech_modifier_toggled           (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(togglebutton)))
okk=2;
}


void
on_accueil_bv_clicked                  (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget*n;
GtkWidget*p;
n=lookup_widget(button,"bv_affichage");
p=lookup_widget(button, "accueil");
n=create_bv_affichage();

gtk_widget_show(n);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////ZIED BEN BRAHIM///////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////





