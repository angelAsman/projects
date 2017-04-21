/*
 * textview.c
 *
 *  Created on: Aug 13, 2015
 *      Author: Angel Asman
 *
 *      This reads 16 bytes of data and converts it the hex and keeps track of file offset in hex
 */
#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define SIZE 10000
/* Finds filesize
 * param: fileSize, integer of file size
 * param: fp, file pointer
 * param: filename, name of file that is selected
 */

void fileSet(int *fileSize, FILE *fp, gchar* filename) {
	fseek(fp, 0, SEEK_END);
	*fileSize = ftell(fp);
	fseek(fp, 0, SEEK_SET);
}

/* Reads 16 bytes of characters from file stream
 * param: numRead, number of characters read
 * param: buff, buffer that contains 16 bytes of characters
 * param: fp, file pointer
 * return: interger for errors
 */
int numberRead(int *numRead, char *buff, FILE *fp) {
	int i = 0;
	*numRead = fread(buff, 1, 16, fp);
	buff[strlen(buff) - 1] = '\0';
	while (buff[i] != '\0') {
		if (!(buff[i] >= 32 && buff[i] <= 127)) {
			buff[i] = '.';
		}
		i++;
	}
	if (*numRead < 1) {
		printf("error\n");
		return 1;
	}
	if (*numRead < 16) {
		memset(&buff[*numRead], 0, 16 - *numRead);
	}
	return 0;

}
/* Fills text view buffer with hex converted text
 * param: buffer, textview buffer
 * param: filename, name of file selected
 * return: interger for errors
 */
int fill_buffer_Hex(GtkTextBuffer* buffer, gchar* filename) {
	GtkTextIter iter;
	FILE *fp;
	int fileSize;
	int x, numRead;
	char buff[17] = { 0 };
	char middle[30] = { 0 };
	char *buffCopy[50] = { 0 };

	if ((fp = fopen(filename, "r")) == NULL) {
		return 1;
	}
	gtk_text_buffer_get_iter_at_offset(buffer, &iter, 0);
	fileSet(&fileSize, fp, filename);
	if (fileSize > SIZE) {
		fileSize = SIZE;
	}

	for (x = 0; x < fileSize; x += 16) {
		numberRead(&numRead, buff, fp);
		int i;
		for (i = 0; i < strlen(buff); i++) {
			sprintf(middle, "%02X", buff[i]);
			buffCopy[i] = malloc(sizeof(char*) * (strlen(middle) + 1));
			strcpy(buffCopy[i], middle);
			gtk_text_buffer_insert(buffer, &iter, buffCopy[i], -1);
			gtk_text_buffer_insert(buffer, &iter, "   ", -1);

		}
		gtk_text_buffer_insert(buffer, &iter, "\n", 1);

	}
	fclose(fp);
	return (0);
}
/* Fills text view buffer file offset converted to hex
 * param: buffer, textview buffer
 * param: filename, name of file selected
 * return: interger for errors
 */
int fill_buffer_Address(GtkTextBuffer* buffer, gchar* filename) {
	GtkTextIter iter;
	FILE *fp;
	int fileSize, current;
	int x, numRead;
	char buff[17] = { 0 };
	char address[8] = { 0 };

	if ((fp = fopen(filename, "r")) == NULL) {
		return 1;
	}
	gtk_text_buffer_create_tag(buffer, "gray_bg", "background", "gray", NULL);
	gtk_text_buffer_get_iter_at_offset(buffer, &iter, 0);
	fileSet(&fileSize, fp, filename);
	if (fileSize > SIZE) {
		fileSize = SIZE;
	}

	for (x = 0; x < fileSize; x += 16) {
		current = ftell(fp);
		sprintf(address, "%08X", current);
		gtk_text_buffer_insert_with_tags_by_name(buffer, &iter, address, -1,
				"gray_bg", NULL);
		gtk_text_buffer_insert(buffer, &iter, "\n", -1);
		numberRead(&numRead, buff, fp);
	}

	fclose(fp);
	return (0);
}
/* Fills text view buffer with text
 * param: buffer, textview buffer
 * param: filename, name of file selected
 * return: interger for errors
 */
int fill_buffer_Text(GtkTextBuffer* buffer, gchar* filename) {
	GtkTextIter iter;
	FILE *fp;
	int fileSize;
	int x, numRead;
	char buff[17] = { 0 };

	if ((fp = fopen(filename, "r")) == NULL) {
		return 1;
	}
	gtk_text_buffer_get_iter_at_offset(buffer, &iter, 0);
	fileSet(&fileSize, fp, filename);
	if (fileSize > SIZE) {
		fileSize = SIZE;
	}
	for (x = 0; x < fileSize; x += 16) {
		numberRead(&numRead, buff, fp);

		gtk_text_buffer_insert(buffer, &iter, buff, -1);
		gtk_text_buffer_insert(buffer, &iter, "\n", 1);

	}
	fclose(fp);
	return (0);
}

