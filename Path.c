/*
 * File: Path.c
 * Author: Eduardo Lobo
 * Description: Creation and manipulation of ADT "Path".
 */

#include "Path.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*----------------------------------------------------------------------*/

pPath NEWPath(char* name, char* lcomponent, char* value) {
    pPath x = (pPath)malloc(sizeof(struct Path));
    x->icomponentsOC = (pnode*)malloc(sizeof(pnode));
    LLinit(x->icomponentsOC);
    x->icomponentsABC = (link*)malloc(sizeof(link));
    STinit(x->icomponentsABC);
    x->name = (char*)malloc(sizeof(char) * (strlen(name) + 1));
    strcpy(x->name, name);
    x->lcomponent = (char*)malloc(sizeof(char) * (strlen(lcomponent) + 1));
    strcpy(x->lcomponent, lcomponent);
    x->value = (char*)malloc(sizeof(char) * (strlen(value) + 1));
    strcpy(x->value, value);
    return x;
}
void Pathlist(pPath path) {
    STsort(*(path->icomponentsABC));
}

void Pathprint(pPath path) {
    LLprint(*(path->icomponentsOC));
}

void Pathinsertsubpath(pPath path, char* name, char* lcomponent) {
    STinsert(path->icomponentsABC, lcomponent);
    LLinsert(path->icomponentsOC, name, lcomponent);
}

int Pathissubpathof(pPath path, char* lcomponent) {
    return strcmp(STsearch(*(path->icomponentsABC), lcomponent), "") != 0;
}

void Pathchangevalue(pPath path, char* newvalue) {
    free(path->value);
    path->value = (char*)malloc(sizeof(char) * (strlen(newvalue) + 1));
    strcpy(path->value, newvalue);
}

void Pathfree(pPath path) {
    free(path->value);
    free(path->lcomponent);
    free(path->name);
    if (path->icomponentsOC != NULL)
        LLfree(path->icomponentsOC);
    if (path->icomponentsABC != NULL)
        STfree(path->icomponentsABC);
    free(path);
}