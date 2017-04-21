/*
 * fref.c

 *
 *  Created on: Jun 25, 2015
 *      Author: Angel Asman
 *
 *  This program take in 2 arguments from command line.
 *  The first is the regular expression, and the second
 *  is the file to be searched. Then it will print the
 *  matching line.
 */

#include <stdio.h>
#include "regexp.h"

#define BUFFSIZE 1024


int main (int argc, char *argv[]){
	FILE *fileStream;
	char text[BUFFSIZE];
	int index;

	// checks the right amount of arguments
	if(argc < 3){
		printf("Not enough arguments");
		return 1;
	}

	/* first checks if the file is valid
	 * reads the text file of n-1 characters and writes to text
	 * then prints match to regular ecpression
	*/
	for(index = 2; index < argc; index++ ){
		if(!(fileStream = fopen(argv[index], "r"))){
			printf("Error opening %s ", argv[index]);
			return 1;

		}else{
			int countLine = 0;
			while(fgets(text, sizeof(text), fileStream)){
				countLine++;
				// print located matches
				if(match(argv[1], text)){
					printf(" %s:%d  %s\n", argv[index], countLine, text);
				}

			}
                }
        }
	


	fclose(fileStream);
	return 0;






}


