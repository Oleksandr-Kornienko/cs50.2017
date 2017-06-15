#include <stdio.h>
#include <cs50.h>

int main(void)
{
    double change;
    int coins = 0;
    
    do 
    {
        printf("O hai! How much change is owed?\n");
        change = get_double();
    } while (change <= 0);
    change = change * 100;
   if (change>=25) {
    do 
    {
        change = change - 25;
        coins = coins + 1;
    } while(!(change<25));
   }
    
    if (change>=10) {
    do 
    {
        change = change - 10;
        coins = coins + 1;
    } while(!(change<10));
    }
    
    if (change>=5) {
    do 
    {
        change = change - 5;
        coins = coins + 1;
    } while(!(change<5));
    }
    
    if (change>=1) {
    do 
    {
        change = change - 1;
        coins = coins + 1;
    } while(!(change<1));
    }

    printf("%i\n", coins);
}