/* Maximum number of characters an instruction can have. */
#define MAX_INPUT_BUFFER 65535 + 1

/* Separator that form paths */
#define SEP "/"

/*----------------------------------------------------------------------*/

/* Description of "help" command. */
#define HELP_DESCRIPTION "help: Imprime os comandos disponíveis."

/* Description of "quit" command. */
#define QUIT_DESCRIPTION "quit: Termina o programa."

/* Description of "set" command. */
#define SET_DESCRIPTION "set: Adiciona ou modifica o valor a armazenar."

/* Description of "print" command. */
#define PRINT_DESCRIPTION "print: Imprime todos os caminhos e valores."

/* Description of "find" command. */
#define FIND_DESCRIPTION "find: Imprime o valor armazenado."

/* Description of "list" command. */
#define LIST_DESCRIPTION "list: Lista todos os componentes imediatos de um sub-caminho."

/* Description of "search" command. */
#define SEARCH_DESCRIPTION "search: Procura o caminho dado um valor."

/* Description of "delete" command. */
#define DELETE_DESCRIPTION "delete: Apaga um caminho e todos os subcaminhos."

/*----------------------------------------------------------------------*/

/* Error printed if the instruction given suparsses the maximum. */
#define NO_MEMORY_ERROR "No memory"

/* Error printed if no path was found in the system. */
#define NOT_FOUND_ERROR "not found"

/* Error printed if the corresponding path has no value assigned. */
#define NO_DATA_ERROR "no data"