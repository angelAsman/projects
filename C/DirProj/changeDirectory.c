/*
 * changeDirectory.c
 *
 *  Created on: Jul 10, 2015
 *      Author: Angel Asman
 *
 *  For specified string, does correct
 *  directory action.
 */
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define SIZE 1024

/*
 * Parameter: command line arguments
 * Changes to specified directory or prints current
 * by comparing argument to specified
 * commands
 * returns: integer
 */

int cwdChange(char **argv){
	char direct[SIZE];

	if(strcmp(argv[0] , "cd") == 0){
		if(chdir(argv[1]) < 0){
			printf("No such directory: %s\n ", argv[1] );
			return 1;
		}
		getcwd(direct, sizeof(direct));// get current directory
		printf("cwd changed to %s\n", direct);
		return 0;

	}else if(strcmp(argv[0] , "pwd") == 0){
		getcwd(direct, sizeof(direct));
		printf("%s ", direct);
		return 0;
	}

	return 1;
}
