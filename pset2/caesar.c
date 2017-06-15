#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main (int argc, string argv[])
{
     int key = atoi(argv[argc-1]);
    if (argc==1||argc>2||key<0||!((key*10)%10==0))
    {
        printf("Argument must be 1! argc = %i\n", argc);
        return 1;
    }
    printf("plaintext: ");
    string plaintext = GetString();
    printf("ciphertext: ");
    for (int i = 0, n = strlen(plaintext); i < n; i++)
{
    
    char element = plaintext[i];
    if (((int)(element)>=65&&(int)(element)<=90)||((int)(element)>=97&&(int)(element)<=122))
    {
        bool lower = false;
        if (islower(element))
        {
            element = element - 32;
            lower = true;
        }
        int code = ((int)(element) + key)%26;
        if (code>=13)
        {
            code = code + 52;
        }
        else 
        {
            code = code + 78;
        }
        if (lower == true)
        {
            printf("%c", tolower((char)code));
        }
        else 
        {
            printf("%c", (char)code);
        }
        
    }
    else 
    {
        printf("%c", element); 
    }
}
printf("\n");

for (char i='a';i<='Z';i++){
   printf("char %c = %i\n", i, (int)i); 
}

    return 0;
}