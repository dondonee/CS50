#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>

bool checkArg(int, char **);
char encrpyt(int, char);

int main(int argc, char **argv)
{
    if (checkArg(argc, argv) == false)
    {
        printf("usage: ./caesar key\n");
        return 1;
    }

    int key = atoi(argv[1]);
    char *plaintext = get_string("plaintext : ");
    char tempChar = encrpyt(key, plaintext[0]);

    printf("%c\n", tempChar);
}

// 명령행 인자가 적절한 값인지 판단
bool checkArg(int argc, char **argv)
{
    bool result = true;

    if (argc != 2)
    {
        result = false;
    }
    else
    {
        int len = (int)strlen(argv[1]);
        for (int i = 0; i < len; i++)
        {
            char element = argv[1][i];
            if (isdigit(element) == 0)
            {
                result = false;
            }
        }
    }

    return result;
}

// 한 문자를 암호화
char encrpyt(int key, char character)
{
    int result;
    int position;

    if (isupper(character))
    {
        position = (character - 65 + key) % 26;
        result = 65 + position;
    }
    else
    {
        position = (character - 97 + key) % 26;
        result = 97 + position;
    }

    return (char)result;
}
