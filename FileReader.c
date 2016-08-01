/*
 * Paulo Garcia and Roel Ronquillo
 * Assignment 3 Indexer
 *
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include "SortedList.h"
#include "tokenizer.h"
#include "FileReader.h"

//Creates new File list
FileNode * createFileNode(char * fname){
	FileNode * FNode = malloc(sizeof(struct filenode));
	FNode->fileName = fname;
	FNode->next = NULL;
	//getFileWords(FNode);
	return FNode;
}

//Adds a new File to the File list
void addFileNode(FileNode *FNode, char *fname, Node * masterList){
	FileNode * current = FNode;
	
	while(current->next!=NULL)
		current = current->next;
	
	current->next = createFileNode(fname);
	getFileWords(current->next, masterList);
}

//Retrieves File tokens and adds them to a list and the File's list of words
void getFileWords(FileNode * Fnode, Node * masterList){
	char * buffer = 0;
	long length;
	FILE * f = fopen (Fnode->fileName, "rb");

	if (f)
	{
		fseek (f, 0, SEEK_END);
		length = ftell (f);
		fseek (f, 0, SEEK_SET);
		buffer = malloc (length);
		if (buffer)
		{
			fread (buffer, 1, length, f);
		}
	fclose (f);
	}
	
	int buff = strlen(buffer);
	char *input=malloc(sizeof(char)*buff);
  
	strncpy(input,buffer,buff);
	input[buff]='\0';
	TokenizerT *tk = TKCreate(input);
	
	char * token = NULL;
	Fnode->wordList = CreateNode();
	while( tk->track < buff){
		token = TKGetNextToken(tk);
		
		addNode(masterList, token);
		addNode(Fnode->wordList,token);
		//free(token);
	}
  //TKDestroy(tk);
  }

//Prints out the count of the word from a particular file  
void findWord(FileNode *Fnode, char * word, FILE * outfile){
	
	int x = findWordCount(word,Fnode->wordList);
	if(x!=0){
		fprintf(outfile,"\t\t{\"%s\" : %d}",Fnode->fileName,findWordCount(word,Fnode->wordList));
	}
	
}

//Prints out word contained in the files in the list
void findWordInFileList(FileNode *FNode,char *word, FILE * outfile){
	
	FileNode * c = FNode;
	
	if(strcmp(word,"")==0){
		return;
	}
	
	fprintf(outfile,"\t{\"%s\":[\n",word);
	while(c){
		if(containsWord(c->wordList,word)){
			findWord(c,word, outfile);
		if(c->next){
			if(containsWord(c->next->wordList,word)){
				fprintf(outfile,",\n");
			}
			else{
				while(c->next){
					if(!containsWord(c->next->wordList,word)){
						c = c->next;
					}
					else{
						fprintf(outfile,",\n");
						break;
					}
				}
			}
		}
	}
		c = c->next;
	}
	fprintf(outfile,"\n\t]}");
}

//Frees the File list
void freeFileNode(FileNode *Fnode){
	FileNode* current;
	while(Fnode){
		current = Fnode;
		Fnode = Fnode->next;
		free(current->fileName);
		freeList(current->wordList);
		free(current);
	}
}
