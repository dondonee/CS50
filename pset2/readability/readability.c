#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

int main(void)
{
    // Getting User Input
    string sText = get_string("Text: ");
    int nLength = strlen(sText);

    // Count
    int nLetterCnt = 0;
    int nWordCnt = 1;
    int nSentenceCnt = 0;
    for (int i = 0; i < nLength; i++)
    {
        char cLetter = sText[i];

        // Letters
        if (isalpha(cLetter) != 0)
        {
            nLetterCnt++;
        };

        // Words
        if (cLetter == ' ' && isalpha(sText[i + 1]) != 0)
        {
            nWordCnt++;
        }

        // Sentences
        if (cLetter == '.' || cLetter == '!' || cLetter == '?' || cLetter == ':')
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

    // Coleman-Liau Index
    float L = ((float)nLetterCnt / (float)nWordCnt) * 100.00;
    float S = ((float)nSentenceCnt / (float)nWordCnt) * 100.00;
    float nIndex = 0.0588 * L - 0.296 * S - 15.8;
    int nGrade = round(nIndex);

    // Print the result
    if (nGrade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (nGrade > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", nGrade);
    }
}
