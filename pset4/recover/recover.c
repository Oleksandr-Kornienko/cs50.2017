/**
 * recover.c
 */

#include <stdio.h>
#include <stdlib.h>

#include <stdint.h>

typedef uint8_t  BYTE;

int main(void)
{
    FILE* file = fopen("card.raw", "r");
    if (file==NULL || !(fopen("card.raw", "r")))
    {
        fclose(file);
	    fprintf(file, "Wasn't able to open the cardfile.\n");
		return 1;
    }
    
    FILE* img = NULL;
    
    int count = 0;
    
    BYTE buffer[512];

    while(fread(&buffer, sizeof(BYTE) * 512, 1, file))
    {
        //check magic number
        if ((buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && buffer[3] == 0xe0) ||
            (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && buffer[3] == 0xe1))
        {
            if (img != NULL)
            {
                fclose(img);
            }

            char title[50];
            sprintf(title, "%03d.jpg", count);
            count++;

            img = fopen(title, "a");

            fwrite(&buffer, sizeof(BYTE) * 512, 1, img);
        }
        else if (img != NULL)
        {
            fwrite(&buffer, sizeof(BYTE) * 512, 1, img);
        }
    }

    fclose(img);
    fclose(file);
}
