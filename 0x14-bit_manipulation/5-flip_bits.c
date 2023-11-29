#include "main.h"

/**
 * flip_bits - Count the num of bits to change to get from one num to another.
 * @n: The first number.
 * @m: The second number.
 *
 * Return: Number of bits to change.
 */
unsigned int flip_bits(unsigned long int n, unsigned long int m)
{
	int bit_index;
	unsigned int count_bits = 0;
	unsigned long int exclusive = n ^ m;
	unsigned long int current_bit;

	for (bit_index = 63; bit_index >= 0; bit_index--)
	{
		current_bit = exclusive >> bit_index;

		if (current_bit & 1)
			count_bits++;
	}

	return (count_bits);
}
