#include <stdio.h>
#include <cs50.h>
#include <math.h>

/*
    $$ Pseudocode :
    0. 변수 초기화
        0-1. int minimum = 0; (최종 반환해야 할 값. 거슬러줄 수 있는 동전의 최소 개수)
        0-2. float owed; (사용자 인풋 저장)
        0-3. bool check = true; (사용자 인풋이 맞는지 확인하는 불리언 값)
    1. 사용자에게 입력을 받는다. 잔돈을 바꿔주어야 할 금액. 예) 9.75 (float)
        1-1. 음수가 아닌지 확인한다.
        1-2. 조건에 맞지 않는 경우 다시 프롬프트를 출력한다.
    2. int 변수에 입력받은 금액을 변환하여 저장한다. (float의 나눗셈은 부동소수점 부정확성 때문에 정확한 결과가 나오지 않는다)
        2-1. 지페(정수 부분)를 변환 저장 예) 9.75 -> 9 -> 900
        2-2. 동전(소수 부분)을 변환 저장 예) 9.75 -> 0.75 -> 75
    3. 지폐를 계산한다. 동전부터 거스름돈을 바꿔 준다. 사용되는 동전: 25센트, 10센트, 5센트, 1센트 (총 4종류)
        3-1. 25센트로 나눈다.
        3-2. 몫을 int type 변수 minimum에 추가한다.
    4. 동전을 계산한다.
        4-1. 25센트로 나눈다.
        4-2. 몫을 minimum에 추가한다.
        4-3. 나머지를 저장한다.
        4-4. 나머지 값을 받아 10, 5, 1센트도 반복한다.
    5. 지폐의 minimum과 동전의 minimum을 합산한다.
    6. minimum을 반환한다.
 
*/

int main(void)
{
    float owed;
    bool check = true;

    //Prompt the user for a change owed
    do {
        owed = get_float("Change owed: ");

        if(owed >= 0)
        {
            check = false;
        }

    }
    while (check);

    //$$
    printf("  Input: %.2f\n", owed);

    //Convert the user's inputted dollars to cents
    int bills = (int)owed * 100;
    int coins = round((owed - (int)owed) * 100); //round(): 가장 가까운 정수로 변환. 예) 0.75 -> 1


    //$$
    printf("  Bills: %i\n", bills);
    printf("  Coins: %i\n", coins);



    


}
