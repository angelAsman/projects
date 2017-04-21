/*
 * redirect.c
 *
 *  Created on: Jul 13, 2015
 *      Author: Angel Asman
 *
 *   Looks for and redirection symbols
 *   and duplicates fd
 */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>

/* Parameter: command line arguments
 * Looks for < or > symbols on command line
*  and duplicates file descriptors then closes
*  opened input and output
*/

void reDirect(char **argv){
	int in, out, i;

	for(i= 0; argv[i]; i++){
		if(strcmp(argv[i], "<") == 0){
			in = open(argv[i + 1], O_RDONLY);
			dup2(in, 0);
			close(in);

		}else if(strcmp(argv[i], ">") == 0){
			out = open(argv[i + 1], O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
			dup2(out, 1);
			close(out);
		}
	}



}
