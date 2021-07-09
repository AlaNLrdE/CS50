#include <stdio.h>
#include <cs50.h>
#include <math.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    string text;
    int letters;
    int words = 0;
    int sentences = 0;
    int grade;
    double modulus;
    float index;
    float L;
    float S;
    
    // get the string from the user...
    text = get_string("Text: ");
    // count the number of letters
    letters = count_letters(text);
    // count the number of words and stences only 
    //if the number of letters is bigger than 0
    if (letters > 0)
    {
        words = count_words(text); 
        sentences = count_sentences(text);
    }
    printf("letters: %d\nwords: %d\nsentences: %d\n", letters, words, sentences);

    // calculate the readability grade
    L = (letters * 100) / (float)words;
    S = (sentences * 100) / (float)words;
    index = 0.0588 * L - 0.296 * S - 15.8;
    printf("L: %f\nS: %f\nindex: %f\n", L, S, index);
    // round up/down depending of the decimal portion of the grade 
    modulus = fmod(index, 1);
    printf("modulus: %f", modulus);
    if (modulus < .5)
    {
        grade = (int)index;
    }
    else
    {
        grade = (int)(index + 1.0);
    }

    // check for the grade level to display the appropiate message
    if (grade >= 16) //if the grade is equal or grater than 16, display 16+
    {
        printf("Grade 16+\n");
    }
    else if (grade < 1) // if the grade is less than 1, display before grade
    {
        printf("Before Grade 1\n");
    }
    else //else display the grade value
    {
        printf("Grade %i\n", (int)grade);
    } 
}

int count_letters(string text)
{
    int letters = 0;
    int i = 0;

    //if the character is between certain range of ascii values, count it as a letter
    while (text[i] != '\0')
    {
        if (text[i] >= 'a' && text[i] <= 'z' || text[i] >= 'A' && text[i] <= 'Z') 
        {
            // increment the letters value by 1 if the character is a letter
            // lower or uppercase
            letters += 1;
        }
        i++;
    }

    return letters;
}

int count_words(string text)
{
    int words = 1;
    int i = 0;

    // if there is a space, increment the number of words
    while (text[i] != '\0')
    {
        if (text[i] == ' ') 
        {
            words += 1;
        }
        i++;
    }

    return words;
}

int count_sentences(string text)
{
    int sentences = 0;
    int i = 0;

    // increment the number of sentences if the character is equal to these characters
    while (text[i] != '\0')
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?') 
        {
            sentences += 1;
        }
        i++;
    }

    return sentences;
}