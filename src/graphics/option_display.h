#include <gtk/gtk.h>


#ifndef OPTION_SELECTION_H
#define OPTION_SELECTION_H

/**
 * @brief Structure contenant les widgets de la fenêtre de sélection des options
*/
typedef struct{
    GtkWidget *window;
    GtkWidget *box;
    GtkWidget *grid;
    GtkWidget *titre;
    GtkWidget *lbl_dep;
    GtkWidget *lbl_dep_voulu;
    GtkWidget *lbl_arr;
    GtkWidget *lbl_arr_voulu;
    GtkWidget *lbl_min_bat;
    GtkWidget *lbl_min_voulu;
    GtkWidget *lbl_max_bat;
    GtkWidget *lbl_max_voulu;
    GtkWidget *lbl_current_bat;
    GtkWidget *lbl_current_voulu;
    GtkWidget *lbl_tps_recharge;
    GtkWidget *lbl_tps_recharge_voulu;
    GtkWidget *lbl_station_payante;
    GtkWidget *lbl_station_payante_voulu;
} WidgetOption;

/**
 * @brief fonction qui initialise les widgets de la fenêtre de sélection des options
 * @param widget_option pointeur sur la structure contenant les widgets de la fenêtre de sélection des options
*/
void init_option_display(WidgetOption *widget_option);

/**
 * @brief fonction qui permet de mettre à jour les labels de la fenêtre de sélection des options
 * @param labels tableau de chaînes de caractères contenant les valeurs des options
*/
void set_labels(char** labels, WidgetOption *widget_option);

#endif
