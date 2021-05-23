/*
 * File: Path.h
 * Author: Eduardo Lobo
 * Description: Creation and manipulation of ADT "Path".
 */

#ifndef _PATH_
#define _PATH_

#include <stdio.h>
#include <stdlib.h>

#include "AVL.h"
#include "LL.h"

#define NULL_VALUE ""
#define ROOT_NAME "root"
#define ROOT_LCOMPONENT "root"

/*----------------------------------------------------------------------*/

/* Type of data called "pPath" which consists of a pointer to an ADT Path. */
typedef struct Path* pPath;

/* Type of data called "Path" that contains a pointer to: a linked list
with the name of the path's immediate components, in order of creation; 
an AVL tree with the path's  immeadiate components' last component names, 
alphabetically; the path's name; the path's last component; the path's value. */
struct Path {
    pnode* icomponentsOC;
    link* icomponentsABC;
    char* name;
    char* lcomponent;
    char* value;
};

/*----------------------------------------------------------------------*/

/* Creates an ADT "path". */
pPath NEWPath(char*, char*, char*);

/* Traverses icomponentsABC, printing the last component of the path's 
immediate components on stdout, alpabetically, one on each line. */
void Pathlist(pPath);

/* Traverses icomponentsOC, printing the names' of the path's immediate 
components on stdout, by order of creation, one on each line. */
void Pathprint(pPath);

/* Inserts the subpath's last component in (path's) icomponentsOC and 
icomponentsABC and the subpath's name in (path's) icomponentsOC. */
void Pathinsertsubpath(pPath, char*, char*);

/* Checks if a certain subpath belongs to a certain path. */
int Pathissubpathof(pPath, char*);

/* Changes the value of a certain path. */
void Pathchangevalue(pPath, char*);

/* Frees the memory allocated for a certain path. */
void Pathfree(pPath);

#endif