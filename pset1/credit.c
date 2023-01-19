#include <stdio.h>
#include <cs50.h>
#include <math.h>
/*
    $$ Pseudocode:
    1.사용자에게 카드번호 입력을 받아 변수에 저장한다.
    2.배열의 길이를 계산한다.
    3.길이에 맞는 배열을 생성한다.
    4.한 자리씩 각 요소에 저장한다.
    5.곱하기 연산
        - 카드번호의 자릿수가 짝수인지 홀수인지 판단한다.
        - 짝수인 경우 배열의 요소가 짝수 번째일 때 2를 곱해준다. (홀수인 경우에는 홀수 번째에 곱해준다.)
    6.더하기 연산
        - 배열의 0번째 요소부터 0으로 초기화한 result 변수에 가산하며 계산한다.
        - 요소가 10 이상인 경우 십의 자리와 일의 자리를 한 자리의 digit으로 분리하여 result 변수에 하나씩 더한다.
    7.카드의 종류를 판단한다.
        - result % 10 != 0인 경우 INVALID
        - result % 10 == 0인 경우 카드사의 종류를 판단한다.
    8.결과값 출력
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
