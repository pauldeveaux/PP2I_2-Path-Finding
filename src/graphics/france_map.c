#include <gtk/gtk.h>
#include <cairo.h>

#include "../utils/parser_csv.h"
#include "france_map.h"

#include "stdio.h"
#include "stdlib.h"



/**
 * Dessine la carte de France
 */
gboolean on_draw(GtkWidget *widget, cairo_t *cr, gpointer data) {
    if (widget == NULL || data == NULL) {}
    WidgetDataFM *widget_data = (WidgetDataFM *) data;
    // Récupérer les données
    csv_reader_t reader = create_reader_default(DATASET_PATH_STATIONS);
    station_t stations[DATASET_STATIONS_LINES];
    parse_to_station(&reader, stations);
    
    // Dessiner la France
    // Dessiner une bordure
    cairo_set_source_rgba(cr, 0,0,0,1);
    cairo_rectangle(cr, 0, 0, DRAWING_WIDTH, DRAWING_HEIGHT);
    cairo_fill (cr);
    // Dessiner un fond coloré
    cairo_set_source_rgb(cr, 0.909, 0.862, 0.792);
    int border_width = 5;
    cairo_rectangle(cr, border_width, border_width, DRAWING_WIDTH - 2*border_width, DRAWING_HEIGHT - 2*border_width);
    cairo_fill (cr);

    int idDepart = -1;
    int idArrivée = -1;
    char * b_dep = widget_data->borne_depart;
    char * b_arr = widget_data->borne_arrivee;
    // Dessiner les stations
    int radius;
    for (int i = 0; i < DATASET_STATIONS_LINES; i++) {
        if (b_dep != NULL && strcmp(stations[i].name, b_dep) == 0){
            idDepart = i;
        }else if(b_arr != NULL && strcmp(stations[i].name, b_arr) == 0){
            idArrivée = i;
        }else{
            //contour noir
            radius = 3;
            cairo_set_source_rgba(cr, 0, 0, 0,1);
            cairo_arc(cr, stations[i].longitude*3000 + 300, 2700 - stations[i].latitude*3000, radius, 0, 2 * G_PI);
            cairo_fill(cr);
            //remplissage orange
            radius = 2;
            cairo_set_source_rgba(cr, 0.7, 0.3, 0,1);
            cairo_arc(cr, stations[i].longitude*3000 + 300, 2700 - stations[i].latitude*3000, radius, 0, 2 * G_PI);
            cairo_fill(cr);
        }
    }

    //affichage départ
    if(idDepart != -1){
        //contour noir
        radius = 6;
        cairo_set_source_rgb(cr, 0, 0, 0);
        cairo_arc(cr, stations[idDepart].longitude*3000 + 300, 2700 - stations[idDepart].latitude*3000, radius, 0, 2 * G_PI);
        cairo_fill(cr);

        //remplissage vert
        radius = 5;
        cairo_set_source_rgba(cr, 0, 1, 0,1);
        cairo_arc(cr, stations[idDepart].longitude*3000 + 300, 2700 - stations[idDepart].latitude*3000, radius, 0, 2 * G_PI);
        cairo_fill(cr);
    }

    //affichage chemin
    /*if(){
            radius = 6;
            cairo_set_source_rgba(cr, 0, 0, 0,1);
            cairo_arc(cr, chemin[i].longitude*3000 + 300, 2700 - chemin[i].latitude*3000, radius, 0, 2 * G_PI);
            cairo_fill(cr);
            //remplissage bleu
            radius = 5;
            cairo_set_source_rgba(cr, 0, 0, 1,1);
            cairo_arc(cr, chemin[i].longitude*3000 + 300, 2700 - chemin[i].latitude*3000, radius, 0, 2 * G_PI);
            cairo_fill(cr);
        }*/

    //affichage arrivée
    if (idArrivée != -1){
        //contour noir
        radius = 6;
        cairo_set_source_rgb(cr, 0, 0, 0);
        cairo_arc(cr, stations[idArrivée].longitude*3000 + 300, 2700 - stations[idArrivée].latitude*3000, radius, 0, 2 * G_PI);
        cairo_fill(cr);

        //remplissage jaune
        radius = 5;
        cairo_set_source_rgba(cr, 1, 1, 0,1);
        cairo_arc(cr, stations[idArrivée].longitude*3000 + 300, 2700 - stations[idArrivée].latitude*3000, radius, 0, 2 * G_PI);
        cairo_fill(cr);
    }

    free_parsed_station(stations);
    return TRUE;
}
/*
 * Redessine un point lorsque l'on clique sur un bouton
 
void on_button_clicked_dep(GtkWidget *button, gpointer data) {
    if (button == NULL) {}
    // Récupérer la valeur sélectionnée dans la liste déroulante
    WidgetDataFM *widget_data = (WidgetDataFM *) data;
    
    GtkComboBox *combo_box = GTK_COMBO_BOX(widget_data->combo_box);
    gint active = gtk_combo_box_get_active(combo_box);

    if (active >= 0) {
        // Récupérer la chaîne de caractères correspondante
        GtkTreeModel *model = gtk_combo_box_get_model(combo_box);
        GtkTreeIter iter;
        gtk_tree_model_iter_nth_child(model, &iter, NULL, active);
        gchar *selected_value;
        gtk_tree_model_get(model, &iter, 0, &selected_value, -1);
        g_print("Selected value: %s\n", selected_value);
        DEPART = atoi(selected_value);
        GtkWidget *drawing_area = GTK_WIDGET(widget_data->drawing_area);
        // Met à jour la zone de dessin
        gtk_widget_queue_draw_area(drawing_area, 0, 0, DRAWING_WIDTH, DRAWING_HEIGHT);
    }  
}*/

void init_france_map(WidgetDataFM *widget_data){
    // Créer la box principale
    widget_data->box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);

    // Créer l'image de la France
    widget_data->drawing_area = gtk_drawing_area_new();
    gtk_widget_set_size_request(widget_data->drawing_area, DRAWING_WIDTH, DRAWING_HEIGHT);
    g_signal_connect(G_OBJECT(widget_data->drawing_area), "draw", G_CALLBACK(on_draw), widget_data);
    gtk_box_pack_start(GTK_BOX(widget_data->box), widget_data->drawing_area, FALSE, FALSE, 0);

    //intialisation des bornes
    widget_data->borne_depart = malloc(sizeof(char)*50);
    widget_data->borne_depart = "--";
    widget_data->borne_arrivee = malloc(sizeof(char)*50);
    widget_data->borne_arrivee = "--";    
}


void france_map_quit(GtkWidget *window, int *data) {
    if (window == NULL) {}
    WidgetDataFM *widget_data = (WidgetDataFM *) data;
    free(widget_data->borne_depart);
    free(widget_data->borne_arrivee);

    gtk_main_quit();
}
