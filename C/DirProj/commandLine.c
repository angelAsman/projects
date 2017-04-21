/*
 * commandLine.c
 *
 *  Created on: Jul 8, 2015
 *      Author: Angel Asman
 *
 *  This is a command line interpreter.
 *  Some of this code is from tokentest.c
 *  written by Professor Bover.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "addtoPath.h"
#include "tokenizer.h"
#include "execute.h"
#include "changeDirectory.h"

#define MAX_LINE    1024

int main(int argc, char** argv){
	char line[MAX_LINE];
	char **tokens;

	changePath();// add CLI directory to PATH

	printf("$> ");
	while (fgets(line, MAX_LINE, stdin)) {
		// remove the '\n' from the end of the line
		line[strlen(line)-1] = '\0';
		tokens = gettokens(line);
		if((execProcess(tokens)) < 0){
			exit(1);
		}
		printf("$> ");
	}

	return 0;

}
