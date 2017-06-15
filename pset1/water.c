#include <stdio.h>
#include <cs50.h>

int main(void)
{
int time;
   do
   { 
    printf("How many minutes do you spend in a shower?\n");
    time = get_int();
   }
    while (time<1);
    printf("You are spending %i bottles of water.\n", time*12);
}