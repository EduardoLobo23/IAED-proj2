#include "Dir.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

pDir NEWDir(char* path, char* value) {
    pDir x = (pDir)malloc(sizeof(struct Dir));
    /* cria a LL que vai conter os filhos */
    x->subdirsOC = (pnode*)malloc(sizeof(pnode));
    LLinit(x->subdirsOC);
    /* cria a AVL que vai conter os filhos */
    x->subdirsABC = (link*)malloc(sizeof(link));
    STinit(x->subdirsABC);
    /* guarda o path e o value */
    x->path = (char*)malloc(sizeof(char) * (strlen(path) + 1));
    strcpy(x->path, path);
    x->value = (char*)malloc(sizeof(char) * (strlen(value) + 1));
    strcpy(x->value, value);
    return x;
}

char* key(pDir dir) {
    return dir->path;
}

int eq(char* path1, char* path2) {
    return strcmp(path1, path2);
}

int less(char* path1, char* path2) {
    return strcmp(path1, path2) < 0;
}

void listDir(pDir dir) {
    STsort(*(dir->subdirsABC));
}

void freeDir(pDir dir) {
    free(dir->value);
    free(dir->path);
    /*STfree(dir->subdirsABC);*/
    LLfree(dir->subdirsOC);
    STfree(dir->subdirsABC);
    free(dir);
}

void insertsubDir(pDir dir, char* subdir) {
    STinsert(dir->subdirsABC, subdir);
    LLinsert(dir->subdirsOC, subdir);
}