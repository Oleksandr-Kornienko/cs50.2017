/**
 * Copies a BMP piece by piece, just because.
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./resize n infile outfile\n");
        return 1;
    }

    // remember filenames
    int zoomNumber = atoi(argv[1]);
    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file 
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf, bfNew;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);
    bfNew = bf;
    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi, biNew;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);
    biNew = bi;
    


    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    biNew.biWidth *= zoomNumber;
    biNew.biHeight *= zoomNumber;
    
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int paddingNew = (4 - (biNew.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    biNew.biSizeImage = (biNew.biWidth * sizeof(RGBTRIPLE) + paddingNew) * abs(biNew.biHeight);
    //bfNew.bfSize = bf.bfSize - bi.biSizeImage + biNew.biSizeImage;
    bfNew.bfSize = biNew.biSizeImage +  sizeof(bfNew) +  sizeof(biNew);

    // write outfile's BITMAPFILEHEADER
    fwrite(&bfNew, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&biNew, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    for (int inputSkipPadding = 0, biHeight = abs(bi.biHeight); inputSkipPadding < biHeight; inputSkipPadding++)
    {
        for (int outputCloneWidth = 0; outputCloneWidth < zoomNumber; outputCloneWidth++)
        {  
            // iterate over pixels in scanline
            for (int inputPixel = 0; inputPixel < bi.biWidth; inputPixel++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                // write RGB triple to outfile
                for (int outputClonePixel = 0; outputClonePixel < zoomNumber; outputClonePixel++)
                fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
            }
            for (int iPutEmpty = 0; iPutEmpty < paddingNew; iPutEmpty++)
            {
                fputc(0x00, outptr);
            }
            if (outputCloneWidth != zoomNumber - 1)
            fseek(inptr, -bi.biWidth * sizeof(RGBTRIPLE), SEEK_CUR);
        }

        // skip over padding, if any
        fseek(inptr, padding, SEEK_CUR);
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
