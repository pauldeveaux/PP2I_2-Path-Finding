#include <gtk/gtk.h>
#include <string.h>
#include <ctype.h>
#include "../utils/parser_csv.h"
#include "../graphics/france_map.h"
#include "../graphics/search_button.h"


/* Fonction permettant de tester le bouton de recherche */
int main(int argc, char *argv[])
{
    // Initialiser GTK+
    gtk_init(&argc, &argv);

    //Initialiser la structure WidgetsData
    WidgetDataSB *widget_data = malloc(sizeof(WidgetDataSB));

    // Créer une fenêtre
    widget_data->window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    
    // Initialiser les widgets de l'interface graphique
    init_search_button(widget_data);
    gtk_container_add(GTK_CONTAINER(widget_data->window), widget_data->grid);

    // Afficher la fenêtre et lancer la boucle d'événements GTK+
    g_signal_connect(widget_data->window, "delete-event", G_CALLBACK(search_button_quit), widget_data);
    gtk_widget_show_all(widget_data->window);
    gtk_main();

    return 0;
}
