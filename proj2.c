/*
 * File: proj.c
 * Author: Eduardo Lobo
 * Description:
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "consts.h"

/* Imprime os comandos disponiveis. */
void help();

/* Adiciona ou modifica o valor a armazenar. */
/*void set(); */

/* Imprime todos os caminhos e valores. */
/*void print(); */

/* Imprime o valor armazenado. */
/*void find(); */

/* Lista todos os componentes de um caminho. */
/*void list(); */

/* Procura o caminho dado num valor. */
/*void search(); */

/* Apaga um caminho e todos os subcaminhos. */
/*void delete (); */

int main() {
    char command[10];
    while (scanf("%s", command) && strcmp(command, "quit") != 0) {
        if (strcmp(command, "help") == 0)
            help();
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