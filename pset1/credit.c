#include <stdio.h>
#include <cs50.h>
#include <math.h>
/*
    Pseudocode:
    1.사용자에게 카드번호 입력을 받아 변수에 저장한다.
    2.배열의 길이를 계산한다.
    3.길이에 맞는 배열을 생성한다.
    4.한 자리씩 각 요소에 저장한다.
    5.checksum 연산
        - 카드번호의 첫번째 숫자부터 검사한다.
        - 배열의 짝수번째 요소이면 2를 곱해준다.
        - 십의자리(한자리 숫자면 0), 일의자리를 각각 sum에 가산한다.
    6.카드의 종류를 판단한다.
        - sum % 10 != 0인 경우 INVALID
        - sum % 10 == 0인 경우 카드사의 종류를 판단한다.
    7.결과값 출력
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
    int parity = count % 2;

    // checksum 연산
    int sum = 0;

    for (int i = 0; i < count; i++)
    {
        int digit = numbers[i];

        if (i % 2 == parity)
            digit *= 2;

        sum += digit / 10;
        sum += digit % 10;
    }

    // 카드번호가 유효한지 식별
    string result;
    if (sum % 10 != 0)
    {
        result = "INVALID";
    }
    else
    {
        // 유효한 경우 카드사 식별
        int creditor = (numbers[0] * 10) + numbers[1];
        if ((creditor == 34 || creditor == 37) && count == 15)
        {
            result = "AMEX";
        }
        else if (creditor >= 51 && creditor <= 55 && count == 16)
        {
            result = "MASTERCARD";
        }
        else if (creditor >= 40 && creditor <= 49 && (count == 13 || count == 16))
        {
            result = "VISA";
        }
        else
        {
            result = "INVALID";
        }
    }

    // 결과 출력
    printf("%s\n", result);
}
