#include "LLdirs.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void LLdirsinit(pnodeDirs* head) {
    *head = NULL;
}

pnodeDirs NEWnodeDirs(pDir dir) {
    pnodeDirs x = (pnodeDirs)malloc(sizeof(struct nodeDirs));
    x->dir = dir;
    x->next = NULL;
    return x;
}

pnodeDirs insertnodeDirs(pnodeDirs head, pDir dir) {
    pnodeDirs x;
    if (head == NULL)
        return NEWnodeDirs(dir);
    for (x = head; x->next != NULL; x = x->next)
        ;
    x->next = NEWnodeDirs(dir);
    return head;
}

void LLdirsinsert(pnodeDirs* head, pDir dir) {
    *head = insertnodeDirs(*head, dir);
}

pnodeDirs deletenodeDirs(pnodeDirs head, char* path) {
    pnodeDirs t;
    for (t = head; t != NULL; t = t->next) {
        if (strcmp(t->dir->path, path) == 0) {
            if (t == head)
                head = t->next;
            freeDir(t->dir);
            free(t);
            break;
        }
    }
    return head;
}

pnodeDirs freenodeDirs(pnodeDirs head) {
    if (head == NULL)
        return head;
    head->next = freenodeDirs(head->next);
    return deletenodeDirs(head, head->dir->path);
}

pnodeDirs lookupDirs(pnodeDirs head, char* name) {
    pnodeDirs t;
    for (t = head; t != NULL; t = t->next)
        if (strcmp(t->dir->name, name) == 0)
            return t;
    return NULL;
}

pnodeDirs lookuppathDirs(pnodeDirs head, char* path) {
    pnodeDirs t;
    for (t = head; t != NULL; t = t->next)
        if (strcmp(t->dir->path, path) == 0)
            return t;
    return NULL;
}

pDir LLdirslookup(pnodeDirs* head, char* name) {
    pnodeDirs aux;
    aux = lookupDirs(*head, name);
    if (aux == NULL)
        return NULL;
    return aux->dir;
}

pDir LLdirslookuppath(pnodeDirs* head, char* path) {
    pnodeDirs aux;
    aux = lookuppathDirs(*head, path);
    if (aux == NULL)
        return NULL;
    return aux->dir;
}

void LLdirsfree(pnodeDirs* head) {
    *head = freenodeDirs(*head);
}
