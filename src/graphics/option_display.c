#include <gtk/gtk.h>
#include "option_display.h"


void init_option_display(WidgetOption *widget){
    widget->box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    widget->grid = gtk_grid_new();
    gtk_box_pack_start(GTK_BOX(widget->box), widget->grid, TRUE, TRUE, 0);
    widget->titre = gtk_label_new("Options");
    gtk_grid_attach(GTK_GRID(widget->grid), widget->titre, 0, 0, 2, 1);
    widget->lbl_dep = gtk_label_new("Borne de départ");
    gtk_grid_attach(GTK_GRID(widget->grid), widget->lbl_dep, 0, 1, 1, 1);
    widget->lbl_dep_voulu = gtk_label_new(" - ");
    gtk_grid_attach(GTK_GRID(widget->grid), widget->lbl_dep_voulu, 0, 2, 1, 1);
    widget->lbl_arr = gtk_label_new("Borne d'arrivée");
    gtk_grid_attach(GTK_GRID(widget->grid), widget->lbl_arr, 1, 1, 1, 1);
    widget->lbl_arr_voulu = gtk_label_new(" - ");
    gtk_grid_attach(GTK_GRID(widget->grid), widget->lbl_arr_voulu, 1, 2, 1, 1);
    widget->lbl_min_bat = gtk_label_new("Batterie minimale");
    gtk_grid_attach(GTK_GRID(widget->grid), widget->lbl_min_bat, 2, 1, 1, 1);
    widget->lbl_min_voulu = gtk_label_new(" - ");
    gtk_grid_attach(GTK_GRID(widget->grid), widget->lbl_min_voulu, 2, 2, 1, 1);
    widget->lbl_max_bat = gtk_label_new("Batterie maximale");
    gtk_grid_attach(GTK_GRID(widget->grid), widget->lbl_max_bat, 3, 1, 1, 1);
    widget->lbl_max_voulu = gtk_label_new(" - ");
    gtk_grid_attach(GTK_GRID(widget->grid), widget->lbl_max_voulu, 3, 2, 1, 1);
    widget->lbl_current_bat = gtk_label_new("Batterie actuelle");
    gtk_grid_attach(GTK_GRID(widget->grid), widget->lbl_current_bat, 4, 1, 1, 1);
    widget->lbl_current_voulu = gtk_label_new(" - ");
    gtk_grid_attach(GTK_GRID(widget->grid), widget->lbl_current_voulu, 4, 2, 1, 1);
    widget->lbl_tps_recharge = gtk_label_new("Temps de recharge maximum");
    gtk_grid_attach(GTK_GRID(widget->grid), widget->lbl_tps_recharge, 5, 1, 1, 1);
    widget->lbl_tps_recharge_voulu = gtk_label_new(" - ");
    gtk_grid_attach(GTK_GRID(widget->grid), widget->lbl_tps_recharge_voulu, 5, 2, 1, 1);
    widget->lbl_station_payante = gtk_label_new("Station payante incluse ?");
    gtk_grid_attach(GTK_GRID(widget->grid), widget->lbl_station_payante, 6, 1, 1, 1);
    widget->lbl_station_payante_voulu = gtk_label_new(" - ");
    gtk_grid_attach(GTK_GRID(widget->grid), widget->lbl_station_payante_voulu, 6, 2, 1, 1);
    gtk_grid_set_column_spacing(GTK_GRID(widget->grid), 10);
    gtk_grid_set_row_spacing(GTK_GRID(widget->grid), 10);
}

void set_labels(char** labels, WidgetOption *widget){
    gtk_label_set_text(widget->lbl_dep_voulu, labels[0]);
    gtk_label_set_text(widget->lbl_arr_voulu, labels[1]);
    gtk_label_set_text(widget->lbl_min_voulu, labels[2]);
    gtk_label_set_text(widget->lbl_max_voulu, labels[3]);
    gtk_label_set_text(widget->lbl_current_voulu, labels[4]);
    gtk_label_set_text(widget->lbl_tps_recharge_voulu, labels[5]);
    gtk_label_set_text(widget->lbl_station_payante_voulu, labels[6]);
}
