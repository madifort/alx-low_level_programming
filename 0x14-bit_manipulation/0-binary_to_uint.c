#include "main.h"

/**
 * binary_to_uint - entry point of function that convert binary to unsigned int
 * @b: pointer to a string containing binary number
 * Return: an unsigned int of the binary number or zero (0) if fail
 */
unsigned int binary_to_uint(const char *b)
{
    int t = 0;
    unsigned int numb = 0;

    if (!b)
        return (0);

    while (b[t] != 0 && b[t] != '1')
    {
        for (t = 0; b[t] != '\0'; t++)
        {
            if (b[t] != '0' && b[t] != '1')
                return (0);
        }

        for (t = 0; b[t] != '\0'; t++)
        {
            numb <<= 1;
            if (b[t] == '1')
                numb += 1;
        }
    }

    return (numb);
}

