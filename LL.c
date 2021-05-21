#include "LL.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void LLinit(pnode* head) {
    *head = NULL;
}

pnode NEWnode(char* path) {
    pnode x = (pnode)malloc(sizeof(struct node));
    x->path = (char*)malloc(sizeof(char) * (strlen(path) + 1));
    strcpy(x->path, path);
    x->next = NULL;
    return x;
}

pnode insertnode(pnode head, char* path) {
    pnode x;
    if (head == NULL)
        return NEWnode(path);
    for (x = head; x->next != NULL; x = x->next)
        ;
    x->next = NEWnode(path);
    return head;
}

void LLinsert(pnode* head, char* path) {
    *head = insertnode(*head, path);
}

void LLprint(pnode head) {
    pnode t;
    for (t = head; t != NULL; t = t->next)
        puts(t->path);
}

pnode deletenode(pnode head, char* path) {
    pnode t;
    for (t = head; t != NULL; t = t->next) {
        if (strcmp(t->path, path) == 0) {
            if (t == head)
                head = t->next;
            free(t->path);
            free(t);
            break;
        }
    }
    return head;
}

pnode freenode(pnode head) {
    if (head == NULL)
        return head;
    head->next = freenode(head->next);
    return deletenode(head, head->path);
}

void LLfree(pnode* head) {
    *head = freenode(*head);
    free(head);
}
