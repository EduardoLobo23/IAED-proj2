/*
 * File: LL.h
 * Author: Eduardo Lobo
 * Description: Creation and manipulation of ADT "LL".
 */

#ifndef _LL_
#define _LL_

#include <stdio.h>
#include <stdlib.h>

/*----------------------------------------------------------------------*/

/* Type of data called "pnode" which consist of a pointer to an ADT
node. */
typedef struct node* pnode;

/* Type of data called "node" that works as a linked list, storing 2
pointers to strings on each node. */
struct node {
    char* name;
    char* lcomponent;
    pnode next;
};

/*----------------------------------------------------------------------*/

/* Initiates the list. */
void LLinit(pnode*);

/* Inserts a new node on the list. */
void LLinsert(pnode*, char*, char*);

/* Searchs for the node that contains a certain string. */
void LLlookup(pnode*, char*);

/* Traverses the list, printing on stdout each node's "name" on a 
different line. */
void LLprint(pnode);

/* Frees the memory allocated for a node with a certain name. */
void LLdelete(pnode*, char*);

/* Frees the memory allocated for the whole list, one node at a time. */
void LLfree(pnode*);

#endif