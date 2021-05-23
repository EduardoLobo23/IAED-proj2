/*
 * File: AVL.c
 * Author: Eduardo Lobo
 * Description: Creation and manipulation of ADT "AVL".
 */

#include "AVL.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*----------------------------------------------------------------------*/

/* Allocates memmory for a new node and assigns it a string. */
link NEW(char* lcomponent, link l, link r) {
    link x = (link)malloc(sizeof(struct STnode));
    x->lcomponent = (char*)malloc(sizeof(char) * (strlen(lcomponent) + 1));
    strcpy(x->lcomponent, lcomponent);
    x->l = l;
    x->r = r;
    return x;
}

/* Inserts a new node on the tree. */
link insertR(link head, char* lcomponent) {
    if (head == NULL)
        return NEW(lcomponent, NULL, NULL);
    if (strcmp(lcomponent, head->lcomponent) < 0)
        head->l = insertR(head->l, lcomponent);
    else
        head->r = insertR(head->r, lcomponent);
    return head;
}

/* Searchs for the node that contains a certain string. */
char* searchR(link head, char* lcomponent) {
    if (head == NULL) {
        return "";
    }
    if (strcmp(lcomponent, head->lcomponent) == 0)
        return head->lcomponent;
    if (strcmp(lcomponent, head->lcomponent) < 0)
        return searchR(head->l, lcomponent);
    else
        return searchR(head->r, lcomponent);
}

/* Traverses the tree in order, printing each nodes' content. */
void sortR(link head) {
    if (head == NULL)
        return;
    sortR(head->l);
    puts(head->lcomponent);
    sortR(head->r);
}

/* Returns the node that contains the biggest value, in this case,
the string that comes last alphabetically . */
link max(link head) {
    if (head == NULL || head->r == NULL)
        return head;
    return max(head->r);
}

/* Deletes a certain node from the tree. */
link deleteR(link head, char* lcomponent) {
    if (head == NULL)
        return head;
    else if (strcmp(lcomponent, head->lcomponent) < 0)
        head->l = deleteR(head->l, lcomponent);
    else if (strcmp(head->lcomponent, lcomponent) < 0)
        head->r = deleteR(head->r, lcomponent);
    else {
        if (head->l != NULL && head->r != NULL) {
            link aux = max(head->l);
            char* x = head->lcomponent;
            head->lcomponent = aux->lcomponent;
            aux->lcomponent = x;
            head->l = deleteR(head->l, aux->lcomponent);
        } else {
            link aux = head;
            if (head->l == NULL && head->r == NULL)
                head = NULL;
            else if (head->l == NULL)
                head = head->r;
            else
                head = head->l;
            free(aux->lcomponent);
            free(aux);
        }
    }
    return head;
}

/* Frees the memory allocated for the whole tree, each node at a time. */
link freeR(link head) {
    if (head == NULL)
        return head;
    head->l = freeR(head->l);
    head->r = freeR(head->r);
    return deleteR(head, head->lcomponent);
}

/*----------------------------------------------------------------------*/

void STinit(link* head) {
    *head = NULL;
}

void STinsert(link* head, char* lcomponent) {
    *head = insertR(*head, lcomponent);
}

char* STsearch(link head, char* lcomponent) {
    return searchR(head, lcomponent);
}

void STsort(link head) {
    sortR(head);
}

void STdelete(link* head, char* lcomponent) {
    *head = deleteR(*head, lcomponent);
}

void STfree(link* head) {
    *head = freeR(*head);
    free(head);
}