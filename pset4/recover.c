/**
 * Recovers JPGs off a corrupted memory card
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <stdint.h>

//Define block as 512 bytes
#define BLOCK 512

int main(int argc, char *argv[])
{
    //ensure proper usage
    if(argc != 2)
    {
        fprintf(stderr, "Usage error: Open file for recovery\n");
        return 1;
    }

    //Check that file is opened sucessfully
    FILE *inptr = fopen(argv[1],"r");
    if(inptr == NULL)
    {
        fprintf(stderr, "Could not open %s\n", argv[1]);
        return 2;
    }

    //Declare function to open & write new file and counter for jpgs
    FILE *outptr = NULL;
    int jpgcount = 0;

    //Declare jpg checks
    bool in_jpg = false;

    //Create name for first file
    char newfile[8];

    //Create variable to pass through fgets check
    char* checkbuffer = malloc(BLOCK);

    //While loop to run until ptr is at EOF
    while(fgets(checkbuffer, BLOCK, inptr) != NULL)
    {
        //Declare temp variable storage and read infile
        unsigned char* buffer = malloc(BLOCK);

        //Read infile into buffer
        fread(buffer, BLOCK, 1, inptr);

        //check whether the current block is the start of a new JPG.
        if (buffer[0] == 0xff &&
            buffer[1] == 0xd8 &&
            buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
            {
                //If already in JPG, close outfile;
                if(in_jpg)
                {
                    fclose(outptr);
                }

                //Set in_jpg to true
                in_jpg = true;

                //Name new output file
                jpgcount++;
                sprintf(newfile,"%03i.JPG", jpgcount);

                //Create and write to new outfile
                outptr = fopen(newfile, "w");
                if(outptr == NULL)
                {
                    fclose(inptr);
                    fprintf(stderr, "Could not create %s\n", newfile);
                    return 3;
                }
                //Write current blcok to outfile
                fwrite(buffer,BLOCK,1,outptr);
            }

        //Check to see if already in jpg; if so, write current block to outfile
        else if(in_jpg)
            {
                fwrite(buffer,BLOCK,1,outptr);
            }

        //Move ptr to next block
        fseek(inptr,512,SEEK_CUR);

        //Free buffer after each iteration
        free(buffer);
    }

    //Close input and output file after last
    fclose(inptr);
    fclose(outptr);

    //Free checkbuffer
    free(checkbuffer);

    //Woohoo!
    return 0;
}
