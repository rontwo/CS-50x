#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    float n;
    int quarters = 0, dimes = 0, nickles = 0, pennies = 0, cent_amount, count;
    do
    {
        printf("How much change do you want?\n");
        n = get_float();
        if(n==0||n<0)
        {
        printf("Number should be greater than zero\n");
        }./
    }
    while(n<=0);

    cent_amount = (int)round(n*100);
    while(cent_amount >= 25)
    {
        quarters ++, cent_amount -=25;
    }
    while(cent_amount >= 10)
    {
        dimes ++, cent_amount -=10;
    }
    while(cent_amount >= 5)
    {
        nickles ++, cent_amount -=5;
    }
    while(cent_amount >= 1)
    {
        pennies ++, cent_amount -=1;
    }
    count = quarters + dimes + nickles + pennies;
    printf("The total amount of coins is %i. %i quarters, %i dimes, %i nickels, %i pennies.\n", count, quarters, dimes, nickles, pennies);
}
