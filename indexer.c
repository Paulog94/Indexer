/*
 * Paulo Garcia and Roel Ronquillo
 * Assignment 3 Indexer
 *
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include "SortedList.h"
#include "tokenizer.h"
#include "FileReader.h"
#include "indexer.h"

//Creates an indexer
Indexer * createIndexer(){
	Indexer * index = malloc(sizeof(struct indexer));
	index->MasterWordList = CreateNode();
	index->FileList = createFileNode("","");
	return index;
}

//Reads a directory and reads all its files and its subdirectories.
int readDirectory(char *dirName, Indexer* index, char *pathName) {
    struct dirent *dirP;
    DIR *dir;

    if((dir = opendir(dirName)) == NULL)
        return 0;

    while((dirP = readdir(dir)) != NULL) {
        if(strcmp(dirP->d_name, ".")==0 || strcmp(dirP->d_name, "..")==0){
            continue;           /*skips hidden files*/
		}
        char objName[300];
        struct stat obj;
        sprintf(objName, "%s/%s", dirName, dirP->d_name); /*stores path name of file or another directory into objName ex: sample/test.txt or sample/directory*/
        if(stat(objName, &obj) != 0) {
            closedir(dir);
            return 0;
        }
        if(S_ISREG(obj.st_mode)) { /*if regular file*/
            char file[300];
            if(pathName == NULL)
                sprintf(file, "%s", dirP->d_name);
            else
                sprintf(file, "%s%s", pathName, dirP->d_name);
			
			char *fname = malloc(strlen(objName)+sizeof(char)); 
			strcpy(fname, objName);
			addFileNode(index->FileList,fname,index->MasterWordList);
            //if(!readFile(objName, index, file)) { /*read file*/
              //  closedir(dir);
                //return 0;
            //}
        } else if(S_ISDIR(obj.st_mode)) { /*if directory*/
            int x = strlen(dirP->d_name);
            if(pathName == NULL) {
                char path[x+2];
                sprintf(path, "%s/", dirP->d_name);
                if(!readDirectory(objName, index, path)) { /*read directory*/
                    closedir(dir);
                    return 0; /*failed*/
                }
            } else {
                int y = strlen(pathName);
                char path[y+x+2];
                sprintf(path, "%s%s/", pathName, dirP->d_name);
                if(!readDirectory(objName, index, path)) { /*read directory*/
                    closedir(dir);
                    return 0; /*failed*/
                }
            }
        }
    }
    closedir(dir);
    return 1; /*succeded*/
}

//Prints out the list format to an outfile
void printIndexer(Indexer * index, FILE * outfile){
	Node * masterList = index->MasterWordList;
	FileNode * Fnode = index->FileList;
	//addFileNode(Fnode,"testcases/test1.txt",masterList);
	//addFileNode(Fnode, "ex1.txt", masterList);
	
	fprintf(outfile,"{\"list\":[\n");
	while (masterList){
		findWordInFileList(Fnode,masterList->tok,outfile);
		if(strcmp(masterList->tok,"")==0){
			masterList = masterList->next;
			continue;
		}
		else
		if(masterList->next){
			fprintf(outfile,",\n");
		}
		else{
			fprintf(outfile,"\n");
		}
		masterList = masterList->next;
	}
	fprintf(outfile,"]}");
	
}

//Frees Indexer
void freeIndexer(Indexer * index){
	freeList(index->MasterWordList);
	freeFileNode(index->FileList);
	free(index);
}
