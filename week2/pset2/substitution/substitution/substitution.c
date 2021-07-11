#include <stdio.h>
#include <cs50.h>
#include <string.h>

#define cnstInvalidKey (int)1
#define cnstExitWithoutError (int)0
#define cnstStringInvalidNumberOfArguments (string)"ERROR: Unexpected number of arguments; expected arguments: 1, user arguments: %d.\n"
#define cnstStringInvalidCharacterKey (string)"Invalid character found in the key, use only characters from a to z or A to Z and avoid duplicates.\n"
#define cnstStringInvalidKeyLenght (string)"Invalid key lenght, it needs to contain %d characters.\n"
#define cnstKeyLenght (int)26

int process_key(string key, char *keyUpper, char *keyLower);
string cipher_text(string originaltext, char *keyUpper, char *keyLower);
int count_characters(string text);
int find_duplicate(string sKey);

int main(int argc, char *argv[])
{
    int iRet;
    char keyUpper[26];
    char keyLower[26];
    string sUserText;
    string sfixedText;

    // validate the number of arguments
    if (argc == 2)
    {
        // validates the key
        iRet = process_key(argv[1], keyUpper, keyLower);
        // if the key is valid...
        if (iRet != cnstInvalidKey)
        {
            // get a string from the used...
            sUserText = get_string("plaintext:  ");
            // ...encode the text...
            sfixedText = cipher_text(sUserText, keyUpper, keyLower);
            // ...show the encoded version of the text
            printf("ciphertext: %s\n", sUserText);
        }
    }
    else // The number of arguments is not as expexted (2 arguments)
    {
        // return with an error message because of the number of arguments
        iRet = cnstInvalidKey;
        printf(cnstStringInvalidNumberOfArguments, argc - 1);
    }
    return iRet;
}

int process_key(string key, char *keyUpper, char *keyLower)
{
    int i;
    int iRet = cnstExitWithoutError;
    bool boValidKey;
    const int cnstLowerUpper = 32;
    int number_letters;
    
    // get the lenght of the key
    number_letters = count_characters(key);
    // validate the key lenght, it should be 26
    if (number_letters == cnstKeyLenght)
    {
        // iterate through the whole key...
        for (i = 0; i < cnstKeyLenght; i++)
        {
            boValidKey = false;
            //convert key to uppercase...
            if (key[i] >= 'a' && key[i] <= 'z')
            {
                //...by substracting 32 from it
                keyUpper[i] = key[i] - cnstLowerUpper;
                keyLower[i] = key[i];
                boValidKey = true;
            }
            // if the character is uppercase, convert it to lowercase
            if (key[i] >= 'A' && key[i] <= 'Z')
            {
                keyLower[i] = key[i] + cnstLowerUpper;
                keyUpper[i] = key[i];
                boValidKey = true;
            }
            // if the character is not an alphabet character, declare the key invalid
            if (boValidKey == false)
            {
                printf(cnstStringInvalidCharacterKey);
                iRet = cnstInvalidKey;
            }
        } 
        // if the key contained only alphabet characters, try to find duplicate character in the key
        if (iRet == 0)
        {
            iRet = find_duplicate(keyUpper);
        }
    }
    else
    {
        printf(cnstStringInvalidKeyLenght, cnstKeyLenght);
        iRet = cnstInvalidKey; 
    }

    return iRet;
}

int find_duplicate(string sKey)
{
    int number_letters;
    int i, j;
    int iRet = 0;
    
    // iterate though the key to try to detect duplicate characters
    number_letters = count_characters(sKey);
    for (i = 0; i < (number_letters - 1); i++)
    {
        //this algorithm compares a given character with the remaining characters in the string
        for (j = i + 1; j < number_letters; j++)
        {
            if (sKey[i] == sKey[j])
            {
                //if there are duplicated characters, print an error message and return an error code
                iRet = 1;
                printf(cnstStringInvalidCharacterKey);
            }
        }
    }
    return iRet;
}

int count_characters(string text)
{
    int letters = 0;
    int i = 0;

    //if the character is between certain range of ascii values, count it as a letter
    while (text[i] != '\0')
    {
        letters += 1;
        i++;
    }
    return letters;
}

string cipher_text(string originaltext, char *keyUpper, char *keyLower)
{
    int i;
    int letters;

    letters = count_characters(originaltext);

    // iterates through the whole string to replace the original character
    // with the ciphered version of it.
    for (i = 0; i < letters; i++)
    {
        // this part handles the lower case characters
        if (originaltext[i] >= 'a' && originaltext[i] <= 'z')
        {
            originaltext[i] = keyLower[originaltext[i] - 97];
        }
        // this part handles the upper case characters
        else if (originaltext[i] >= 'A' && originaltext[i] <= 'Z')
        {
            originaltext[i] = keyUpper[originaltext[i] - 65];
        }
    }
    return originaltext;
}