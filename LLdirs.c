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
    pnodeDirs t, prev;
    for (t = head, prev = NULL; t != NULL; prev = t, t = t->next) {
        if (strcmp(t->dir->path, path) == 0) {
            if (t == head)
                head = t->next;
            else
                prev->next = t->next;
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

pDir searchDirs(pnodeDirs* head, pDir dir, char* value) {
    pnode t;
    pDir d;

    if (strcmp(dir->value, value) == 0)
        return dir;
    if (dir->subdirsOC != NULL)
        for (t = *(dir->subdirsOC); t != NULL; t = t->next) {
            d = LLdirslookuppath(head, t->path);
            if (d != NULL) {
                if (strcmp(d->value, value) == 0)
                    return d;
                d = searchDirs(head, d, value);
                if (d != NULL)
                    return d;
            }
        }
    return NULL;
}

pDir LLdirssearch(pnodeDirs* head, char* value) {
    pDir root = LLdirslookuppath(head, "root");
    root = searchDirs(head, root, value);
    if (root == NULL)
        return NULL;
    return root;
}

void LLdirsprint(pnodeDirs* pDirs, pDir dir) {
    pnode t = *(dir->subdirsOC);
    pDir d;
    for (; t != NULL; t = t->next) {
        d = LLdirslookuppath(pDirs, t->path);
        if (d != NULL) {
            if (strcmp(d->value, "") != 0)
                printf("%s %s\n", d->path, d->value);
            if (d->subdirsOC != NULL)
                LLdirsprint(pDirs, d);
        }
    }
}

pnodeDirs LLdirsdeleteaux(pnodeDirs* pDirs, pDir dir) {
    pnode t;
    pDir d;
    for (t = *(dir->subdirsOC); t != NULL; t = t->next) {
        d = LLdirslookuppath(pDirs, t->path);
        if (d->subdirsOC != NULL)
            *pDirs = LLdirsdeleteaux(pDirs, d);
        *pDirs = deletenodeDirs(*pDirs, d->path);
    }

    return deletenodeDirs(*pDirs, dir->path);
}

void deletetry(pnodeDirs* pDirs, pDir dir) {
    pnode t = *(dir->subdirsOC);
    pDir d;
    for (; t != NULL; t = t->next) {
        d = LLdirslookuppath(pDirs, t->path);
        if (d->subdirsOC != NULL)
            deletetry(pDirs, d);
    }
    *pDirs = deletenodeDirs(*pDirs, dir->path);
}

void LLdirsdelete(pnodeDirs* head, pDir dir) {
    deletetry(head, dir);
}