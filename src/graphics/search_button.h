#include <gtk/gtk.h>
#include <string.h>
#include <ctype.h>

#include "../utils/parser_csv.h"
#ifndef SEARCH_BUTTON_H
#define SEARCH_BUTTON_H


/**
 * @brief Structure contenant les widgets pour un label
 * @param event_box La boîte d'événement
 * @param label Le label
 */
typedef struct{
    GtkEventBox *event_box;
    GtkWidget *label;
} WidgetLabel;

/**
 * @brief Structure contenant les widgets de l'interface graphique
 * @param window La fenêtre
 * @param search_entry Le champ de saisie de texte
 * @param search_button Le bouton "Rechercher"
 * @param grid La grille
 * @param search_box La boîte de recherche
 * @param label1 Le label 1
 * @param label2 Le label 2
 * @param label3 Le label 3
 * @param label4 Le label 4
 * @param label5 Le label 5
 * @param box La boîte des labels
*/
typedef struct{
    GtkWidget *window;
    GtkWidget *search_entry;
    GtkWidget *search_button;
    GtkWidget *grid;
    GtkWidget *search_box;
    WidgetLabel *label1;
    WidgetLabel *label2;
    WidgetLabel *label3;
    WidgetLabel *label4;
    WidgetLabel *label5;
    GtkWidget *box;
} WidgetDataSB;



/**
 * @brief Vérifie si la chaîne de caractères theString commence par la chaîne de caractères theBase en ignorant la casse
 * @param theString La chaîne de caractères à vérifier
 * @param theBase La chaîne de caractères à rechercher
 * @return true si la chaîne de caractères theString commence par la chaîne de caractères theBase, false sinon
*/
bool startsWith( const char * theString, const char * theBase );

/**
 * @brief Fonction appelée lorsqu'on clique sur le bouton "Rechercher"
 * @param button Le bouton "Rechercher"
 * @param user_data Les données utilisateur (ici, le champ de saisie de texte)
*/
void on_search_button_clicked(GtkButton *button, gpointer data);

/**
 * @brief Initialise les widgets de l'interface graphique
 * @param widget_data Les widgets de l'interface graphique
 * @return void
*/
void init_search_button(WidgetDataSB *widget_data);

/**
 * @brief Initialise un label
 * @return Le label initialisé
*/
WidgetLabel* init_label();

/**
 * @brief Fonction qui free pour éviter une fuite mémoire
 * lors de la fermeture de la windows
 */
void search_button_quit(GtkWidget *window, int *data);

#endif 

