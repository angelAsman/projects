/*
 * Treeview.h
 *
 *  Created on: Aug 9, 2015
 *      Author: Angel Asman
 */
#include <gtk/gtk.h>

GtkTreeModel *createTree();
GtkWidget *create_view_and_model(void);
void item_selected();
