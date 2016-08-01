/*
 * Paulo Garcia and Roel Ronquillo
 * Assignment 3 Indexer
 *
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include "SortedList.h"
#include "tokenizer.h"
#include "FileReader.h"
#include "indexer.h"

void toLowerCase(char * string);
void saveFile(Indexer * index, FILE * save);

void toLowerCase(char *string) {
    int i;
    for(i = 0; string[i] != '\0'; i++)
        string[i] = tolower(string[i]);
}

void saveFile(Indexer * index, FILE * save){

}

int main(int argc, char **argv) {

	if (argc != 3) {
		printf("Usage: ./index <inverted-index filename> <directory or file name>\nAborting\n");
		
		return 0;
	}

	FILE *save = fopen(argv[1], "r");
    
	if(save != NULL) { /*if file already exists*/
        char input[10];
		printf("File %s already exists, Overwrite [Y/N]? ", argv[1]);
			fflush( stdout );
			scanf("%s", input);
            
			toLowerCase(input);
            if(strcmp(input, "yes") == 0 || strcmp(input, "y") == 0){
                printf("\n Overwriting file\n");
				fflush( stdout );
			
			}
            else if(strcmp(input, "no") == 0 || strcmp(input, "n") == 0) {
                fclose(save);
                printf("Aborting\n"); //abort if user doesn't want to overwrite
				return 0;
            }
			else{
            printf("Invalid input. Aborting\n"); //if input is invalid
			fclose(save);
			return 0;
			}
			
    }

     save = fopen(argv[1], "w");/*opens file for writing, creates a new file if file doesn't exist*/

	char *objName = argv[2];
    int successval;
    struct stat obj;
    if(stat(objName, &obj) != 0) {
        fclose(save);
        printf("Failed to read a file.\nAborting\n");
        return 1;
    }

    Indexer* index = createIndexer();

    if(S_ISREG(obj.st_mode)) { /*if regular file*/
        char *obj = malloc(sizeof(char)*(strlen(objName)+1));
        obj = strcpy(obj, objName);
        addFileNode(index->FileList, objName, index->MasterWordList);
		successval = 1;
		
    } else if(S_ISDIR(obj.st_mode)) /*if directory*/
        successval = readDirectory(objName, index, NULL);

    if(!successval) {
        fclose(save);
        printf("Failed to read a file.\nAborting\n");
        return 1;
    }
	
	//prints to outfile
	printIndexer(index,save);
	
     /*saves file*/
        printf("Inverted index saved to file %s\n", argv[1]);
		fflush( stdout );
		
    fclose(save);
	freeIndexer(index);
	
	return 0;

}