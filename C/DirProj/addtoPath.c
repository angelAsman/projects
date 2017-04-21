/*
 * addtoPath.c
 *
 *  Created on: Jul 15, 2015
 *      Author: Angel Asman
 *
 *   Adds the current working directory
 *   at start of program to PATH environment variable
 */
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Adds the CLI current directory to PATH
 * for execvp() to find CLI built in executables
 */

#define SIZE 1024

void changePath(){
	char* newPath;
	char* var;
	char buff[SIZE];
	char colon[SIZE] = ":";

	getcwd(buff, sizeof(buff));
	newPath = buff;
	strcat(colon,newPath);
	var = getenv("PATH");
	strcat(var, colon);
	setenv("PATH", var, 1);
}
