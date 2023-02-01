#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>

bool checkArg(int, char **);

int main(int argc, char **argv)
{
    if (checkArg(argc, argv) == false)
    {
        printf("usage: ./caesar key\n");
        return 1;
    }
    else
    {
        printf("Succces.\n");
    }

    char *key = strdup(argv[1]);
    char *plaintext = get_string("plaintext:  ");

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
