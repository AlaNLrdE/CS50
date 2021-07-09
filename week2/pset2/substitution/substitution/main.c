//
//  main.c
//  substitution
//
//  Created by Alan Osuna on 5/3/21.
//

#include <stdio.h>
#include "cs50.h"
#include <string.h>

#define cnstInvalidKey (int)1
#define cnstExitWithoutError (int)0
#define cnstStringInvalidNumberOfArguments (string)"ERROR: Unexpected number of arguments; expected arguments: 1, user arguments: %d.\n"
#define cnstStringInvalidCharacterKey (string)"Invalid character found in the key, use only characters from a to z or A to Z.\n"
#define cnstStringInvalidKeyLenght (string)"Invalid key lenght, it needs to contain %d characters.\n"
#define cnstKeyLenght (int)26

int process_key(string key, char* keyUpper, char* keyLower);
string cipher_text(string originaltext, char* keyUpper, char* keyLower);
int count_characters(string text);

int main(void)
{
    int iRet;
    int argc = 2;
    char keyUpper[26];
    char keyLower[26];
    string input = "ZYXWVUTSRQPONMLKJIHGFEDCBA";
    string sUserText;
    string sfixedText;

    if (argc == 2)
    {
        iRet = process_key(input, keyUpper, keyLower);
        if (iRet != cnstInvalidKey)
        {
            sUserText = get_string("plaintext:  ");
            sfixedText = cipher_text(sUserText, keyUpper, keyLower);
            printf ("ciphertext: %s\n", sUserText);
        }
    }
    else // The number of arguments is not as expexted (2 arguments)
    {
        iRet = cnstInvalidKey;
        printf(cnstStringInvalidNumberOfArguments, argc - 1);
    }
    return iRet;
}

int process_key(string key, char* keyUpper, char* keyLower)
{
    int i;
    int iRet = cnstExitWithoutError;
    bool boValidKey;
    const int cnstLowerUpper = 32;
    int number_letters;
    
    number_letters = count_characters(key);

    if(number_letters == cnstKeyLenght)
    {
        for (i = 0; i < cnstKeyLenght; i++)
        {
            boValidKey = false;
            //convert key to uppercase
            if (key[i] >= 'a' && key[i] <= 'z')
            {
                keyUpper[i] = key[i] - cnstLowerUpper;
                keyLower[i] = key[i];
                boValidKey = true;
            }
            if (key[i] >= 'A' && key[i] <= 'Z')
            {
                keyLower[i] = key[i] + cnstLowerUpper;
                keyUpper[i] = key[i];
                boValidKey = true;
            }
            if (boValidKey == false)
            {
                printf(cnstStringInvalidCharacterKey);
                iRet = cnstInvalidKey;
            }
        }
    }
    else
    {
        printf(cnstStringInvalidKeyLenght, cnstKeyLenght);
        iRet = cnstInvalidKey;
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

string cipher_text(string originaltext, char* keyUpper, char* keyLower)
{
    int i;
    int letters;

    letters = count_characters(originaltext);

    for (i = 0; i < letters; i++)
    {
        if (originaltext[i] >= 'a' && originaltext[i] <= 'z')
        {
            originaltext[i] = keyLower[originaltext[i]-97];
        }
        else if (originaltext[i] >= 'A' && originaltext[i] <= 'Z')
        {
            originaltext[i] = keyUpper[originaltext[i]-65];
        }
    }
    return originaltext;
}
