#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    // Variable declarations
    bool keySuccessful = false;
    int key = 0;

    // Get input
    do {
        if(argc != 2)
        {
        printf("Please enter key again:\n");
        return 1;
        }
        else
        {
        keySuccessful = true;
        key = atoi(argv[1]);
        }
    } while (!keySuccessful);
    {
        printf("plaintext: ");
        string s = get_string();
        printf("ciphertext: ");
        for (int i = 0, l = strlen(s); i < l; i++)
        {
            if(isalpha(s[i]))
            {
            // Convert upper case letters; A = 65
                if(isupper(s[i]))
                {
                    printf("%c",((((s[i]-'A')+key)%26)+65));
                }
                // Convert lower case letters; a = 97
                if(islower(s[i]))
                {
                    printf("%c",((((s[i]-'a')+key)%26)+97));
                }
            }
            else {
                printf("%c", s[i]);
            }
        }
    }
    printf("\n");
    return 0;
}
