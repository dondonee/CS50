#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

float countLetter(string, int);
float countWord(string, int);
float countSentence(string, int);
int calculateIndex (float letter, float word, float sentence);

int main(void)
{
    // Getting User Input
    string text = get_string("Text: ");
    int textLen = strlen(text);

    // Count
    float letterCnt = countLetter(text, textLen);
    float wordCnt = countWord(text, textLen);
    int sentenceCnt = countSentence(text, textLen);

    // Coleman-Liau Index
    int nGrade = calculateIndex(letterCnt, wordCnt, sentenceCnt);

    // Print the result
    if (nGrade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (nGrade > 15)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", nGrade);
    }
}

float countLetter(string text, int length)
{
    int result = 0;
    for (int i = 0; i < length; i++)
    {
        char c = text[i];

        if (isalpha(c))
        {
            result++;
        };
    }

    return result;
}

float countWord(string text, int length)
{
    int result = 1;

    for (int i = 0; i < length; i++)
    {
        char c = text[i];

        if (c == ' ' && isalpha(text[i + 1]))
        {
            result++;
        }
    }

    return result;
}

float countSentence(string text, int length)
{
    int result = 0;

    for (int i = 0; i < length; i++)
    {
        char c = text[i];

        if (c == '.' || c == '!' || c == '?' || c == ':')
        {
            char str1[2];
            char str2[3];
            strncpy(str1, &text[i - 2], 2);
            strncpy(str2, &text[i - 3], 3);

            if (strncmp(str1, "Mr", 2) != 0 && strncmp(str2, "Mrs", 3) != 0)
            {
                result++;
            }
        }
    }

    return result;
}

int calculateIndex (float letter, float word, float sentence)
{
    float L = letter / word * 100.00;
    float S = sentence / word * 100.00;
    int result = round(0.0588 * L - 0.296 * S - 15.8);

    return result;
}
