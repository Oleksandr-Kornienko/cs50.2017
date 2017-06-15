#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

char *getInicials(string name);

int main (void)
{
    string name = GetString();
    string inicials  = getInicials(name);
    printf("%s\n", inicials);
}

char *getInicials(string name)
{
    int element = 0;
    static char inicials[10];
    inicials[element] = toupper(name[0]);
    for (int i=0;i<strlen(name);i++)
    {
        if (name[i]==' ')
        {
            element++;
            inicials [element] = toupper(name[i+1]);
        }
    }
    return inicials;
}
