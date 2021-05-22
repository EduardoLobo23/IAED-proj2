/*
 * File: proj2.c
 * Author: Eduardo Lobo
 * Description:
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Dir.h"
#include "LLdirs.h"
#include "consts.h"

/* Imprime os comandos disponiveis. */
void help();

/* Termina o programa */
void quit(pnodeDirs*);

/* Adiciona ou modifica o valor a armazenar. */
void set(pnodeDirs*);

/* Imprime todos os caminhos e valores. */
void print(pnodeDirs*);

/* Imprime o valor armazenado. */
void find(pnodeDirs*);

/* Lista todos os componentes de um caminho. */
void list(pnodeDirs*);

/* Procura o caminho dado num valor. */
void search(pnodeDirs*);

/* Apaga um caminho e todos os subcaminhos. */
void delete (pnodeDirs*);

int main() {
    pnodeDirs Dirs;
    pnodeDirs* pDirs = &Dirs;
    pDir root = NEWDir("root", "root", "");
    char command[7];

    LLdirsinit(pDirs);

    LLdirsinsert(pDirs, root);

    while (scanf("%s", command)) {
        if (strcmp(command, "help") == 0)
            help();
        if (strcmp(command, "quit") == 0)
            quit(pDirs);
        if (strcmp(command, "set") == 0)
            set(pDirs);
        if (strcmp(command, "print") == 0)
            print(pDirs);
        if (strcmp(command, "find") == 0)
            find(pDirs);
        if (strcmp(command, "list") == 0)
            list(pDirs);
        if (strcmp(command, "search") == 0)
            search(pDirs);
        if (strcmp(command, "delete") == 0)
            delete (pDirs);
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

void quit(pnodeDirs* pDirs) {
    LLdirsfree(pDirs);
    exit(0);
}

void set(pnodeDirs* pDirs) {
    pDir x = LLdirslookup(pDirs, "root");
    char path[200] = "/", value[200], buffer[200];
    char* token;

    scanf("%s", buffer);
    token = strtok(buffer, "/");
    while (token != NULL) {
        strcat(path, token);
        if (subdirofDir(x, token) == 0) {
            insertsubDir(x, path, token);
            x = NEWDir(path, token, "");
            LLdirsinsert(pDirs, x);
        } else {
            x = LLdirslookuppath(pDirs, path);
        }
        strcat(path, "/");
        token = strtok(NULL, "/");
    }
    getchar();
    scanf("%[^\n]", value);
    changevalueDir(x, value);
}

void list(pnodeDirs* pDirs) {
    pDir x = LLdirslookup(pDirs, "root");
    char buffer[200], path[200] = "/";
    char* token;
    int c = getchar();
    if (c == '\n') {
        listDir(x);
        return;
    } else {
        scanf("%s", buffer);
        token = strtok(buffer, "/");
        while (token != NULL) {
            strcat(path, token);
            strcat(path, "/");
            token = strtok(NULL, "/");
        }
        path[strlen(path) - 1] = '\0';
        x = LLdirslookuppath(pDirs, path);
        if (x == NULL) {
            puts(NOT_FOUND_ERROR);
            return;
        }
        listDir(x);
    }
}

void search(pnodeDirs* pDirs) {
    pDir x;
    char value[200];
    getchar();
    scanf("%[^\n]", value);
    x = LLdirssearch(pDirs, value);
    if (x == NULL) {
        puts(NOT_FOUND_ERROR);
        return;
    }
    puts(x->path);
}

void find(pnodeDirs* pDirs) {
    pDir x;
    char buffer[200], path[200] = "/";
    char* token;
    scanf("%s", buffer);
    token = strtok(buffer, "/");
    while (token != NULL) {
        strcat(path, token);
        strcat(path, "/");
        token = strtok(NULL, "/");
    }
    path[strlen(path) - 1] = '\0';
    x = LLdirslookuppath(pDirs, path);
    if (x == NULL) {
        puts(NOT_FOUND_ERROR);
        return;
    }
    if (strcmp(x->value, "") == 0) {
        puts(NO_DATA_ERROR);
        return;
    }
    puts(x->value);
}

void print(pnodeDirs* pDirs) {
    pDir root = LLdirslookup(pDirs, "root");
    LLdirsprint(pDirs, root);
}

void delete (pnodeDirs* pDirs) {
    pDir x = LLdirslookup(pDirs, "root");
    char buffer[200], path[200] = "";
    char *token, *name;
    int c = getchar();
    if (c == '\n') {
        LLdirsfree(pDirs);
        x = NEWDir("root", "root", "");
        LLdirsinsert(pDirs, x);
        return;
    }
    scanf("%s", buffer);
    token = strtok(buffer, "/");
    while (token != NULL) {
        strcat(path, token);
        name = token;
        token = strtok(NULL, "/");
    }
    x = LLdirslookup(pDirs, name);
    freeDir(x);
}