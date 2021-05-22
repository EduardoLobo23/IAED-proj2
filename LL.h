#ifndef _LL_
#define _LL_

#include <stdio.h>
#include <stdlib.h>

typedef struct node* pnode;
struct node {
    char* path;
    char* name;
    pnode next;
};

void LLinit(pnode*);
void LLinsert(pnode*, char*, char*);
void LLfree(pnode*);
void LLprint(pnode);
void LLlookup(pnode*, char*);

#endif