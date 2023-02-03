#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>

#define ALPHABET_LEN 26

bool checkArg(int argc, char **argv);
char *getCiphertext(char *key, char *plaintext);

int main(int argc, char **argv)
{
    if (!checkArg(argc, argv))
    {
        return 1;
    }

    char *plaintext = get_string("plaintext:  ");
    char *ciphertext = getCiphertext(argv[1], plaintext);

    printf("ciphertext: %s", ciphertext);
    printf("\n");
    free(ciphertext);

    return 0;
}

bool checkArg(int argc, char **argv)
{

    if (argc != 2)
    {
        printf("usage: ./caesar key\n");
        return false;
    }

    if (strlen(argv[1]) != ALPHABET_LEN)
    {
        printf("Key must contain 26 characters.\n");
        return false;
    }

    char temp[ALPHABET_LEN];

    for (int i = 0; i < ALPHABET_LEN; i++)
    {
        temp[i] = toupper(argv[1][i]);
    }

    if (strspn(temp, "ABCDEFGHIJKLMNOPQRSTUVWXYZ") != ALPHABET_LEN)
    {
        printf("Key must only contain alphabetic characters.\n");
        return false;
    }

    if (strspn("ABCDEFGHIJKLMNOPQRSTUVWXYZ", temp) != ALPHABET_LEN)
    {
        printf("Key must not contain repeated characters.\n");
        return false;
    }

    return true;
}

char *getCiphertext(char *key, char *plaintext)
{
    size_t len = strlen(plaintext);
    char *result = malloc(len);

    for (int i = 0; i < (int)len; i++)
    {
        char character = plaintext[i];
        int index;

        if (isupper(character))
        {
            index = character - 'A';
            result[i] = toupper(key[index]);
        }
        else if (islower(character))
        {
            index = character - 'a';
            result[i] = tolower(key[index]);
        }
        else
        {
            result[i] = character;
        }
    }

    return result;
}
