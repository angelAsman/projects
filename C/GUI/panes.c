/*
 * panes.c
 *
 *  Created on: Aug 7, 2015
 *      Author: Angel Asman
 *
 *  This sets up the three resizable panes. In the window container
 */
#include <gtk/gtk.h>
#include "Treeview.h"
#include "listview.h"
#include "textview.h"
#include <stdlib.h>
#include <unistd.h>

/* Inserts a widget into a scroll window pane
 * param: scroll, a widget for scrolled window
 * param: button, a widget that will be inserted into scroll window
 */

void addScroll(GtkWidget *scroll, GtkWidget *buttons) {
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scroll),
			GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

	gtk_container_add(GTK_CONTAINER(scroll), buttons);

}
/* Creates panes that are resizable and children of each other
 * param: window, a widget window container
 * param: hpane, a widget for the horizontal pane
 * param: vpane, a widget for the vertical pane
 */

void makePanes(GtkWidget *window, GtkWidget *hpane, GtkWidget *vpane) {


	char *path = "";
	GtkWidget *view, *listview, *textview1, *textview2, *textview3, *hbox;
	hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);

	view = create_view_and_model();
	listview = createAndview(path);
	//for intilization only
/*	textview1 = textViewCreate(path);
	textview2 = textViewCreate(path);
	textview3 = textViewCreate(path);
	gtk_box_pack_start((GTK_BOX(hbox)), textview1,TRUE,TRUE, 0);
	gtk_box_pack_start((GTK_BOX(hbox)), textview2,TRUE,TRUE, 0);
	gtk_box_pack_start((GTK_BOX(hbox)), textview3,TRUE,TRUE, 0);*/
	//Handeling
	GtkTreeSelection *selection, *listSelection;
	selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(view));
	listSelection = gtk_tree_view_get_selection(GTK_TREE_VIEW(listview));
	// connect the selection callback function
	g_signal_connect(G_OBJECT(selection), "changed", G_CALLBACK(item_selected),
			listview);

	g_signal_connect(G_OBJECT(listSelection), "changed",
			G_CALLBACK(file_selected), hbox);


	GtkWidget *button1scroll = gtk_scrolled_window_new(NULL, NULL);
	GtkWidget *button2scroll = gtk_scrolled_window_new(NULL, NULL);
	GtkWidget *button3scroll = gtk_scrolled_window_new(NULL, NULL);

	addScroll(button1scroll, view);
	addScroll(button2scroll, listview);
	addScroll(button3scroll, hbox);


	/* Add button scrolls as children to coorespnding gtk panes
	 */
	gtk_paned_pack1(GTK_PANED(hpane), button1scroll, TRUE, FALSE);
	gtk_paned_pack2(GTK_PANED(hpane), vpane, TRUE, FALSE);
	gtk_paned_pack1(GTK_PANED(vpane), button2scroll, TRUE, FALSE);
	gtk_paned_pack2(GTK_PANED(vpane), button3scroll, TRUE, FALSE);

}
