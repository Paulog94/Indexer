/*
 * Paulo Garcia and Roel Ronquillo
 * Assignment 3 Indexer
 *
*/

#ifndef INDEXER
#define INDEXER
#include "FileReader.h"

struct indexer{
	struct node * MasterWordList;
	struct filenode * FileList;
}; 
typedef struct indexer Indexer;

Indexer * createIndexer();
void printIndexer(Indexer * index, FILE * outfile);
int readDirectory(char *dirName, Indexer* index, char *pathName);
void freeIndexer(Indexer * index);

#endif