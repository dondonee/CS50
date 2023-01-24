#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>

int main(void)
{
    // Getting User Input
    string sText = get_string("Text: ");
    int nLength = strlen(sText);

    // Letters
    int nLetterCnt = 0;
    int nWordCnt = 0;
    int nSentenceCnt = 0;
    for (int i = 0; i < nLength; i++)
    {
        char cLetter = sText[i];

        if (isupper(cLetter) || islower(cLetter))
        {
            nLetterCnt++;
        };

        if (cLetter == ' ' || (cLetter == '.' && i == nLength - 1))
        {
            nWordCnt++;
        }

        if (cLetter == '.')
        {
            char str1[2];
            char str2[3];
            strncpy(str1, &sText[i - 2], 2);
            strncpy(str2, &sText[i - 3], 3);

            if (strncmp(str1, "Mr", 2) != 0 && strncmp(str2, "Mrs", 3) != 0)
            {
                nSentenceCnt++;
            }
        }
    }

    printf("%i letter(s)\n", nLetterCnt);
    printf("%i word(s)\n", nWordCnt);
    printf("%i sentence(s)\n", nSentenceCnt);
}
