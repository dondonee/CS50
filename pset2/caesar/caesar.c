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

    const int key = atoi(argv[1]);
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
    if (isalpha(character))
    {
        return (char)((character - (islower(character) ? 97 : 65) + key) % 26 + (islower(character) ? 97 : 65));
    }
    return character;
}

char *getCiphertext(int key, char *plaintext)
{
    size_t len = strlen(plaintext);
    char *result = malloc(len + 1);

    for (int i = 0; i < (int)len; i++)
    {
        result[i] = encrypt(key, plaintext[i]);
    }

    result[len] = '\0';

    return result;
}
