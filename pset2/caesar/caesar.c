#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>

bool checkArg(int, char **) ;

int main(int argc, char **argv)
{
    if (checkArg(argc, argv))
    {
        printf("Success\n");
        int k = atoi(argv[1]);
        printf("%i\n", k);
        return 0;
    }
    else
    {
        printf("usage: ./caesar key\n");
        return 1;
    }
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
        for (int i = 0; i < (int)strlen(argv[1]) - 1; i++)
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
