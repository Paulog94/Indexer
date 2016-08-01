/*
 * Paulo Garcia and Roel Ronquillo
 * Assignment 3 Indexer
 *
*/

#ifndef FILE_READER
#define FILE_READER
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "SortedList.h"

struct filenode{
	char * fileName;
	struct node * wordList;
	struct filenode * next;
};

typedef struct filenode FileNode;

FileNode * createFileNode();
void getFileWords(FileNode * Fnode, Node * masterList);
void findWord(FileNode *Fnode, char * word, FILE * outfile);
void addFileNode(FileNode *FNode, char *word, Node * masterList);
void findWordInFileList(FileNode *FNode,char *word, FILE * outfile);
void freeFileNode(FileNode *Fnode);

#endif