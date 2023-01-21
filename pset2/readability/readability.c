#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>

int main(void)
{
    //Getting User Input
    string sText = get_string("Text: ");
    int nLength = strlen(sText);

    //Letters
    int nLetterCnt = 0;
    for(int i = 0; i < nLength; i++)
    {
        char cLetter = sText[i];

        if (isupper(cLetter) || islower(cLetter))
        {
            nLetterCnt++;
        };
    }

    printf("%i\n", nLetterCnt);

}
