/*gtkMain.c
 * Created by: Angel Asman
 *
 * Version 1
 *
 * This is a file browser interface created with gtk 3.0
 *
 */

#include <gtk/gtk.h>
#include "panes.h"
#include "display.h"
static void destroy(GtkWidget*, gpointer);

/*This function is the main gtk loop that runs the graphical user interface.
 * The GUI is a file browser that displays different information on 3 separate panes
 */

int main(int argc, char *argv[]) {

	GtkWidget *window, *hpaned, *vpaned, *scroll;
	gtk_init(&argc, &argv);
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "File Browser");
	gtk_container_set_border_width(GTK_CONTAINER(window), 10);
	gtk_widget_set_size_request(window, 500, 300);

	g_signal_connect(G_OBJECT (window), "destroy", G_CALLBACK (destroy), NULL);
	/*main scrolled window*/
	scroll = gtk_scrolled_window_new(NULL, NULL);
	hpaned = gtk_paned_new(GTK_ORIENTATION_HORIZONTAL);
	vpaned = gtk_paned_new(GTK_ORIENTATION_VERTICAL);

	makePanes(window, hpaned, vpaned);
	display(window,scroll,hpaned);

	gtk_main();
	return 0;
}

static void destroy(GtkWidget *window, gpointer data) {
	gtk_main_quit();
}
