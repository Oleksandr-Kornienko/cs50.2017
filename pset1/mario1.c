#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int number;
    do 
    {
        printf("Enter height: ");
        number = get_int();
    } while (!(number>=0 && number<=23));
    for (int i=1;i<=number;i++)
    {
        for (int empty=1; empty<=number-i;empty++)
        {
            printf(" ");
        }
        for (int symbol=0; symbol<=i;symbol++) 
        {
            printf("#");
        }
        printf("\n");
    }
}
