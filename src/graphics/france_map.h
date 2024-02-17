#include <gtk/gtk.h>
#include <cairo.h>

#include "../utils/parser_csv.h"

#ifndef FRANCE_MAP_H
#define FRANCE_MAP_H

/**
 * @brief Structure contenant les widgets de l'interface graphique
 * @param window La fenêtre
 * @param box La boîte
 * @param drawing_area La zone de dessin
 * @param list_store Le modèle de données
 * @param combo_box La liste déroulante
 * @param renderer Le rendu
 * @param button Le bouton "Rechercher"
*/
typedef struct {
    GtkWidget *window;
    GtkWidget *box;
    GtkWidget *drawing_area;
    GtkListStore *list_store;
    GtkWidget *combo_box;
    GtkCellRenderer *renderer;
    GtkWidget *button;
    char* borne_depart;
    char* borne_arrivee;
} WidgetDataFM;

/**
 * @brief Fonction appelée pour redessinerla carte
 * @param widget La zone de dessin
 * @param cr Le contexte de rendu
 * @param user_data Les données utilisateur
*/
gboolean on_draw(GtkWidget *widget, cairo_t *cr, gpointer data);

/**
 * @brief Fonction qui initialise les widgets de l'interface graphique
 * @param widget_data Les widgets de l'interface graphique
*/
void init_france_map(WidgetDataFM *widget_data);

/**
 * @brief Fonction qui free pour éviter une fuite mémoire
 * lors de la fermeture de la windows
 */
void france_map_quit(GtkWidget *window, int *data);

#define DRAWING_WIDTH 850
#define DRAWING_HEIGHT 550
#endif
