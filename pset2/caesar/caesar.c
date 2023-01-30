#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>

bool checkArg(int, char **);
char encrypt(int, char);
char *getCiphertext(int, char *);

int main(int argc, char **argv)
{
    if (checkArg(argc, argv) == false)
    {
        printf("usage: ./caesar key\n");
        return 1;
    }

    int key = atoi(argv[1]);
    char *plaintext = get_string("plaintext:  ");
    char *ciphertext = getCiphertext(key, plaintext);

    printf("ciphertext: %s\n", ciphertext);
    free(ciphertext);

    return 0;
}

// 명령행 인자가 적절한 값인지 판단
bool checkArg(int argc, char **argv)
{
    if (argc != 2 || strspn(argv[1], "0123456789") != strlen(argv[1]))
    {
        return false;
    }

    return true;
}

// 한 문자를 암호화
char encrypt(int key, char character)
{
    int result;
    int position;

    if (isupper(character))
    {
        position = (character - 65 + key) % 26;
        result = 65 + position;
    }
    else if (islower(character))
    {
        position = (character - 97 + key) % 26;
        result = 97 + position;
    }
    else
    {
        result = character;
    }

    return (char)result;
}

char *getCiphertext(int key, char *plaintext)
{
    int len = strlen(plaintext);
    char *result = malloc(len + 1);

    for (int i = 0; i < len; i++)
    {
        result[i] = encrypt(key, plaintext[i]);
    }

    result[len] = '\0';

    return result;
}
