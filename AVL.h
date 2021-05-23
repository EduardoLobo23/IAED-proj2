/*
 * File: AVL.h
 * Author: Eduardo Lobo
 * Description: Creation and manipulation of ADT "AVL".
 */

#ifndef _AVL_
#define _AVL

#include <stdio.h>
#include <stdlib.h>

/*----------------------------------------------------------------------*/

/* Type of data called "link" which consists of a pointer to an ADT STnode. */
typedef struct STnode *link;

/* Type of data called "STnode" that works as an AVL, storing a pointer 
to a string on each node. */
struct STnode {
    char *lcomponent;
    link l;
    link r;
};

/*----------------------------------------------------------------------*/

/* Initiates the tree. */
void STinit(link *);

/* Inserts a new node on the tree. */
void STinsert(link *, char *);

/* Searchs for the node that contains a certain string. */
char *STsearch(link, char *);

/* Traverses the tree in order, printing on stdout the string attached
to each node on a different line. */
void STsort(link);

/* Frees the memory allocated for a single node of the tree, containing 
a certain string. */
void STdelete(link *, char *);

/* Frees the memory allocated for the whole tree, each node at a time. */
void STfree(link *);

#endif