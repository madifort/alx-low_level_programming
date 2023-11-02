#include "main.h"

/**
 * _strcpy - Copies a string from src to dest
 * @dest: The destination where the string will be copied to
 * @src: The source string to be copied
 *
 * Return: A pointer to the destination string
 */
char *_strcpy(char *dest, char *src)
{
	int a = 0;
	int b = 0;

	while (*(src + a) != '\0')
	{
		a++;
	}

	for (; b < a; b++)
	{
		dest[b] = src[b];
	}

	dest[a] = '\0';

	return (dest);
}
