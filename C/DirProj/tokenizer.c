/*
 * tokenizer.c
 *
 *  Created on: July 1, 2015
 *      Author: Angel Asman
 *
 *  Looks through command arguments
 *  and splits up tokens into an array
 *
 */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


/* Parameter: int last - pointer to end of string
 * 			  int index - pointer to index of string
 * 			  char temp - command line string
 *
 * Moves pointer along if it does not
 * encounter another quote or null.
*/
void movePointer(int *last, int *index, char *temp){
	while((temp[*index+1] != '"') && (temp[*index+1] != '\0')){
		(*last)++;
		(*index)++;
	}
}

/* Parameter: int buff- token index
 * 			  int lastPoint - pointer to end of string
 * 			  int firstPoint - pointer to start of string
 * 			  char tokens - token array
 * 			  char temp - command line string
 *
 * Allocates memory, then copies substring into token index
 * from the firstPoint to the difference of the ending point
 * then sets the firstPoint to the lastPoint.
 *
 */
void assignToken(int *buff, int *lastPoint, int *firstPoint, char **tokens, char *temp){
	tokens[*buff] = malloc(sizeof(char)*((*lastPoint-*firstPoint)+1));
	strncpy(tokens[*buff], (temp + *firstPoint), (*lastPoint - *firstPoint));
	*firstPoint = *lastPoint;
	(*buff)++;
}

/*Parameter: int first - pointer to start of token
 * 			 int last - pointer to end of token
 *increment the first and last pointer
 */
void incrementPointers(int *first, int *last){
	(*first)++;
	(*last)++;
}

/*Parameter: int i - string index
 * 			 int first - pointer to start of token
 * 			 int last - pointer to end of token
 * move all pointers along by one in string if there is a space
 *
 */
void moveIfspace(int *i, int *first, int *last){
	(*i)++;
	incrementPointers(first,last);
}

/*
 * Parameter: command line argument string
 * Looks through a copy of line by index i,
 * then finds delimiters and breaks up tokens.
 * returns: array of null terminated strings as tokens
 */
char **gettokens (char *line){
	char **tokens;
	char *tempString;
	int size = strlen(line);
	int i = 0;
	int buffIndex = 0;
	int begin = 0;
	int end = 0;
	tokens = malloc(sizeof(char*)*(size+1));
	tempString = line;


	while(i < (size)){
		switch(tempString[i]){

		case ' ':// in case of space, move along string
			moveIfspace(&i,&begin,&end);
			break;

		case '"':// in case of quote
			movePointer(&end,&i,tempString);
			incrementPointers(&begin,&end);
			assignToken(&buffIndex, &end, &begin, tokens, tempString);
			i = end++;
			incrementPointers(&begin,&end);
			break;

		default:// in case of letters
			while((tempString[i] !=' ') && (tempString[i] !='"') && (i < size)){
				i++;
				end++;
			}
			if(tempString[i] == '"'){// if there is a quote in between chars
				begin = begin +2;// cut off at quote
				movePointer(&end,&i,tempString);
				i=end++;
			}
			assignToken(&buffIndex, &end, &begin, tokens, tempString);
		}

	}

	tokens[-1] = '\0';
	return tokens;

}
