/*
 * File: LLpaths.h
 * Author: Eduardo Lobo
 * Description: Creation and manipulation of ADT "LLpaths".
 */

#ifndef _LLDIRS_
#define _LLDIRS_

#include "Path.h"

/*----------------------------------------------------------------------*/

/* Type of data called "pnodePaths" which consists of a pointer to an 
ADT nodePaths. */
typedef struct nodePaths* pnodePaths;

/* Type of data called "nodePaths" that works as a linked list, storing
a pointer to an ADT Path. */
struct nodePaths {
    pPath path;
    pnodePaths next;
};

/*----------------------------------------------------------------------*/

/* Initiates the list. */
void LLpathsinit(pnodePaths*);

/* Inserts a new node on the list. */
void LLpathsinsert(pnodePaths*, pPath);

/* Searchs for the node that contains a path with a certain name. */
pPath LLpathslookup(pnodePaths*, char*);

/* Traverses the list, printing on stdout every paths' name and value,
one path per line. If the path doesn't have a value its not printed. */
void LLpathsprint(pnodePaths*, pPath);

/* Searchs for the node that contains a path with a certain value. */
pPath LLpathssearchbyvalue(pnodePaths*, char*);

/* Frees the memory allocated for a node with a certain path.
Also frees the memory allocated for the nodes that contain it's 
subpaths. */
void LLpathsdelete(pnodePaths*, pPath);

/* Frees the memory allocated for the whole list, one node at a time.  */
void LLpathsfree(pnodePaths*);

#endif