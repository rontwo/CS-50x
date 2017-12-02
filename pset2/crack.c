#define _XOPEN_SOURCE
#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

int main(int argc, string argv[])
{
    // Check user entered only one value
    if(argc != 2 || argv[1] == NULL)
        {
        printf("Key was not accepted. Please enter one argument.\n");
        return 1;
        }
    // Variable declaration; store salt
    string hash = argv[1];
    char salt[3] = {hash[0], hash[1], '\0'}, test[5];
    test[4] = '\0';

    // Check salt is correct
    printf("%s\n", salt);
    // Define and check lenght of alphabet (upper & lower)
    string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    int alen = strlen(alphabet);
    printf("%i\n", alen);

    for(int i = 0; i < alen; i++)
    {
        for(int j = 0; j < alen; j++)
        {
            for (int k = 0; k < alen; k++)
            {
                for (int l = 0; l < alen; l++)
                {
                    test[0] = alphabet[i];
                    test[1] = alphabet[j];
                    test[2] = alphabet[k];
                    test[3] = alphabet[l];
                    if(strcmp(hash, crypt(test, salt)) == 0)
                    {
                        printf("The correct pw is %s\n", test);
                    }

                }
            }
        }
    }
    return 0;
}
