/*
 * Paulo Garcia and Roel Ronquillo
 * Assignment 3 Indexer
 *
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "tokenizer.h"

/*
 * Tokenizer type.  You need to fill in the type as part of your implementation.
 */

/*
 * TKCreate creates a new TokenizerT object for a given token stream
 * (given as a string).
 * 
 * TKCreate should copy the arguments so that it is not dependent on
 * them staying immutable after returning.  (In the future, this may change
 * to increase efficiency.)
 *
 * If the function succeeds, it returns a non-NULL TokenizerT.
 * Else it returns NULL.
 *
 * You need to fill in this function as part of your implementation.
 */

TokenizerT *TKCreate( char * ts ) {
  TokenizerT *tk = malloc(sizeof(struct TokenizerT_));
	tk->input = ts;
	int x = strlen(ts);
	tk->input[x]='\0';
	tk->track = 0;
  return tk;
}

/*
 * TKDestroy destroys a TokenizerT object.  It should free all dynamically
 * allocated memory that is part of the object being destroyed.
 *
 * You need to fill in this function as part of your implementation.
 */

void TKDestroy( TokenizerT * tk ) {
	free(tk->input);
	free(tk);
}

/*
 * TKGetNextToken returns the next token from the token stream as a
 * character string.  Space for the returned token should be dynamically
 * allocated.  The caller is responsible for freeing the space once it is
 * no longer needed.
 *
 * If the function succeeds, it returns a C string (delimited by '\0')
 * containing the token.  Else it returns 0.
 *
 * You need to fill in this function as part of your implementation.
 */

char *TKGetNextToken( TokenizerT * tk ) {
  return parser(tk->input, &tk->track);
}

/***********************************************************************
*
*	Keyword Function:
*	Checks for keywords stored in C, in Unix I/O, and in Formatted I/O
*
************************************************************************/
 
char * checkWord(int * x, char * input){//stores Word and changes pointer integer
  char * token=NULL;
  int BUFF;
  int i = *x;
  while((isalpha(input[i])||isdigit(input[i]))&& i<strlen(input)){
    i++;
  }
  BUFF = i - *x;
  token = malloc(sizeof(char) * BUFF);
  strncpy(token, input+*x,BUFF);
  token[BUFF]='\0';
  int j = 0;
  for(j; j<BUFF; j++){
	if(isalpha(token[j]))
	token[j] = tolower(token[j]);
	}
  *x=i;
  return token;
}


/*******************************************************************
*	Parser Function:
*	based on the track number of the Tokenizer struct, the
*	parser will look at the input char at the given number spot
*	and send it to differnt function parsers depending on
*	what the character in input[i] is. 
*******************************************************************/

char * parser(char * input, int * track){
    int i=*track;
	char * token =NULL;
	
	if(isalpha(input[i])){
		token = checkWord(&i, input);
		*track = i;
		return token;
    }
	else if(input[i]=='\0'||i>strlen(input)){
		*track = i;
	return NULL;
	}
    else
		while(!isalpha(input[i]))
			i++;
		*track = i;
		return parser(input, track);
}
