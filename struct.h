
#ifndef STRUCT_H
#define STRUCT_H

/* TYPEDEF and #DEFINE */

typedef struct
{
    char* comName;
    char* comValue;
} Command;

typedef struct LinkedListNode
{
    Command* data;
    struct LinkedListNode* next; /* the tag name( top ) can be used within the struct */
    struct LinkedListNode* prev;
} LinkedListNode;

typedef struct
{
    LinkedListNode* head;
    LinkedListNode* tail;
} LinkedList;



#endif
/* ============================== */
