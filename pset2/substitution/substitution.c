#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>

#define ALPHABET_LEN 26

bool checkArg(int, char **);
int getPosition(char);
char *getCiphertext(char *, char *);

int main(int argc, char **argv)
{
    if (checkArg(argc, argv) == false)
    {
        return 1;
    }

    char *key = malloc(strlen(argv[1]));
    key = strcpy(key, argv[1]);
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
        if (islower(argv[1][i]))
        {
            temp[i] = toupper(argv[1][i]);
        }
        else
        {
            temp[i] = argv[1][i];
        }
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
