#include <stdio.h>
#include <stdlib.h>
#include "linkedList.h"
#include "Turtle.h"

LinkedList* createList()
{
    LinkedList* list = ( LinkedList* )malloc( sizeof( LinkedList ) );
    list->head = NULL; /* creating an EMPTY Linked List */
    list->tail = NULL; 
    return list;
}
 
void insertFirst( LinkedList* list, Command* value )
{
    LinkedListNode* newNode; /* declaring a LinkedListNode pointer */   

    newNode = ( LinkedListNode* )malloc( sizeof( LinkedListNode ) ); /* create a new Node */
    
    newNode->data = value; /* data points to the value to be inserted; same as (*newNode).data */

    if( list->head == NULL )
    {
        list->head = newNode;
        list->tail = newNode;
    }
    else
    {
        list->head->prev = newNode;
        newNode->next = list->head;
        list->head = newNode;
    }
                  
}

void insertLast( LinkedList* list, Command* value )
{
    
    LinkedListNode* newNode = ( LinkedListNode* )malloc( sizeof( LinkedListNode ) ); /* create a new Node */
          
    newNode->data = value;
    
    if( list->head == NULL )
    {
        list->head = newNode;
        list->tail = newNode;
    }
    else
    {
        list->tail->next = newNode;
        newNode->prev = list->tail;
        list->tail = newNode;   
    }      
}

void removeNode( LinkedList* list )
{
    LinkedListNode* temp;

    if( list->head == NULL )
    { 
        printf( "LinkedList is NULL" ); /* DON'T remove if head is null */
    }
    else
    {
        temp = list->head;
        list->head = list->head->next; /* The head now points to the next node */ 
        free( temp ); /* Free the first Node */         
    }
}

Command* retrieve( LinkedListNode* node, int position ) 
{   
    int num, ii;
    LinkedListNode* temp = node; 
    num = listLength( node );
    
    if( position > num )
    {
        printf( "The position entered is NOT within the linkedList" );
    }  
    else
    {
        for( ii = 0; ii < position - 1; ii++ ) /* position starts from 1 onwards */
        {
            temp = node->next; /* keep on going until the position is found */
        } 
    }
    
    return temp->data;
}

int listLength( LinkedListNode* node )
{
    int length = 0;
    if( node != NULL )
    {
        length = 1 + listLength( ( node->next ) ); /* recurse through function to add length */
    }
    return length;
}

/* Frees the whole list */
void freeLinkedList( LinkedList* list )
{ 
    freeNode( list->head );
    free( list );
}

/* Frees a given node and everything after it. */
void freeNode( LinkedListNode *node )
{
    if( node != NULL ) 
    {
        freeNode( node->next ); /* recurssive call */

         free( node->data ); 
        free( node );
    }
} 


