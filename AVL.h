#ifndef _AVL_
#define _AVL

#include <stdio.h>
#include <stdlib.h>

typedef struct STnode *link;

struct STnode {
    char *path;
    link l;
    link r;
};

void STinit(link *);
void STinsert(link *, char *);
int STcount(link);
char *STsearch(link, char *);
void STsort(link);
void STfree(link *);

#endif