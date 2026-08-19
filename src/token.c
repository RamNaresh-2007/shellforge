#include <stdio.h>
#include <string.h>

#include "token.h"

void token_list_init(token_list_t *list)
{
    list->count = 0;
}

int token_add(token_list_t *list,
              token_type_t type,
              const char *text)
{
    if (list == NULL)
        return 0;

    if (list->count >= MAX_TOKENS)
        return 0;

    list->tokens[list->count].type = type;

    strncpy(list->tokens[list->count].text,
            text,
            MAX_TOKEN_LEN - 1);

    list->tokens[list->count].text[MAX_TOKEN_LEN - 1] = '\0';

    list->count++;

    return 1;
}

void token_print(const token_list_t *list)
{
    if (list == NULL)
        return;

    printf("\n========== TOKENS ==========\n");

    for (int i = 0; i < list->count; i++)
    {
        printf("Token %d: ", i);

        switch (list->tokens[i].type)
        {
        case TOKEN_WORD:
            printf("WORD");
            break;

        case TOKEN_PIPE:
            printf("PIPE");
            break;

        case TOKEN_INPUT:
            printf("INPUT");
            break;

        case TOKEN_OUTPUT:
            printf("OUTPUT");
            break;

        case TOKEN_APPEND:
            printf("APPEND");
            break;

        case TOKEN_BACKGROUND:
            printf("BACKGROUND");
            break;

        case TOKEN_END:
            printf("END");
            break;

        default:
            printf("UNKNOWN");
            break;
        }

        printf(" -> \"%s\"\n",
               list->tokens[i].text);
    }

   printf("============================\n");
}
