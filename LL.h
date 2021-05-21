#ifndef _LL_
#define _LL_

#include <stdio.h>
#include <stdlib.h>

typedef struct node* pnode;
struct node {
    char* path;
    pnode next;
};

void LLinit(pnode*);
void LLinsert(pnode*, char*);
void LLfree(pnode*);
void LLprint(pnode);

#endif