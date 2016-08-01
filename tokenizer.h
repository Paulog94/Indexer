/*
 * Paulo Garcia and Roel
 *
 *
 */

#ifndef TOKENIZER
#define TOKENIZER

struct TokenizerT_ {
	char * input;
	int track;

};

typedef struct TokenizerT_ TokenizerT;

TokenizerT * TKCreate(char * ts);

void TKDestroy(TokenizerT * tk);

char *TKGetNextToken(TokenizerT *tk);

char * checkWord(int * x, char * input);

char * parser(char * input, int * track);
#endif