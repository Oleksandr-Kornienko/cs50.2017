#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    long long card;
    long long card2;
    int count=0;
    int sum=0;
    long long digit;
    long long a;
    int firstNumber;
    int secondNumber;
    
    do
    {
        printf("Number: ");
        card = get_long_long();
    } while (card<=0);
    
    card2=card;
    while (!(card2<1))
    {
        card2=card2/10;
        count++; 
    }
    
    
    card2=card;
    for (int i = 1;i<=count;i=i+2)
    {
        a = pow(10,i);
        digit = card2/a;
        digit = digit%10;
        digit = digit*2;
        if (digit<10)
        {
            sum = sum+digit;
        }
        else 
        {
            firstNumber = digit/10;
            secondNumber = digit%10;
            sum = sum+firstNumber+secondNumber;
        }
    }
    
    for (int i = 0;i<=count;i=i+2)
    {
        a = pow(10,i);
        digit = card2/a;
        digit = digit%10;
        if (digit<10)
        {
            sum = sum+digit;
        }
        else 
        {
            firstNumber = digit/10;
            secondNumber = digit%10;
            sum = sum+firstNumber+secondNumber;
        }
    }
    
    int AmexAndMasterNumber = card/pow(10,count-2);
    int VisaNumber = card/pow(10,count-1);
    
    if (card>=pow(10,14)&&card<pow(10,15)&&(AmexAndMasterNumber==34||AmexAndMasterNumber==37)&&(sum%10==0))
    {
        printf("AMEX\n");
    }
    else if (card>=pow(10,15)&&card<pow(10,16)&&(AmexAndMasterNumber==51||AmexAndMasterNumber==52||AmexAndMasterNumber==53
     ||AmexAndMasterNumber==54||AmexAndMasterNumber==55)&&(sum%10==0))
    {
        printf("MASTERCARD\n");
    }
     else if (VisaNumber==4&&((card>=pow(10,12)&&card<pow(10,13))||(card>=pow(10,15)&&card<pow(10,16)))&&(sum%10==0))
    {
        printf("VISA\n");
    }
    
    else {
        printf("INVALID\n");
    }
return 0;
}