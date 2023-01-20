#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int num;
    bool check = true;

    do
    {
        num = get_int("Height: ");

        if (num > 0 && num < 9)
        {
            check = false;
        }
    } while (check);


    for (int i = 0; i < num; i++)
    {
        //right-alignd pyramid
        for (int j = (num - 1); j > i; j--)\
        {
            printf(" ");
        }

        for (int j = 0; j < (i + 1); j++)
        {
            printf("#");
        }

        printf("  ");

        //left-aligned pyramid
        for (int j = 0; j < (i + 1); j++)
        {
            printf("#");
        }

        for (int j = (num - 1); j > i; j--)\
        {
            printf(" ");
        }

        printf("\n");
    }

    
}
