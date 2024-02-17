#include <gtk/gtk.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "../utils/parser_csv.h"
#include "france_map.h"
#include "search_button.h"


/**
 * @brief Vérifie si la chaîne de caractères theString commence par la chaîne de caractères theBase en ignorant la casse
 * @param theString La chaîne de caractères à vérifier
 * @param theBase La chaîne de caractères à rechercher
 * @return true si la chaîne de caractères theString commence par la chaîne de caractères theBase, false sinon
*/
bool startsWith( const char * theString, const char * theBase ) {
    char* str = malloc(sizeof(char) * strlen(theString) + 1);
    char* base = malloc(sizeof(char) * strlen(theBase) + 1);
    strcpy(str, theString);
    strcpy(base, theBase);
    for (int i = 0; str[i] != '\0'; i++) {
        str[i] = tolower(str[i]);
    }
    for (int i = 0; base[i] != '\0'; i++) {
        base[i] = tolower(base[i]);
    }
    bool retour = strncmp( str, base, strlen( base ) ) == 0;
    free(str);
    free(base);
    return retour;
}

WidgetLabel* init_label()
{
    WidgetLabel *widget_label = malloc(sizeof(WidgetLabel));
    widget_label->event_box = gtk_event_box_new();
    widget_label->label = gtk_label_new("");
    gtk_container_add(GTK_CONTAINER(widget_label->event_box), widget_label->label);
    return widget_label;
}

/**
 * @brief Fonction appelée lorsqu'on clique sur le bouton "Rechercher"
 * @param button Le bouton "Rechercher"
 * @param user_data Les données utilisateur (ici, le champ de saisie de texte)
*/
void on_search_button_clicked(GtkButton *button, gpointer data)
{
    if (button == NULL) return;

    WidgetDataSB *widget_data_sb = (WidgetDataSB *) data;
    // Récupérer les différents widgets
    GtkEntry *search_entry = GTK_ENTRY(widget_data_sb->search_entry);
    GtkLabel *label1 = GTK_LABEL(widget_data_sb->label1->label);
    GtkLabel *label2 = GTK_LABEL(widget_data_sb->label2->label);
    GtkLabel *label3 = GTK_LABEL(widget_data_sb->label3->label);
    GtkLabel *label4 = GTK_LABEL(widget_data_sb->label4->label);
    GtkLabel *label5 = GTK_LABEL(widget_data_sb->label5->label);

    // Récupérer le texte saisi dans le champ de saisie
    const char *search_text = gtk_entry_get_text(search_entry);

    // Lancer la recherche avec le texte saisi
    csv_reader_t reader = create_reader_default(DATASET_PATH_STATIONS);
    station_t stations[DATASET_STATIONS_LINES];
    station_t station_afficher[5];
    parse_to_station(&reader, stations);
    int j = 0;
    for (int i = 0; i < DATASET_STATIONS_LINES; i++)
    {
        if (startsWith(stations[i].name, search_text)){
            if (j<5){
                station_afficher[j] = stations[i];
            }
            j++;
        }
    }
    // Afficher les résultats
    switch (j)
    {
    case 0:
        gtk_label_set_text(label1, "Aucun résultat");
        gtk_label_set_text(label2, "");
        gtk_label_set_text(label3, "");
        gtk_label_set_text(label4, "");
        gtk_label_set_text(label5, "");
        break;
    case 1:
        //affichage chaine de caractères
        gtk_label_set_text(label1, station_afficher[0].name);
        gtk_label_set_text(label2, "-");
        gtk_label_set_text(label3, "-");
        gtk_label_set_text(label4, "-");
        gtk_label_set_text(label5, "-");
        break;
    case 2:
       //affichage chaine de caractères
        gtk_label_set_text(label1, station_afficher[0].name);
        gtk_label_set_text(label2, station_afficher[1].name);
        gtk_label_set_text(label3, "-");
        gtk_label_set_text(label4, "-");
        gtk_label_set_text(label5, "-");
        break;
    case 3:
        //affichage chaine de caractères
        gtk_label_set_text(label1, station_afficher[0].name);
        gtk_label_set_text(label2, station_afficher[1].name);
        gtk_label_set_text(label3, station_afficher[2].name);
        gtk_label_set_text(label4, "-");
        gtk_label_set_text(label5, "-");
        break;
    case 4:
        //affichage chaine de caractères
        gtk_label_set_text(label1, station_afficher[0].name);
        gtk_label_set_text(label2, station_afficher[1].name);
        gtk_label_set_text(label3, station_afficher[2].name);
        gtk_label_set_text(label4, station_afficher[3].name);
        gtk_label_set_text(label5, "-");
        break;
    case 5:
        //affichage chaine de caractères
        gtk_label_set_text(label1, station_afficher[0].name);
        gtk_label_set_text(label2, station_afficher[1].name);
        gtk_label_set_text(label3, station_afficher[2].name);
        gtk_label_set_text(label4, station_afficher[3].name);
        gtk_label_set_text(label5, station_afficher[4].name);
        break;
    default:
        //affichage chaine de caractères
        gtk_label_set_text(label1, station_afficher[0].name);
        gtk_label_set_text(label2, station_afficher[1].name);
        gtk_label_set_text(label3, station_afficher[2].name);
        gtk_label_set_text(label4, station_afficher[3].name);
        char* txt5 = malloc(sizeof(char) * 100);
        sprintf(txt5, "et %d stations supplémentaires ...", j);
        gtk_label_set_text(label5, txt5);
        break;
    }
    free_parsed_station(stations);
}

void init_search_button(WidgetDataSB *widget_data){
    widget_data->search_entry  = gtk_entry_new();
    widget_data->search_button = gtk_button_new_with_label("Rechercher");

    // Création d'un GtkGrid pour ajouter les deux boxes
    widget_data->grid = gtk_grid_new();

    // Créer une boîte horizontale pour les éléments de la barre de recherche
    widget_data->search_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_box_pack_start(GTK_BOX(widget_data->search_box), widget_data->search_entry, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(widget_data->search_box), widget_data->search_button, FALSE, FALSE, 0);

    // Création des labels
    widget_data->label1 = init_label();
    widget_data->label2 = init_label(); 
    widget_data->label3 = init_label();
    widget_data->label4 = init_label();
    widget_data->label5 = init_label();   

    // Création d'un conteneur vertical pour les labels
    widget_data->box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_set_border_width(GTK_CONTAINER(widget_data->box), 10);
    gtk_box_pack_start(GTK_BOX(widget_data->box), widget_data->label1->event_box, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(widget_data->box), widget_data->label2->event_box, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(widget_data->box), widget_data->label3->event_box, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(widget_data->box), widget_data->label4->event_box, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(widget_data->box), widget_data->label5->event_box, FALSE, FALSE, 0);

    gtk_grid_attach(GTK_GRID(widget_data->grid), widget_data->box, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(widget_data->grid), widget_data->search_box, 0, 0, 1, 1);
    

    // Connecter les signaux
    g_signal_connect(widget_data->search_button, "clicked", G_CALLBACK(on_search_button_clicked), widget_data);  
    /*g_signal_connect(wd->wsb->label1->event_box, "button_press_event", G_CALLBACK(on_label_clicked), wd->wfm);
    g_signal_connect(wd->wsb->label2->event_box, "button_press_event", G_CALLBACK(on_label_clicked), wd->wfm);
    g_signal_connect(wd->wsb->label3->event_box, "button_press_event", G_CALLBACK(on_label_clicked), wd->wfm);
    g_signal_connect(wd->wsb->label4->event_box, "button_press_event", G_CALLBACK(on_label_clicked), wd->wfm);
    g_signal_connect(wd->wsb->label5->event_box, "button_press_event", G_CALLBACK(on_label_clicked), wd->wfm);
    g_signal_connect(wd->window, "delete-event", G_CALLBACK(gtk_main_quit), NULL);
    */

}

void search_button_quit(GtkWidget *window, int *data) {
    if (window == NULL) {}
    WidgetDataSB *widget_data_sb = (WidgetDataSB *) data;
    free(widget_data_sb->label1);
    free(widget_data_sb->label2);
    free(widget_data_sb->label3);
    free(widget_data_sb->label4);
    free(widget_data_sb->label5);


    gtk_main_quit();
}
