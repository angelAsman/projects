/*
 * pathCreate.c
 *
 *  Created on: Aug 16, 2015
 *      Author: Angel Asman
 */
#include <string.h>
#define SIZE 1024


void createPath(char *newpath, char *oldpath, char *directoryName){
	char addedPath[SIZE] = "/";
	//char Path[SIZE];
	strcpy(newpath, oldpath);
	strcat(addedPath, directoryName);
	strcat(newpath, addedPath);
}
