/**
 * Copies a BMP piece by piece, just because.
 * Implemented using the "rewrite" method
 */

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./resize infile outfile by factor of n\n");
        return 1;
    }

    //Store the resize factor
    int scalefactor = atoi(argv[1]);
    if(scalefactor < 1 || scalefactor > 100)
    {
        printf("Scale factor must be between 1 and 100\n");
        return 1;
    }

    // remember filenames
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
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);


    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    //Create outfile's BITMAPFILEHEADER and BITMAPINFOHEADER
    BITMAPFILEHEADER out_bf = bf;
    BITMAPINFOHEADER out_bi = bi;

    out_bi.biWidth *= scalefactor;
    out_bi.biHeight *= scalefactor;

    // determine padding for scanlines
    int in_padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int out_padding = (4 - (out_bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    out_bi.biSizeImage = (out_bi.biWidth * sizeof(RGBTRIPLE) + out_padding) * abs(out_bi.biHeight);
    out_bf.bfSize = out_bi.biSizeImage + 54;

    // write outfile's BITMAPFILEHEADER
    fwrite(&out_bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&out_bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // Allocate memory (array) to hold each scanline
    RGBTRIPLE *pixels = malloc(sizeof(RGBTRIPLE)*out_bi.biWidth);

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        int count = 0;
        // iterate over pixels in scanline & write to array
        for (int j = 0; j < bi.biWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;
            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            // Write RGB triple to array n (scalefactor) times
            for(int k = 0; k < scalefactor; k++)
            {
                *(pixels+count) = triple;
                count++;
            }
        }

        // Write RGB array & padding to outfile n times
        for(int l = 0; l < scalefactor; l++)
        {
            //Iterate over each elemnt in RGB array and write to outfile;
            for(int m = 0; m < out_bi.biWidth; m++)
            {
                fwrite(&pixels[m], sizeof(RGBTRIPLE), 1, outptr);
            }
            // Write outfile padding
            for (int n = 0; n < out_padding; n++)
            {
                fputc(0x00, outptr);
            }
        }
        // skip over padding, if any
        fseek(inptr, in_padding, SEEK_CUR);
    }
    // Free memory used for pixels
    free(pixels);

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
