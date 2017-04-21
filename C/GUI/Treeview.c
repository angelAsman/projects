/*
 * Treeview.c
 *
 *  Created on: Aug 9, 2015
 *      Author: angel
 *
 * This creates a gtk treeview for directorys in a file system.
 */

#include <gtk/gtk.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <stdbool.h>
#include "listview.h"
#include "pathCreate.h"

#define SIZE 1024

enum {
	IMAGE = 0, FILE_NAME, GHOST, NUM_COLS,
};

/* Traverses the directory and subdirectories
 * and inserts them into the treeview
 * param: parent, The parent for the iter
 * param: path, the file path
 * param: image, the image to be inserted
 * param: store, the treeview store
 * param: iter, the iter of the treestore
 */

void dirwalk(GtkTreeIter *parent, char* path, GdkPixbuf*image,
		GtkTreeStore *store, GtkTreeIter *iter) {

	struct dirent *directory;
	DIR *dp;

	if ((dp = opendir(path)) != NULL) {
		while ((directory = readdir(dp)) != NULL) {
			if (directory->d_type == DT_DIR && directory->d_type == DT_DIR
					&& strcmp(directory->d_name, ".") != 0
					&& strcmp(directory->d_name, "..") != 0) {

				char Path[SIZE];
				createPath(Path,path,directory->d_name);
				gtk_tree_store_append(store, iter, parent);
				gtk_tree_store_set(store, iter, IMAGE, image, FILE_NAME,
						directory->d_name, GHOST, Path, -1);

				dirwalk(iter, Path, image, store, iter);

			}

		}
		closedir(dp);
	}

}

/* Creates the intial treeview and calls dirwalk
 * return: the treeview model
 */
GtkTreeModel *
createTree() {
	GtkTreeStore *store;
	GtkTreeIter iter;
	GdkPixbuf *image;

	store = gtk_tree_store_new(NUM_COLS, GDK_TYPE_PIXBUF, G_TYPE_STRING,
			G_TYPE_STRING);
	image = gdk_pixbuf_new_from_file_at_size("folder_black.png", 30, 30,
			GDK_PIXBUF_ERROR_CORRUPT_IMAGE);

	char *home;
	home = getenv("HOME");

	dirwalk(NULL, home, image, store, &iter);

	return GTK_TREE_MODEL(store);
}

/* Creates the columns for the treeview
 * return: the treeview store
 */
GtkWidget *
create_view_and_model(void) {
	GtkCellRenderer *renderer;
	GtkTreeModel *model;
	GtkWidget *view;
	GtkTreeViewColumn *column;

	view = gtk_tree_view_new();

	//	 --- Column #1 ---

	renderer = gtk_cell_renderer_pixbuf_new();
	column = gtk_tree_view_column_new_with_attributes("", renderer, "pixbuf",
			IMAGE, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(view), column);

	// --- Column #2 ---

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Directory", renderer,
			"text", FILE_NAME, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(view), column);

	//--- Ghost column ---

	column = gtk_tree_view_column_new_with_attributes("", NULL, "text", GHOST,
			NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(view), column);

	model = createTree();

	gtk_tree_view_set_model(GTK_TREE_VIEW(view), model);

	g_object_unref(model);

	return view;
}

/* A callback for the directory selected
 * param: selection, is what directory was selected
 * param: data, user data
 */
void item_selected(GtkWidget *selection, gpointer data) {
	GtkTreeModel *model;
	GtkTreeIter iter;
	if (gtk_tree_selection_get_selected(GTK_TREE_SELECTION(selection), &model,
			&iter)) {
		gchar *name;
		gtk_tree_model_get(model, &iter, GHOST, &name, -1);
		GtkTreeModel *newModel;
		GtkWidget *view = data;
		newModel = createListTree(name);
		gtk_tree_view_set_model(GTK_TREE_VIEW(view), newModel);


	}
}
