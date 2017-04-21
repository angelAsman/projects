/*
 * execute.c
 *
 *  Created on: Jul 9, 2015
 *      Author: Angel Asman
 *
 *   Compares command line arguments
 *   and creates a parent and child process.
 *   Then executes command either internally or
 *   externally depending on argument. While also
 *   keeping track of stdin and stdout.
 */
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include "redirect.h"
#include "changeDirectory.h"

#define SIZE 1024

/* Parameter: input file descriptor and output file descriptor
 * Restores stdin and stdout
 *
 */
void preserveIO(int *in, int *out){
	dup2(*in,0); // preserve stdin and stdout
	dup2(*out,1);

	close(*in);
	close(*out);
}

/* Parameter: command line argument array
 * This functions compares the
 * command line arguments and
 * either creates a child process and
 * executes or executes the command
 * internally.
 * returns: integer
 */
int execProcess(char **argv){
	pid_t pid;
	int state, saved_stdout, saved_stdin;

	saved_stdout = dup(1);
	saved_stdin = dup(0);

	if(cwdChange(argv) == 0){// change Directory
		return 0;
	}

	if(strcmp(argv[0] , "exit") == 0){// terminate
		return -1;
	}
	reDirect(argv);

	if((pid = fork()) < 0){ // fork into a child
		printf("forking child process failed\n");
		return 1;

	}else if(pid == 0){ // child process
		reDirect(argv);
		if(strcmp(argv[0] , "exit") == 0){// terminate
			return -1;
		}

		if (execvp(*argv, argv) < 0){ // execute process
			printf("Cannot execute command\n");
			preserveIO(&saved_stdin, &saved_stdout);
			return 1;
		}
	}
	preserveIO(&saved_stdin, &saved_stdout);

	wait(&state);// parent waits
	return 0;


}
