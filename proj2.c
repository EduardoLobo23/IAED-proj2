/*
 * File: proj2.c
 * Author: Eduardo Lobo
 * Description: A program simulating a hierarchical storage system.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "LLpaths.h"
#include "Path.h"
#include "consts.h"

/* Imprime os comandos disponiveis. */
void help();

/* Termina o programa */
void quit(pnodePaths*);

/* Adiciona ou modifica o valor a armazenar. */
void set(pnodePaths*);

/* Imprime todos os caminhos e valores. */
void print(pnodePaths*);

/* Imprime o valor armazenado. */
void find(pnodePaths*);

/* Lista todos os componentes imediatos de um sub-caminho. */
void list(pnodePaths*);

/* Procura o caminho dado num valor. */
void search(pnodePaths*);

/* Apaga um caminho e todos os subcaminhos. */
void delete (pnodePaths*);

int main() {
    pnodePaths Paths;
    pnodePaths* pPaths = &Paths;
    pPath root = NEWPath(ROOT_NAME, ROOT_LCOMPONENT, NULL_VALUE);
    char command[7];
    LLpathsinit(pPaths);
    LLpathsinsert(pPaths, root);
    while (scanf("%s", command)) {
        if (strcmp(command, "help") == 0)
            help();
        if (strcmp(command, "quit") == 0)
            quit(pPaths);
        if (strcmp(command, "set") == 0)
            set(pPaths);
        if (strcmp(command, "print") == 0)
            print(pPaths);
        if (strcmp(command, "find") == 0)
            find(pPaths);
        if (strcmp(command, "list") == 0)
            list(pPaths);
        if (strcmp(command, "search") == 0)
            search(pPaths);
        if (strcmp(command, "delete") == 0)
            delete (pPaths);
    }
    return 0;
}

void help() {
    puts(HELP_DESCRIPTION);
    puts(QUIT_DESCRIPTION);
    puts(SET_DESCRIPTION);
    puts(PRINT_DESCRIPTION);
    puts(FIND_DESCRIPTION);
    puts(LIST_DESCRIPTION);
    puts(SEARCH_DESCRIPTION);
    puts(DELETE_DESCRIPTION);
}

void quit(pnodePaths* pPaths) {
    LLpathsfree(pPaths);
    exit(0);
}

void set(pnodePaths* pPaths) {
    pPath path = LLpathslookup(pPaths, ROOT_NAME);
    char name[MAX_INPUT_BUFFER] = SEP, value[200], buffer[MAX_INPUT_BUFFER];
    char* component;

    scanf("%s", buffer);
    component = strtok(buffer, SEP);
    while (component != NULL) {
        strcat(name, component);
        if (Pathissubpathof(path, component) == 0) {
            Pathinsertsubpath(path, name, component);
            path = NEWPath(name, component, NULL_VALUE);
            LLpathsinsert(pPaths, path);
        } else {
            path = LLpathslookup(pPaths, name);
        }
        strcat(name, SEP);
        component = strtok(NULL, SEP);
    }
    getchar();
    scanf("%[^\n]", value);
    Pathchangevalue(path, value);
}

void list(pnodePaths* pPaths) {
    pPath path = LLpathslookup(pPaths, ROOT_NAME);
    char buffer[MAX_INPUT_BUFFER], name[MAX_INPUT_BUFFER] = SEP;
    char* component;
    int c = getchar();
    if (c == '\n') {
        Pathlist(path);
        return;
    } else {
        scanf("%s", buffer);
        component = strtok(buffer, SEP);
        while (component != NULL) {
            strcat(name, component);
            strcat(name, SEP);
            component = strtok(NULL, SEP);
        }
        name[strlen(name) - 1] = '\0';
        path = LLpathslookup(pPaths, name);
        if (path == NULL) {
            puts(NOT_FOUND_ERROR);
            return;
        }
        Pathlist(path);
    }
}

void search(pnodePaths* pPaths) {
    pPath path;
    char value[200];
    getchar();
    scanf("%[^\n]", value);
    path = LLpathssearchbyvalue(pPaths, value);
    if (path == NULL) {
        puts(NOT_FOUND_ERROR);
        return;
    }
    puts(path->name);
}

void find(pnodePaths* pPaths) {
    pPath path;
    char buffer[MAX_INPUT_BUFFER], name[MAX_INPUT_BUFFER] = SEP;
    char* component;
    scanf("%s", buffer);
    component = strtok(buffer, SEP);
    while (component != NULL) {
        strcat(name, component);
        strcat(name, SEP);
        component = strtok(NULL, SEP);
    }
    name[strlen(name) - 1] = '\0';
    path = LLpathslookup(pPaths, name);
    if (path == NULL) {
        puts(NOT_FOUND_ERROR);
        return;
    }
    if (strcmp(path->value, NULL_VALUE) == 0) {
        puts(NO_DATA_ERROR);
        return;
    }
    puts(path->value);
}

void print(pnodePaths* pPaths) {
    pPath root = LLpathslookup(pPaths, ROOT_NAME);
    LLpathsprint(pPaths, root);
}

void delete (pnodePaths* pPaths) {
    pPath path = LLpathslookup(pPaths, ROOT_NAME);
    pPath father;
    int count = 0;
    char buffer[MAX_INPUT_BUFFER], name[MAX_INPUT_BUFFER] = SEP, fname[MAX_INPUT_BUFFER] = SEP;
    char *component, *lcomponent;
    int c = getchar();
    if (c == '\n') {
        LLpathsfree(pPaths);
        path = NEWPath(ROOT_NAME, ROOT_LCOMPONENT, NULL_VALUE);
        LLpathsinsert(pPaths, path);
        return;
    }
    scanf("%s", buffer);
    component = strtok(buffer, SEP);
    while (component != NULL) {
        strcat(name, component);
        strcat(name, SEP);
        lcomponent = component;
        component = strtok(NULL, SEP);
        if (component != NULL) {
            strcat(fname, lcomponent);
            strcat(fname, SEP);
        }
        count++;
    }
    name[strlen(name) - 1] = '\0';
    fname[strlen(fname) - 1] = '\0';
    path = LLpathslookup(pPaths, name);
    if (path == NULL) {
        puts(NOT_FOUND_ERROR);
        return;
    }
    if (count == 1)
        father = LLpathslookup(pPaths, ROOT_NAME);
    else
        father = LLpathslookup(pPaths, fname);
    LLdelete(father->icomponentsOC, path->name);
    STdelete(father->icomponentsABC, path->lcomponent);
    LLpathsdelete(pPaths, path);
}