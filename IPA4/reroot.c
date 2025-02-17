#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "reroot.h"

/*
stack* Push(tree currNode)
{
    stack *temp;
    temp = malloc(sizeof(stack));
    currNode -> next = NULL; 
    return currNode;
}

stack* Pop(stack *st)
{
    st = st -> next;
    return st;
}


void Push(tree * stack, tree *currNode)
{   
    ++ top;
    stack[top] = currNode;
}
 
tree * Pop(tree * stack[])
{  
    tree * popped = NULL;
    popped =  stack[top];
    --top;
    return popped;
}
*/

tree* LoadFile(char* filename) 
{
    FILE* fptr = fopen(filename, "r");
    if(fptr == NULL) 
    {
        printf("Error, unable to open File for reading...\n");
        return NULL;
    }
    //char c;
    char nodeType;
    //double width, height;
    printf("Starting the I/O...\n");
    tree* newNode;
    top = -1;
    
    do
    { 
        nodeType = fgetc(fptr);
	printf("%c", nodeType);
        if(nodeType == '(')
        {
	    newNode = malloc(sizeof(tree));
	    fscanf(fptr, "%le,%le)", &newNode->width, &newNode->height);
	    newNode->xCoordinate = 0.0;
            newNode->yCoordinate = 0.0;
            newNode->cut = '-';
            Push(&(stack[0]), newNode);
        }
         
        else if(nodeType == 'H')
        {
            newNode = malloc(sizeof(tree));
            newNode -> cut = 'H';
            newNode -> rightChild = Pop(stack);
	    newNode -> leftChild = Pop(stack);
	    Push(stack, newNode);
        }
        else if(nodeType == 'V')
        {
            newNode = malloc(sizeof(tree));
            newNode -> cut = 'V';
            newNode -> rightChild = Pop(stack);
	    newNode -> leftChild = Pop(stack);
	    Push(stack, newNode);
        }
        
    }while (nodeType != EOF);
    
    return newNode;
    //return tree;
}


void SaveFile(tree * ptr, char * filename)
{
    FILE* fptr = fopen(filename, "w");
    if(fptr == NULL) 
    {
        printf("Error, unable to open File for writing...\n");
        return NULL;
    }
    return;

}
/********** PACKING FUNCTIONS ***********/



void MeasureCuts(tree *temp)
{
    if(temp -> leftChild == NULL)
    {        
	// Basecase 
	return;
    }
    if(temp->leftChild->height == 0.0)
    {
        //printf("go left\n");
        MeasureCuts(temp->leftChild);
    }
    if(temp->rightChild->height == 0.0)
    {
        //printf("go right\n");
        MeasureCuts(temp->rightChild);
    }

    if(temp->cut == 'H')
    {
        temp->height = temp->leftChild->height + temp->rightChild->height;
        if((temp->rightChild->width) > (temp->leftChild->width))
        {
            temp->width = temp->rightChild->width;
        }
        else
        {
            temp->width = temp->leftChild->width;      
        }
        
    }
    else if(temp->cut == 'V')
    {
        temp->width = temp->leftChild->width + temp->rightChild->width;
        if((temp->rightChild->height) > (temp->leftChild->height))
        {
            temp->height = temp->rightChild->height;
        }
        else
        {
            temp->height = temp->leftChild->height;      

        }
    }
    return;
}


void GetCoordinates(tree * temp)
{
    if(temp == NULL)
    {        
	// Basecase 
	return;
    }
    if(temp -> cut == 'V')
    {
        temp->leftChild->xCoordinate = temp -> xCoordinate;
        temp->leftChild->yCoordinate = temp->yCoordinate;
        temp->rightChild->yCoordinate = temp->yCoordinate;
        temp->rightChild->xCoordinate = temp -> xCoordinate + temp->leftChild->width;
        printf("At V-cut...\n");
        printf("Cut: %c X:%le, Y:%le \n",temp->leftChild->cut,temp->leftChild->xCoordinate,temp->leftChild->yCoordinate); 
        printf("Cut: %c X:%le, Y:%le \n",temp->rightChild->cut,temp->rightChild->xCoordinate,temp->rightChild->yCoordinate);   
  
    }
    else if(temp -> cut == 'H')
    {
        temp->leftChild->xCoordinate = temp->xCoordinate;
        temp->rightChild->xCoordinate = temp->xCoordinate;
        temp->rightChild->yCoordinate = temp->yCoordinate;
        temp->leftChild->yCoordinate = temp->yCoordinate + temp->rightChild->height;
        printf("At H-cut...\n");
        printf("Cut: %c X:%le, Y:%le \n",temp->leftChild->cut,temp->leftChild->xCoordinate,temp->leftChild->yCoordinate); 
        printf("Cut: %c X:%le, Y:%le \n",temp->rightChild->cut,temp->rightChild->xCoordinate,temp->rightChild->yCoordinate);   
	
    }

    GetCoordinates(temp->leftChild);
    GetCoordinates(temp->rightChild);
    return;
}

void FindDimensions(tree * temp, double *maxWidth, double *maxHeight)
{
    if(temp == NULL)
    { 
        return;
    }
    if(temp -> cut == 'V')
    {
        
        if(temp->leftChild->xCoordinate + temp->rightChild->xCoordinate > *maxWidth)
        {
           *maxWidth = temp->leftChild->width + temp->rightChild->width;
        }
  
    }
    else if(temp -> cut == 'H')
    {
        if(temp->leftChild->yCoordinate + temp->rightChild->yCoordinate > *maxHeight)
        {
           *maxHeight = temp->leftChild->height + temp->rightChild->height;
        }
	
    } 
    FindDimensions(temp->leftChild, maxWidth, maxHeight);
    FindDimensions(temp->rightChild, maxWidth, maxHeight);
    return;
}



tree* SampleTree() 
{
    tree* head = malloc(sizeof(tree));
    tree* nodex = malloc(sizeof(tree));
    tree* nodey = malloc(sizeof(tree)); 
    tree* nodez = malloc(sizeof(tree)); 
    tree* nodeV = malloc(sizeof(tree)); 
    nodex -> width = 3;
    nodex -> height = 3;
    nodey -> width = 4;
    nodey -> height = 5;
    nodez -> width = 7;
    nodez -> height = 7;
    nodex -> cut = '-';
    nodey -> cut = '-';
    nodez -> cut = '-';
    head -> cut = 'H';
    nodeV -> cut = 'V';
    head -> leftChild = nodex; 
    head -> rightChild = nodeV;      
    nodeV -> leftChild = nodey;
    nodeV -> rightChild = nodez;
    return head; 
}

void PrintPreorder(tree *head)
{
    if(head != NULL)
    {
        if(head->cut == '-') 
        {
            printf("(%le,%le)", head->width, head->height);
        }
        else
        {
            printf("%c",head->cut);   
        }
        PrintPreorder(head->leftChild);
        PrintPreorder(head->rightChild);
    }
    return;
}

void PrintInorder(tree *head)
{
    if(head != NULL)
    {
        PrintInorder(head->leftChild);
        if(head->cut == '-') 
        {
            printf("(%le,%le)", head->width, head->height);
        }
        else
        {
            printf("%c",head->cut);   
        }
        PrintInorder(head->rightChild);
    }
    return;
}
 
void PrintPostorder(tree *head)
{
    if(head != NULL)
    {
        PrintPostorder(head->leftChild);
        PrintPostorder(head->rightChild);
        if(head->cut == '-') 
        {
            printf("(%le,%le)", head->width, head->height);
        }
        else
        {
            printf("%c",head->cut);   
        }
    }
    return;
}

int main(int argc, char* argv[])
{
    
    tree *head = NULL;
    //clock_t start, end;
    double maxWidth = 0.0;
    double maxHeight = 0.0;
    
    if(argc != 3){
        printf("Incorrect number of arguments provided...now exiting\n");
        return 1;
    }
    
    //head = LoadFile(argv[1]);
    printf("\n \n");
    head = SampleTree();
    printf("Preorder: ");
    PrintPreorder(head);
    printf("\n\n");
    printf("Inorder: ");
    PrintInorder(head);
    printf("\n\n");
    printf("Postorder: ");
    PrintPostorder(head);
    printf("\n\n");
    MeasureCuts(head); 
    GetCoordinates(head);
    FindDimensions(head, &maxWidth, &maxHeight);
    printf("Width: %le  Height: %le \n", maxWidth, maxHeight);
    return 0;
}

