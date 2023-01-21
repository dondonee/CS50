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
    int nWordCnt = 0;
    for(int i = 0; i < nLength; i++)
    {
        char cLetter = sText[i];

        if (isupper(cLetter) || islower(cLetter))
        {
            nLetterCnt++;
        };

        if (cLetter == ' ' || (cLetter == '.' && i == nLength -1))
        {
            nWordCnt++;
        }
    }

    printf("%i letter(s)\n", nLetterCnt);
    printf("%i word(s)\n", nWordCnt);

}
