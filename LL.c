/*
 * File: LL.c
 * Author: Eduardo Lobo
 * Description: Creation and manipulation of ADT "LL".
 */

#include "LL.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*----------------------------------------------------------------------*/

/* Allocates memory for a new node and assigns it 2 strings. */
pnode NEWnode(char* name, char* lcomponent) {
    pnode x = (pnode)malloc(sizeof(struct node));
    x->name = (char*)malloc(sizeof(char) * (strlen(name) + 1));
    strcpy(x->name, name);
    x->lcomponent = (char*)malloc(sizeof(char) * (strlen(lcomponent) + 1));
    strcpy(x->lcomponent, lcomponent);
    x->next = NULL;
    return x;
}

/* Inserts a new node on the list. */
pnode insertnode(pnode head, char* name, char* lcomponent) {
    pnode x;
    if (head == NULL)
        return NEWnode(name, lcomponent);
    for (x = head; x->next != NULL; x = x->next)
        ;
    x->next = NEWnode(name, lcomponent);
    return head;
}

/* Searchs for the node with a certain name. */
pnode lookupnode(pnode head, char* name) {
    pnode t;
    for (t = head; t != NULL; t = t->next)
        if (strcmp(t->name, name) == 0)
            return t;
    return NULL;
}

/* Deletes the node with a certain name. */
pnode deletenode(pnode head, char* name) {
    pnode t, prev;
    for (t = head, prev = NULL; t != NULL; prev = t, t = t->next) {
        if (strcmp(t->name, name) == 0) {
            if (t == head)
                head = t->next;
            else
                prev->next = t->next;
            free(t->name);
            free(t->lcomponent);
            free(t);
            break;
        }
    }
    return head;
}

/* Frees the memory allocated for the whole tree, each node at a time. */
pnode freenode(pnode head) {
    if (head == NULL)
        return head;
    head->next = freenode(head->next);
    return deletenode(head, head->name);
}

/*----------------------------------------------------------------------*/

void LLinit(pnode* head) {
    *head = NULL;
}

void LLinsert(pnode* head, char* name, char* lcomponent) {
    *head = insertnode(*head, name, lcomponent);
}

void LLlookup(pnode* head, char* name) {
    *head = lookupnode(*head, name);
}

void LLprint(pnode head) {
    pnode t;
    for (t = head; t != NULL; t = t->next) {
        puts(t->name);
    }
}

void LLdelete(pnode* head, char* name) {
    *head = deletenode(*head, name);
}

void LLfree(pnode* head) {
    *head = freenode(*head);
    free(head);
}