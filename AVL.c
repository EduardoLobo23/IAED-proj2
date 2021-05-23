#include "AVL.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

link NEW(char* path, link l, link r) {
    link x = (link)malloc(sizeof(struct STnode));
    x->path = (char*)malloc(sizeof(char) * (strlen(path) + 1));
    strcpy(x->path, path);
    x->l = l;
    x->r = r;
    return x;
}

void STinit(link* head) {
    *head = NULL;
}

link insertR(link head, char* path) {
    if (head == NULL)
        return NEW(path, NULL, NULL);
    if (strcmp(path, head->path) < 0)
        head->l = insertR(head->l, path);
    else
        head->r = insertR(head->r, path);
    return head;
}

void STinsert(link* head, char* path) {
    *head = insertR(*head, path);
}

char* searchR(link head, char* path) {
    if (head == NULL) {
        return "";
    }
    if (strcmp(path, head->path) == 0)
        return head->path;
    if (strcmp(path, head->path) < 0)
        return searchR(head->l, path);
    else
        return searchR(head->r, path);
}

char* STsearch(link head, char* key) {
    return searchR(head, key);
}

link max(link head) {
    if (head == NULL || head->r == NULL)
        return head;
    return max(head->r);
}

link min(link head) {
    if (head == NULL || head->l == NULL)
        return head;
    return min(head->l);
}

link deleteR(link head, char* path) {
    if (head == NULL)
        return head;
    else if (strcmp(path, head->path) < 0)
        head->l = deleteR(head->l, path);
    else if (strcmp(head->path, path) < 0)
        head->r = deleteR(head->r, path);
    else {
        if (head->l != NULL && head->r != NULL) {
            link aux = max(head->l);
            char* x = head->path;
            head->path = aux->path;
            aux->path = x;
            head->l = deleteR(head->l, aux->path);
        } else {
            link aux = head;
            if (head->l == NULL && head->r == NULL)
                head = NULL;
            else if (head->l == NULL)
                head = head->r;
            else
                head = head->l;
            free(aux->path);
            free(aux);
        }
    }
    return head;
}

void STdelete(link* head, char* key) {
    *head = deleteR(*head, key);
}

int count(link head) {
    if (head == NULL)
        return 0;
    return count(head->r) + count(head->l) + 1;
}

int STcount(link head) {
    return count(head);
}

void sortR(link head) {
    if (head == NULL)
        return;
    sortR(head->l);
    puts(head->path);
    sortR(head->r);
}

void STsort(link head) {
    sortR(head);
}

link freeR(link head) {
    if (head == NULL)
        return head;
    head->l = freeR(head->l);
    head->r = freeR(head->r);
    return deleteR(head, head->path);
}

void STfree(link* head) {
    *head = freeR(*head);
    free(head);
}

int height(link head) {
    int u, v;

    if (head == NULL)
        return -1;
    u = height(head->l);
    v = height(head->r);
    if (u > v)
        return u + 1;
    return v + 1;
}

void traversePreOrder(link head) {
    if (head == NULL)
        return;
    puts(head->path);
    traversePreOrder(head->l);
    traversePreOrder(head->r);
}

void traverseInOrder(link head) {
    if (head == NULL)
        return;
    traverseInOrder(head->l);
    puts(head->path);
    traverseInOrder(head->r);
}

void traversePostOrder(link head) {
    if (head == NULL)
        return;
    traversePostOrder(head->l);
    traversePostOrder(head->r);
    puts(head->path);
}

link rotL(link head) {
    link x = head->r;
    head->r = x->l;
    x->l = head;
    return x;
}

link rotR(link head) {
    link x = head->l;
    head->l = x->r;
    x->r = head;
    return x;
}