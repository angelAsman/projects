/*
 * display.c
 *
 *  Created on: Aug 8, 2015
 *      Author: Angel Asman
 */
#include <gtk/gtk.h>

void display(GtkWidget *window, GtkWidget *scroll, GtkWidget *hpaned) {

	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scroll),
			GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
	gtk_container_add(GTK_CONTAINER(scroll), hpaned);

	gtk_container_add(GTK_CONTAINER(window), scroll);
	gtk_widget_show_all(window);


}


