#include <gtk/gtk.h>
#include <cairo.h>

#include "../graphics/options_user.h"

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    WidgetOption *widget_data = malloc(sizeof(WidgetOption));

    // Créer une fenêtre
    widget_data->window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(widget_data->window), "PPII 2023");
    gtk_container_set_border_width(GTK_CONTAINER(widget_data->window), 10);

    // initialiser les widgets de l'interface graphique
    init_option_display(widget_data);
    
    // Afficher la fenêtre
    gtk_container_add(GTK_CONTAINER(widget_data->window), widget_data->box);
    gtk_widget_show_all(widget_data->window);
    g_signal_connect(widget_data->window, "delete-event", G_CALLBACK(gtk_main_quit), NULL);

    // Démarrer la boucle principale GTK
    gtk_main();

    return 0;
}
