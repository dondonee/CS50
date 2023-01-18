#include <stdio.h>
#include <cs50.h>
#include <math.h>
/*
    $$ What to do :
    1. 사용자에게 거스름돈 값을 입력 받는다.
    2. 거슬러줄 수 있는 동전의 최소 개수를 출력한다.
*/
/*
    $$ Pseudocode :
    1. 사용자에게 바꿔주어야 할 금액을 입력받는다. 예) 9.75 (float)
        1-1. 음수가 아닌지 확인한다.
        1-2. 조건에 맞지 않는 경우 1로 돌아가 프롬프트를 다시 출력한다.
    2. int 변수에 입력받은 금약을 1페니 단위로 변환하여 저장한다. (float의 나눗셈은 부동소수점 부정확성 때문에 정확한 결과가 나오지 않는다)
    3. 큰 동전부터 사용해 거슬러준다. 사용되는 동전: 25센트, 10센트, 5센트, 1센트 (총 4종류)
        3-1. 25센트 동전을 사용해 나눈다.
        3-2. 몫을 int type 변수 minimum에 가산한다.
        3-3. 나머지를 계산한다.
            3-3-a. 나머지가 0인 경우 반복문을 탈출한다.
        3-4. 나머지 값을 받아 10, 5, 1센트 차례로 반복한다.
    4. minimum을 반환한다. 

*/
int whittleDown(int);

int main(void)
{
    float owed;
    bool check = true;
    int minimum = 0;

    // Prompt the user for a change owed
    do
    {
        owed = get_float("Change owed: ");

        if (owed >= 0)
        {
            check = false;
        }

    } while (check);

    // Convert the user's inputted dollars to cents
    int coins = round(owed * 100); // round(): 가장 가까운 정수로 변환. 예) 0.75 -> 1

    // Print result(minimum)
    minimum = whittleDown(coins);
    printf("%i\n", minimum);
}

int whittleDown(int dividend)
{
    int coinTypes[4] = {25, 10, 5, 1};
    int remainder = dividend;
    int result = 0;

    for (int i = 0; i < 4; i++)
    {
        int size = coinTypes[i];
        int quotient = remainder / size;
        remainder = remainder - (size * quotient);

        result += quotient;

        if (remainder == 0)
        {
            i = 999;
        }
    }

    return result;
}
