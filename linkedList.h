#include "struct.h"


/* BEGIN - ALL THE FUNCTIONS */

LinkedList* createList( void );
void insertFirst( LinkedList* , Command* );
void insertLast( LinkedList*, Command* );
void removeNode( LinkedList* );
int listLength( LinkedListNode* );
void freeLinkedList( LinkedList* list );
void freeNode( LinkedListNode* node );
Command* retrieve( LinkedListNode*, int );

/* END - ALL THE FUNCTIONS */


