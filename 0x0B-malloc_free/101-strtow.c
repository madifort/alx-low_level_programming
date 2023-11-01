#include <stdlib.h>
#include "main.h"

/**
 * count_word - Helper function to count the number of words in a string
 * @s: String to evaluate
 * Return: Number of words
 */
int count_word(char *s)
{
	int flag, c, w;

	flag = 0;
	w = 0;

	for (c = 0; s[c] != '\0'; c++)
	{
		if (s[c] == ' ')
			flag = 0;
		else if (flag == 0)
		{
			flag = 1;
			w++;
		}
	}

	return (w);
}

/**
 * allocate_memory - Allocates memory for an array of strings
 * @words: Number of words
 * @str: Input string
 * Return: A pointer to the allocated memory
 */
char **allocate_memory(int words, char *str)
{
	char **matrix;
	int i, k = 0, len = 0, c = 0, start, end;

	while (str[len])
		len++;

	matrix = (char **)malloc(sizeof(char *) * (words + 1));
	if (matrix == NULL)
		return (NULL);

	for (i = 0; i <= len; i++)
	{
		if (str[i] == ' ' || str[i] == '\0')
		{
			if (c)
			{
				end = i;
				matrix[k] = (char *)malloc(sizeof(char) * (c + 1));
				if (matrix[k] == NULL)
					return (NULL);

				while (start < end)
					matrix[k][start - i] = str[start++];
				matrix[k][c] = '\0';
				k++;
				c = 0;
			}
		}
		else if (c++ == 0)
		{
			start = i;
		}
	}

	matrix[k] = NULL;
	return (matrix);
}

/**
 * strtow - Splits a string into words
 * @str: String to split
 * Return: Pointer to an array of strings (Success) or NULL (Error)
 */
char **strtow(char *str)
{
	int words;

	if (str == NULL || str[0] == '\0')
		return (NULL);

	words = count_word(str);
	if (words == 0)
		return (NULL);

	return (allocate_memory(words, str));
}
