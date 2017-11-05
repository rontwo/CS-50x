#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    // Check user entered only one value
    if(argc != 2 || argv[1] == NULL)
        {
        printf("Key was not accepted. Please enter one argument.\n");
        return 1;
        }
    // Check that only alphabetical characters were entered
    for (int j = 0, n = strlen(argv[1]); j < n; j++)
        {
        if(!isalpha(argv[1][j]))
            {
                printf("Key was not accepted. Non-a,lkmlphabetical characters given.\n");
                return 1;
            }
        }
    string key = argv[1];
    int keylength = strlen(key);

    // Get string
    printf("plaintext: ");

    //Get string, check length > 0
    string plaintext = get_string();
    printf("ciphertext: ");
    for (int i = 0, j= 0, n = strlen(plaintext); i < n; i++)
    {
        //Convert jth char in key to ASCII
        if(!isalpha(plaintext[i]))
        {
            printf("%c", plaintext[i]);
        }
        else
        {
        int keyvalue = tolower(key[j%keylength])-'a';
        //Cipher uppercase
        if(isupper(plaintext[i]))
            {
                printf("%c", (plaintext[i]-'A'+keyvalue)%26+'A');
                j++;
            }
        // Cipher lowercase
        if(islower(plaintext[i]))
            {
                printf("%c", (plaintext[i]-'a'+keyvalue)%26+'a');
                j++;
            }
        }
        }
    printf("\n");
    return 0;
}
