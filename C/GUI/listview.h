/*
 * listview.h
 *
 *  Created on: Aug 12, 2015
 *      Author: angel
 */
#include <gtk/gtk.h>

GtkTreeModel *createListTree(char *filename);
GtkWidget *createAndview(char *filename);
void file_selected(GtkWidget *selection, gpointer data);
gint sort_last_names(GtkTreeModel *model, GtkTreeIter *a, GtkTreeIter *b,
		gpointer data);



