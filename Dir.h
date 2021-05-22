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
    char* name;
    char* value;
};

pDir NEWDir(char*, char*, char*);
void listDir(pDir);
char* key(pDir);
int eq(char*, char*);
int less(char*, char*);
void freeDir(pDir);
void insertsubDir(pDir, char*, char*);
int subdirofDir(pDir, char*);
void changevalueDir(pDir, char*);
void printDir(pDir);
void deleteDir(pDir);

#endif