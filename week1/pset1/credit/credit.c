#include <stdio.h>
#include <cs50.h>

bool luhnValidation(unsigned long ccNumber, unsigned int noDigits);

int main(void)
{
    unsigned long ccNumber;
    unsigned long tmpNumber;
    unsigned int noDigits = 0;

    ccNumber = get_long("Number: ");
    tmpNumber = ccNumber;

    /* get the number of digits from the user's input */
    while (tmpNumber > 0)
    {
        //This algorithm divides the number by 10 and if the result is greater than 0 that means that there are still
        // digits to be counted
        tmpNumber = tmpNumber / 10;
        noDigits++;
    }

    if (noDigits == 15) /* if its an American Expres...*/
    {
        tmpNumber =  ccNumber / (1e13);
        if (tmpNumber == 34 || tmpNumber == 37) // 34 and 37 corresponds to AMEX
        {
            // Validation trough Luhn's algorithm
            if (luhnValidation(ccNumber, noDigits) == true)
            {
                printf("AMEX\n");
            }
            else //if the Luhn's algorithm returns false that means that the number is invalid
            {
                printf("INVALID\n");
            }
        }
        else // AMEX is the only card with 15 numbers, but if the IDs are not equal to 34 or 37, that means that the number is invalid
        {
            printf("INVALID\n");
        }
    }
    else if (noDigits == 16) /*...or if its a mastercard or visa*/
    {
        tmpNumber =  ccNumber / (1e15);
        if (tmpNumber == 4)
        {
            // Validation trough Luhn's algorithm
            if (luhnValidation(ccNumber, noDigits) == true)
            {
                printf("VISA\n");
            }
            else //if the Luhn's algorithm returns false that means that the number is invalid
            {
                printf("INVALID\n");
            }
        }
        else
        {
            tmpNumber =  ccNumber / (1e14);
            if (tmpNumber == 51 || tmpNumber == 52 || tmpNumber == 53 || tmpNumber == 54 || tmpNumber == 55) // these are the Ids for MASTERCARD
            {
                // Validation trough Luhn's algorithm
                if (luhnValidation(ccNumber, noDigits) == true)
                {
                    printf("MASTERCARD\n");
                }
                else //if the Luhn's algorithm returns false that means that the number is invalid
                {
                    printf("INVALID\n");
                }
            }
            else// MASTERCARD and VISA use 16 numbers in their cards, but if the IDs are not equal to 51-55 or 4, that means that the number is invalid
            {
                printf("INVALID\n");
            }
        }
    }
    else if (noDigits == 13) /*...or if its a visa */
    {
        tmpNumber =  ccNumber / (1e12);
        if (tmpNumber == 4) // This is VISA's Id number
        {
            // Validation trough Luhn's algorithm
            if (luhnValidation(ccNumber, noDigits) == true)
            {
                printf("VISA\n");
            }
            else //if the Luhn's algorithm returns false that means that the number is invalid
            {
                printf("INVALID\n");
            }
        }
        else // VISA is the only card with 13 numbers, but if the IDs are not equal to 34 or 37, that means that the number is invalid
        {
            printf("INVALID\n");
        }
    }
    else /*...or invalid */
    {
        printf("INVALID\n");
    }

}

bool luhnValidation(unsigned long ccNumber, unsigned int noDigits)
{
    unsigned int i;
    unsigned long tmpNumber;
    unsigned int digits[16] = {0};
    unsigned int everyotheracc = 0;
    bool boRet = false;

    tmpNumber = ccNumber;

    for (i = 0; i < noDigits; i++)
    {
        digits[i] = tmpNumber % 10;
        tmpNumber = tmpNumber / 10;
    }
    for (i = 1; i < noDigits; i += 2)
    {
        tmpNumber = digits[i] * 2;
        everyotheracc = everyotheracc + (tmpNumber / 10) + (tmpNumber % 10);
    }
    for (i = 0; i < noDigits; i += 2)
    {
        everyotheracc = everyotheracc + digits[i];
    }
    if (everyotheracc % 10 == 0)
    {
        boRet = true;
    }

    return boRet;
}