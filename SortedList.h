/*
 * Paulo Garcia and Roel Ronquillo
 * Assignment 3 Indexer
 *
*/

#ifndef SORTED_LIST
#define SORTED_LIST

struct node{
	char * tok;
	int count;
	struct node * next;
};
typedef struct node Node;

Node *CreateNode();
void addNode(Node *head,char*token);
void freeList(Node * head);
int ListLength(Node * head);
void copy_string(char * target, char * source);
void printList(Node * head);
int findWordCount(char * word, Node * head);
void bubbleSort(Node * start);
void swap(Node * a, Node *b);
int containsWord(Node * head, char * word);


#endif