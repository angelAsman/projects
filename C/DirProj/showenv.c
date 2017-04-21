/*
 * showenv.c
 *
 *  Created on: Jul 11, 2015
 *      Author: Angel Asman
 *
 *   Prints out environment variables
 */

#include <stdio.h>
#include <stdlib.h>
#include "tokenizer.h"
#include <string.h>


#define BUFFSIZE 1024

/*Parameter: int i - index
 * 			 char temp - array of variables
 * Prints the defined enviroment variables
 *
 */
void printVariables(int i, char **temp){
	char *name;
	for(; temp[i]; i++){
		if((name = getenv(temp[i]))){
			printf("%s = %s \n",temp[i], name);

		}else{
			printf("Undefined variables\n");
		}
	}

}

int main (int argc, char *argv[], char *envp[]){
	char text[BUFFSIZE];
	int index;
	char **tokens;

	// checks the for variable arguments
		if(argc < 2 ){
			printf("Please enter in variables: ");
			while(fgets(text, BUFFSIZE, stdin)){ //tokenize the input

				text[strlen(text)-1] = '\0';
				tokens = gettokens(text);
				index = 0;
				printVariables(index, tokens);
				return 0;
			}

		}else{
			index = 1;
			printVariables(index, argv);
		}
		return 0;
}
