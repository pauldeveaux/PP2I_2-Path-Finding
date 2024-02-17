#include <gtk/gtk.h>
#include "options_user.h"


void init_option_display(WidgetOption *widget){
    widget->box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    widget->grid = gtk_grid_new();
    // Créer un GtkAdjustment pour gérer les valeurs du SpinButton
    GtkAdjustment *adjustment = gtk_adjustment_new(1.0, 1.0, 100.0, 1.0, 1.0, 0.0);
    widget->spin1 = gtk_spin_button_new(adjustment, 1.0, 0);
    widget->spin2 = gtk_spin_button_new(adjustment, 1.0, 0);
    widget->spin3 = gtk_spin_button_new(adjustment, 1.0, 0);
    GtkAdjustment *adjustment2 = gtk_adjustment_new(1.0, 1.0, 120.0, 1.0, 1.0, 0.0);
    widget->spin4 = gtk_spin_button_new(adjustment2, 1.0, 0);
    widget->label1 = gtk_label_new("Batterie minimal souhaité :");
    widget->label2 = gtk_label_new(", maximale :");
    widget->label3 = gtk_label_new("Batterie actuelle :");
    widget->label4 = gtk_label_new("Temps de recharge maximum souhaité (min):");
    widget->label5 = gtk_label_new("Prendre en compte les stations payantes ? :");

    widget->radio_button_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_container_set_border_width(GTK_CONTAINER(widget->radio_button_box), 10);
    widget->radio_button_yes = gtk_radio_button_new_with_label(NULL, "Oui");
    widget->radio_button_no = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(widget->radio_button_yes), "Non");
    gtk_box_pack_start(GTK_BOX(widget->radio_button_box), widget->radio_button_yes, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(widget->radio_button_box), widget->radio_button_no, TRUE, TRUE, 0);

    gtk_grid_attach(GTK_GRID(widget->grid), widget->label1, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(widget->grid), widget->spin1, 1, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(widget->grid), widget->label2, 2, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(widget->grid), widget->spin2, 3, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(widget->grid), widget->label3, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(widget->grid), widget->spin3, 1, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(widget->grid), widget->label4, 0, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(widget->grid), widget->spin4, 1, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(widget->grid), widget->label5, 0, 3, 1, 1);
    gtk_grid_attach(GTK_GRID(widget->grid), widget->radio_button_box, 1, 3, 1, 1);



    gtk_box_pack_start(GTK_BOX(widget->box), widget->grid, TRUE, TRUE, 0);
}
