#ifndef _DIR_
#define _DIR_

#include <stdio.h>
#include <stdlib.h>

#include "AVL.h"
#include "LL.h"

typedef struct Dir* pDir;
struct Dir {
    pnode* subdirsOC;
    link* subdirsABC;
    char* path;
    char* value;
};

pDir NEWDir(char*, char*);
void listDir(pDir);
char* key(pDir);
int eq(char*, char*);
int less(char*, char*);
void freeDir(pDir);
void insertsubDir(pDir, char*);

#endif