#include <stdio.h>
#include <cs50.h>

int main(void)
{
    /* asking for the users name */
    string name = get_string("What is your name?\n");
    /* ...then greet him using his/hers name */
    printf("hello, %s\n", name);
}