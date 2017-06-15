#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

bool checkArgumentAmount(int argc);
bool checkArgumentContent(string code);
int main (int argc, string argv[])
{
    if (checkArgumentAmount(argc)==false||checkArgumentContent(argv[1])==false)
    {
        return 1;
    }
    printf("plaintext: ");
    string plaintext = GetString();
    printf("ciphertext: ");
       for (int i = 0, c = 0, plaintextLen = strlen(plaintext); i < plaintextLen; i++, c++)
    {
        if (c >= strlen(argv[1]))
        {
            c = 0;
        }
        bool upperText = false;
        char keyCharElement = argv[1][c];
        int keyIntElement = (int)keyCharElement;
        int cipherIntElement;
        if (isupper(keyCharElement))
        {
            keyIntElement = keyIntElement + 32;
        }
        int textIntElement = (int)plaintext[i];
        
        if ((textIntElement>=65&&textIntElement<=90)||(textIntElement>=97&&textIntElement<=122))
        {
            if (isupper(plaintext[i]))
            {
                textIntElement = textIntElement + 32;
                upperText = true; 
            }
            cipherIntElement = (textIntElement + keyIntElement - 97)%26;
            if (cipherIntElement >= 19)
            {
                cipherIntElement = cipherIntElement + 78;
            }
            else 
            {
                cipherIntElement = cipherIntElement + 104;
            }
        }
        else 
        {
           cipherIntElement = textIntElement;
           c = c - 1;
        }

        char cipherCharElement = (char)cipherIntElement;
        if (upperText == true)
        {
            cipherCharElement = toupper(cipherCharElement);
        }
        printf("%c", cipherCharElement);
        
    }
    printf("\n");
    return 0;
}

bool checkArgumentAmount(int argc)
{
   if (argc<2||argc>2)
    {
        printf("Argument must be 1!\n");
        return false;
    } 
    return true;
}

bool checkArgumentContent(string code)
{
    bool boolean=false;
    for (int i=0,n=strlen(code); i<n; i++)
    {
        int codeNumber = (int)code[i];
        if ((codeNumber>=65&&codeNumber<=90)||(codeNumber>=97&&codeNumber<=122))
        {
            boolean = true;
        } 
        else
        {
            printf("Argument must contain only alphabetic chars!\n");
            boolean = false;
            break;
        }
    }
    return boolean;
}