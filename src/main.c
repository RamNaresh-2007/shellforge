#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "history.h"

int main(void)
{
    // Display welcome banner
    printf("===========================================\n");
    printf("           ShellForge\n");
    printf("A Unix style Shell written in C\n");
    printf("===========================================\n");

    // Initialize history
    using_history();

    char *line;

    while (1)
    {
        line = readline("shellforge$ ");

        if (line == NULL)
        {
            printf("GoodBye!\n");
            break;
        }

        // Ignore empty input
        if (strlen(line) == 0)
        {
            free(line);
            continue;
        }

        // Store command in history
        add_history(line);

        // History command
        if (strcmp(line, "history") == 0)
        {
            print_history();
            free(line);
            continue;
        }

        // Exit command
        if (strcmp(line, "exit") == 0)
        {
            free(line);
            printf("Exiting...\n");
            break;
        }

        printf("YOU ENTERED : %s\n", line);

        free(line);
    }

    return 0;
}
