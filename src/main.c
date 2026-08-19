#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "token.h"
#include "lexer.h"
#include "parser.h"
#include "expand.h"

int main(void)
{
    char *input;

    while (1)
    {
        input = readline("shellforge> ");

        if (input == NULL)
        {
            printf("\n");
            break;
        }

        if (input[0] == '\0')
        {
            free(input);
            continue;
        }

        add_history(input);

        token_list_t tokens;

        lexer(input, &tokens);

        token_print(&tokens);

        pipeline_t pipeline;

        if (!parser(&tokens, &pipeline))
        {
            free(input);
            continue;
        }

        expand_variables(&pipeline);

        pipeline_print(&pipeline);

        free(input);
    }

    return 0;
}
