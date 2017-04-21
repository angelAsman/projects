/*
 * listview.c
 *
 *  Created on: Aug 12, 2015
 *      Author: Angel Asman
 *
 *
 *      Creates the file list inside each directory
 */

#include <gtk/gtk.h>
#include <string.h>
#include <sys/stat.h>
#include "textview.h"
#include "pathCreate.h"

enum {
	IMAGE = 0, NAME, SIZE, DATE, GHOST, NUM_COLS,
};

#define BUFF 1024

/* This function readable_fs is directly copied from the site:
 * Program and Design,
 * http://programanddesign.com/cpp/human-readable-file-size-in-c/
 * From an article titled "Human-readable file size in C". It was created by Mark.
 *
 * param: double size, the size of file in bytes
 * param: char buff,  the buffer to store the coverted bytes.
 * return: the buffer with converted bytes
 */
char* readable_fs(double size, char *buf) {
	int i = 0;
	const char* units[] =
			{ "B", "kB", "MB", "GB", "TB", "PB", "EB", "ZB", "YB" };
	while (size > 1024) {
		size /= 1024;
		i++;
	}
	sprintf(buf, "%.*f %s", i, size, units[i]);
	return buf;
}

/* Sorts the names for each column by comparing iters
 * param: model, the tree model
 * param: a, the tree iterator
 * param: b, the tree iterator
 * param: data, the user data
 * return: the sorted column
 */
gint sort(GtkTreeModel *model, GtkTreeIter *a, GtkTreeIter *b, gpointer data) {
	gchar *name1, *name2;
	gtk_tree_model_get(model, a, NAME, &name1, -1);
	gtk_tree_model_get(model, b, NAME, &name2, -1);
	int order = strcmp(name1, name2);
	g_free(name1);
	g_free(name2);
	return -order;
}

/* Creates the tree model for list store
 * param: filename, the file pathway
 * return: list store model
 */
GtkTreeModel *
createListTree(char *filename) {
	GtkListStore *store;
	GdkPixbuf *image, *image2, *image3;
	GtkTreeIter iter;

	store = gtk_list_store_new(NUM_COLS, GDK_TYPE_PIXBUF, G_TYPE_STRING,
	G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
	image = gdk_pixbuf_new_from_file_at_size("rocko.png", 25, 25,
			GDK_PIXBUF_ERROR_CORRUPT_IMAGE);

	image2 = gdk_pixbuf_new_from_file_at_size("kitten.png", 25, 25,
			GDK_PIXBUF_ERROR_CORRUPT_IMAGE);

	image3 = gdk_pixbuf_new_from_file_at_size("yoshi.png", 25, 25,
			GDK_PIXBUF_ERROR_CORRUPT_IMAGE);

	struct dirent *directory;
	struct stat st;
	double size;
	char sizeBuffer[1024] = { 0 };
	char date[30];
	DIR *dp;
	// open file and read contents
	if ((dp = opendir(filename)) != NULL) {
		while ((directory = readdir(dp)) != NULL) {
			if (directory->d_type == DT_REG && directory->d_type == DT_REG
					&& strcmp(directory->d_name, ".") != 0
					&& strcmp(directory->d_name, "..") != 0) {

				// create absolute path
				char Path[BUFF];
				createPath(Path, filename,directory->d_name);
				stat(Path, &st);
				size = st.st_size;
				readable_fs(size, sizeBuffer);
				strftime(date, 30, "%d-%m-%y %X", localtime(&(st.st_ctime)));
				// for image selection
				if ((st.st_mode > 0) && (S_IEXEC & st.st_mode)) {
					gtk_list_store_append(store, &iter);
					gtk_list_store_set(store, &iter, IMAGE, image2, NAME,
							directory->d_name, SIZE, sizeBuffer, DATE, date,
							GHOST, Path, -1);

				} else if ((st.st_mode > 0) && (S_IREAD & st.st_mode)) {
					gtk_list_store_append(store, &iter);
					gtk_list_store_set(store, &iter, IMAGE, image3, NAME,
							directory->d_name, SIZE, sizeBuffer, DATE, date,
							GHOST, Path, -1);

				} else {

					gtk_list_store_append(store, &iter);
					gtk_list_store_set(store, &iter, IMAGE, image, NAME,
							directory->d_name, SIZE, sizeBuffer, DATE, date,
							GHOST, Path, -1);
				}
			}
		}

		closedir(dp);
	}
	//sorted data
	GtkTreeSortable *sortable = GTK_TREE_SORTABLE(store);
	gtk_tree_sortable_set_sort_func(sortable, NAME, sort, GINT_TO_POINTER(NAME),
			NULL);
	gtk_tree_sortable_set_sort_column_id(sortable, NAME, GTK_SORT_ASCENDING);

	return GTK_TREE_MODEL(store);
}

/* Creates the columns for listStore
 * param: filename pathway
 * return: list tree store
 */
GtkWidget *
createAndview(char *filename) {
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
	//	 --- Column #2 ---
	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("File Name", renderer,
			"text", NAME, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(view), column);
	gtk_tree_view_column_set_sort_column_id(column, NAME);
	gtk_tree_view_column_set_sort_indicator(column, TRUE);
	//	 --- Column #3 ---
	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Size", renderer, "text",
			SIZE, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(view), column);
	gtk_tree_view_column_set_sort_column_id(column, SIZE);
	gtk_tree_view_column_set_sort_indicator(column, TRUE);
	//	 --- Column #4 ---
	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Date", renderer, "text",
			DATE, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(view), column);
	gtk_tree_view_column_set_sort_column_id(column, DATE);
	gtk_tree_view_column_set_sort_indicator(column, TRUE);
	//	 --- Ghost ---
	column = gtk_tree_view_column_new_with_attributes(NULL, NULL, "text", GHOST,
			NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(view), column);

	model = createListTree(filename);

	gtk_tree_view_set_model(GTK_TREE_VIEW(view), model);

	g_object_unref(model);

	return view;
}

/* After a file is selected in directory view
 * that file is read by textview.c and
 * is displayed into a window
 * param: selection, is what directory was selected
 * param: data, user data
 */
void file_selected(GtkWidget *selection, gpointer data) {
	GtkTreeModel *model;
	GtkTreeIter iter;
	if (gtk_tree_selection_get_selected(GTK_TREE_SELECTION(selection), &model,
			&iter)) {

		gchar *name;
		GtkWidget *Boxview = data;

		//create new textviews
		GtkWidget* textview1 = gtk_text_view_new();
		GtkWidget* textview2 = gtk_text_view_new();
		GtkWidget* textview3 = gtk_text_view_new();
		/* This code snippet was copied and modifyed slightly from
		 * StackOverflow, http://stackoverflow.com/questions/9192223/remove-gtk-container-children-repopulate-it-then-refresh
		 * Created by unwind
		 */
		GList *children, *Childiter;
		children = gtk_container_get_children(GTK_CONTAINER(Boxview));
		for (Childiter = children; Childiter != NULL;
				Childiter = g_list_next(Childiter))
			gtk_widget_destroy(GTK_WIDGET(Childiter->data));
		g_list_free(children);
		//get the name of file selected
		gtk_tree_model_get(model, &iter, GHOST, &name, -1);

		GtkTextBuffer* buffer1 = gtk_text_view_get_buffer(
				GTK_TEXT_VIEW(textview1));
		GtkTextBuffer* buffer2 = gtk_text_view_get_buffer(
				GTK_TEXT_VIEW(textview2));
		GtkTextBuffer* buffer3 = gtk_text_view_get_buffer(
				GTK_TEXT_VIEW(textview3));
		// fill textview buffers
		fill_buffer_Address(buffer1, name);
		fill_buffer_Hex(buffer2, name);
		fill_buffer_Text(buffer3, name);

		gtk_box_pack_start((GTK_BOX(Boxview)), textview1, TRUE, FALSE, 0);
		gtk_box_pack_start((GTK_BOX(Boxview)), textview2, TRUE, FALSE, 0);
		gtk_box_pack_start((GTK_BOX(Boxview)), textview3, TRUE, FALSE, 0);
		gtk_widget_show_all(Boxview);

	}

}
