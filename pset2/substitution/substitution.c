#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>

bool checkArg(int, char **);
int getPosition(char);
char *getCiphertext(char *, char *);

int main(int argc, char **argv)
{
    if (checkArg(argc, argv) == false)
    {
        printf("usage: ./caesar key\n");
        return 1;
    }

    char *key = strdup(argv[1]);
    char *plaintext = get_string("plaintext:  ");
    char *ciphertext = getCiphertext(key, plaintext);

    printf("ciphertext: %s", ciphertext);
    printf("\n");
    free(key);
    free(ciphertext);
    return 0;
}

bool checkArg(int argc, char **argv)
{

    if (argc != 2)
    {
        return false;
    }

    size_t len = strlen(argv[1]);

    if (len != 26)
    {
        return false;
    }

    if (strspn("ABCDEFGHIJKLMNOPQRSTUVWXYZ", argv[1]) == len || strspn("abcdefghijklmnopqrstuvwxyz", argv[1]) == len)
    {
        return true;
    }

    return false;
}

int getPosition(char character)
{
    if (isupper(character))
    {
        return character - 65;
    }

    if (islower(character))
    {
        return character - 97;
    }

    return character;
}

char *getCiphertext(char *key, char *plaintext)
{
    size_t len = strlen(plaintext);
    char *result = malloc(len);

    for (int i = 0; i < (int)len; i++)
    {
        char character = plaintext[i];
        int position = getPosition(plaintext[i]);

        if (isupper(character))
        {
            result[i] = toupper(key[position]);
        }
        else if (islower(character))
        {
            result[i] = tolower(key[position]);
        }
        else
        {
            result[i] = character;
        }
    }

    return result;
}
