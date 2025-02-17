#ifndef SORTING_H
#define SORTING_H
#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    	long val;
    	struct node *next;
}Node;

typedef struct list{
	Node *node;
	struct list *next;
}List;

Node *Load_File(char *Filename);
int Save_File(char *Filename, Node *list);
Node *Shell_Sort(Node *list);
void Traverse_List(Node *list, int moves);
void Print_List(Node *head);
int Count_Number_Elements(Node *list);
int *Gen_Seq(int Size);


#endif
