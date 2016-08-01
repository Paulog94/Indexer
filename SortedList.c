/*
 * Paulo Garcia and Roel Ronquillo
 * Assignment 3 Indexer
 *
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "SortedList.h"
#include "tokenizer.h"

//Creates new token Node
Node *CreateNode(){
	Node *head = malloc(sizeof(struct node));
	head->tok = NULL;
	head->next = NULL;
	head->count = 0;
	
	return head;
}

//Adds node to the List
void addNode(Node *head,char * tok){
	if(!head->tok)
	{	
		int buff = strlen(tok);
		char *token=malloc(sizeof(char)*buff);
		strncpy(token,tok,buff);
		token[buff]='\0';
		head->tok = token;
		head->count++;
		//printf("%s\n",head->tok);
	}
	else{
		Node * current = head;
		int x = strcmp(current->tok,tok);
		if(head->tok==""){
			head->tok = tok;
			head->count++;
			return;
		}
		if(x==0){
			head->count++; return;
		}
		if(x>0){
			//printf("Place Node Here\n");
			Node * newNode = CreateNode();
			newNode->tok = current->tok;
			newNode->count = current->count;
			int buff = strlen(tok);
			
			char *token=malloc(sizeof(char)*buff);
			strncpy(token,tok,buff);
			token[buff]='\0';
			current->tok = token;
			current->count = 1;
			
			newNode->next = current-> next;
			current-> next = newNode;
			}
		if(x<0){
			//printf("traverse\n");
			if(!current->next){
				Node * newNode = CreateNode();
				
				int buff = strlen(tok);
				char *token=malloc(sizeof(char)*buff);
				strncpy(token,tok,buff);
				token[buff]='\0';
				newNode->tok = token;
				newNode->count++;
				current->next = newNode;
			}
			else{
				addNode(current->next, tok);
			}
		}
	}
}
	
//Frees All nodes
void freeList(Node *head){
	Node* current;
	while(head){
		current = head;
		head = head->next;
		free(current->tok);
		free(current);
	}
}

//Prints the entire list
void printList(Node * head){
	
	Node* current = head;
	while(current){
		printf("%s: %d\n",current->tok, current->count);
		current=current->next;
	}
	
}

//Identifies the length of the list
int ListLength(Node * head){
	int count = 1;
	Node * current = head;
	while(current->next){
		count++;
		current = current->next;
	}
	return count;
}

//Returns the number of times a particular word appears
int findWordCount(char * word, Node * head){
	Node * current = head;
	while(current){
		if(strcmp(current->tok,word)==0)
			return current->count;
		current = current->next;
	}
	return 0;
}

//Sorts the Word List Alphabetically
void bubbleSort(Node * head){
    
	int swapped, i;
    Node * ptr1;
    Node * lptr = NULL;
 
    /* Checking for empty list */
    if (head == NULL)
        return;
 
    do
    {
        swapped = 0;
        ptr1 = head;
 
        while (ptr1->next != lptr)
        {
            if (ptr1->count > ptr1->next->count)
            { 
				swap(ptr1, ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    }
    while (swapped);
}
 
//function to swap data of two nodes a and b
void swap(Node * a, Node *b){
    int temp = a->count;
    a->count = b->count;
    b->count = temp;
	char * temp1 = a->tok;
	a->tok = b->tok;
    b->tok = temp1;
}

//Boolean to see if a list contains a particular word
int containsWord(Node * head, char * word){
	Node * current = head;
	while(current){
		if(strcmp(current->tok,word)==0)
			return 1;
	current = current->next;
	}
	return 0;
}
