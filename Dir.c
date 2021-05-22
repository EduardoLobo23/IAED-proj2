#include "Dir.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

pDir NEWDir(char* path, char* name, char* value) {
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
    x->name = (char*)malloc(sizeof(char) * (strlen(name) + 1));
    strcpy(x->name, name);
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

void printDir(pDir dir) {
    LLprint(*(dir->subdirsOC));
}

void freeDir(pDir dir) {
    free(dir->value);
    free(dir->name);
    free(dir->path);
    if (dir->subdirsOC != NULL)
        LLfree(dir->subdirsOC);
    if (dir->subdirsABC != NULL)
        STfree(dir->subdirsABC);
    free(dir);
}

void insertsubDir(pDir dir, char* subdir) {
    STinsert(dir->subdirsABC, subdir);
    LLinsert(dir->subdirsOC, subdir);
}

int subdirofDir(pDir dir, char* path) {
    return strcmp(STsearch(*(dir->subdirsABC), path), "") != 0;
}

void changevalueDir(pDir dir, char* newvalue) {
    free(dir->value);
    dir->value = (char*)malloc(sizeof(char) * (strlen(newvalue) + 1));
    strcpy(dir->value, newvalue);
}

void deleteDir(pDir dir) {
    puts(dir->value);
}