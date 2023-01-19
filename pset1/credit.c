#include <stdio.h>
#include <cs50.h>
#include <math.h>
/*
    $$ Pseudocode:
    사용자에게 카드번호 입력을 받아 변수에 저장한다.
    배열의 길이를 계산한다.
    길이에 맞는 배열을 생성한다.
    한 자리씩 각 요소에 저장한다.
    곱하기 연산
        뒤에서 두번째 자리부터, 한 자리씩 건너 뛰며 2를 곱한 뒤, 저장한다.
    더하기 연산 - 0번쨰 요소부터 하나씩 가산하며 각 자릿수의 총 합을 구한다.
        10 이상인 경우 1을 더하고 뒷자리를 더한다.
*/
int main(void)
{
    // 카드번호 프롬프트
    long n = get_long("Number: ");

    // 카드번호의 자리수 구하기
    int count = 0;
    long nTemp = n;
    while (nTemp != 0)
    {
        nTemp = nTemp / 10;
        count++;
    }

    // 카드번호 배열에 한자리씩 저장하기
    int numbers[count];
    int exponent = count - 1;
    nTemp = n;
    for (int i = 0; i < count; i++)
    {
        long digit = (long)pow(10.0, (double)exponent - i);
        numbers[i] = (int)(nTemp / digit);
        nTemp %= digit;
    }

    // 카드번호 자릿수의 홀짝 판단. 총 자릿수가 짝수 -> 배열[짝수]일때 곱하기 2
    int check = count % 2;

    // 대상 digit에 곱하기 2
    for (int i = 0; i < count; i++)
    {
        if (i % 2 == check)
        {
            numbers[i] *= 2;
        }
    }

    int result = 0;
    for (int i = 0; i < count; i++)
    {
        int element = numbers[i];

        if (element > 9)
        {
            result += element / 10;
            result += element % 10;
        }
        else
        {
            result += element;
        }
    }
}
