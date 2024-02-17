#include <gtk/gtk.h>
#include <string.h>
#include <ctype.h>

#include "../utils/parser_csv.h"
#ifndef OPTIONS_USER_H
#define OPTIONS_USER_H


typedef struct {
    GtkWidget *window;
    GtkWidget *box;
    GtkWidget *grid;
    GtkWidget *label1;
    GtkWidget *spin1;
    GtkWidget *label2;
    GtkWidget *spin2;
    GtkWidget *label3;
    GtkWidget *spin3;
    GtkWidget *label4;
    GtkWidget *spin4;
    GtkWidget *label5;
    GtkWidget *radio_button_box;
    GtkWidget *radio_button_yes, *radio_button_no;
}WidgetOption;
/**
 * @brief initialise les options de l'utilisateur
*/
void init_option_display(WidgetOption *wd_options);

#endif // OPTIONS_USER_H