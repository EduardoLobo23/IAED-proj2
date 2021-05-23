/*
 * File: LLpaths.c
 * Author: Eduardo Lobo
 * Description: Creation and manipulation of ADT "LLpaths".
 */

#include "LLpaths.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*----------------------------------------------------------------------*/

/* Allocates memory for a new node and assigns it an ADT Path. */
pnodePaths NEWnodePaths(pPath path) {
    pnodePaths x = (pnodePaths)malloc(sizeof(struct nodePaths));
    x->path = path;
    x->next = NULL;
    return x;
}

/* Inserts a new node on the list. */
pnodePaths insertnodePaths(pnodePaths head, pPath path) {
    pnodePaths x;
    if (head == NULL)
        return NEWnodePaths(path);
    for (x = head; x->next != NULL; x = x->next)
        ;
    x->next = NEWnodePaths(path);
    return head;
}

/* Deletes the node that contains the path with a certain name. */
pnodePaths deletenodePaths(pnodePaths head, char* name) {
    pnodePaths t, prev;
    for (t = head, prev = NULL; t != NULL; prev = t, t = t->next) {
        if (strcmp(t->path->name, name) == 0) {
            if (t == head)
                head = t->next;
            else
                prev->next = t->next;
            Pathfree(t->path);
            free(t);
            break;
        }
    }
    return head;
}

/* Frees the memory allocated for the whole tree, each node at a time. */
pnodePaths freenodePaths(pnodePaths head) {
    if (head == NULL)
        return head;
    head->next = freenodePaths(head->next);
    return deletenodePaths(head, head->path->name);
}

/* Searchs for the node that contains a path with a certain name. */
pnodePaths lookupPaths(pnodePaths head, char* name) {
    pnodePaths t;
    for (t = head; t != NULL; t = t->next)
        if (strcmp(t->path->name, name) == 0)
            return t;
    return NULL;
}

/* Searchs for the node that contains a path with a certain value. */
pPath searchPaths(pnodePaths* head, pPath path, char* value) {
    pnode t;
    pPath p;

    if (strcmp(path->value, value) == 0)
        return path;
    if (path->icomponentsOC != NULL)
        for (t = *(path->icomponentsOC); t != NULL; t = t->next) {
            p = LLpathslookup(head, t->name);
            if (p != NULL) {
                if (strcmp(p->value, value) == 0)
                    return p;
                p = searchPaths(head, p, value);
                if (p != NULL)
                    return p;
            }
        }
    return NULL;
}

/* Deletes the node that contains a certain path.
If that path has subpaths, deletes them too. */
void deletepath(pnodePaths* pPaths, pPath path) {
    pnode t = *(path->icomponentsOC);
    pPath p;
    for (; t != NULL; t = t->next) {
        p = LLpathslookup(pPaths, t->name);
        if (p->icomponentsOC != NULL)
            deletepath(pPaths, p);
    }
    *pPaths = deletenodePaths(*pPaths, path->name);
}

/*----------------------------------------------------------------------*/

void LLpathsinit(pnodePaths* head) {
    *head = NULL;
}

void LLpathsinsert(pnodePaths* head, pPath path) {
    *head = insertnodePaths(*head, path);
}

pPath LLpathslookup(pnodePaths* head, char* name) {
    pnodePaths aux;
    aux = lookupPaths(*head, name);
    if (aux == NULL)
        return NULL;
    return aux->path;
}

void LLpathsprint(pnodePaths* pPaths, pPath path) {
    pnode t = *(path->icomponentsOC);
    pPath p;
    for (; t != NULL; t = t->next) {
        p = LLpathslookup(pPaths, t->name);
        if (p != NULL) {
            if (strcmp(p->value, "") != 0)
                printf("%s %s\n", p->name, p->value);
            if (p->icomponentsOC != NULL)
                LLpathsprint(pPaths, p);
        }
    }
}

pPath LLpathssearchbyvalue(pnodePaths* head, char* value) {
    pPath path = LLpathslookup(head, "root");
    path = searchPaths(head, path, value);
    if (path == NULL)
        return NULL;
    return path;
}

void LLpathsdelete(pnodePaths* head, pPath path) {
    deletepath(head, path);
}

void LLpathsfree(pnodePaths* head) {
    *head = freenodePaths(*head);
}