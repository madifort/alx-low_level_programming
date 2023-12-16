/*
* File: 100-elf_header.c
* Auth: madifort
*/

#include <elf.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void check_elf(unsigned char *e_ident);
void print_magic(unsigned char *e_ident);
void print_class(unsigned char *e_ident);
void print_data(unsigned char *e_ident);
void print_version(unsigned char *e_ident);
void print_abi(unsigned char *e_ident);
void print_type(unsigned int e_type);
void print_entry(unsigned long int e_entry);
void close_elf(int elf);

/**
 * check_elf - function confirms if a file is an ELF file.
 * @e_ident: A pointer to an array containing the ELF magic numbers.
 *
 * Description: If the file is not an ELF file - exit code 98.
 */
void check_elf(unsigned char *e_ident)
{
int index;

for (index = 0; index < 4; index++)
{
	if (e_ident[index] != 127 &&
			e_ident[index] != 'E' &&
			e_ident[index] != 'L' &&
			e_ident[index] != 'F')
	{
		dprintf(STDERR_FILENO, "Error: Not an ELF file\n");
		exit(98);
	}
}
}

/**
 * print_magic - function prints the magic numbers of an ELF header.
 * @e_ident: A pointer to an array containing the ELF magic numbers.
 *
 * Description: Magic numbers are separated by spaces.
 */
void print_magic(unsigned char *e_ident)
{
int index;

printf("  Magic:   ");

for (index = 0; index < EI_NIDENT; index++)
{
	printf("%02x", e_ident[index]);

	if (index == EI_NIDENT - 1)
		printf("\n");
	else
		printf(" ");
}
}

/**
 * print_class - function prints the class of the ELF file
 * @e_ident: a pointer to an array of bytes specifies
 *		how to interpret the file
 *
 * Return: nothing is returned
 */
void print_class(unsigned char *e_ident)
{
printf("  Class:                             ");

switch (e_ident[EI_CLASS])
{
case ELFCLASSNONE:
	printf("none\n");
	break;
case ELFCLASS32:
	printf("ELF32\n");
	break;
case ELFCLASS64:
	printf("ELF64\n");
	break;
default:
	printf("<unknown: %x>\n", e_ident[EI_CLASS]);
}
}

/**
 * print_data - function prints the data of an ELF header.
 * @e_ident: A pointer to an array containing the ELF class.
 */
void print_data(unsigned char *e_ident)
{
printf("  Data:                              ");

switch (e_ident[EI_DATA])
{
case ELFDATANONE:
	printf("none\n");
	break;
case ELFDATA2LSB:
	printf("2's complement, little endian\n");
	break;
case ELFDATA2MSB:
	printf("2's complement, big endian\n");
	break;
default:
	printf("<unknown: %x>\n", e_ident[EI_CLASS]);
}
}

/**
 * print_version - function print the version of the ELF file
 * @e_ident: a pointer to an array of bytes specifies
 *           how to interpret the file
 *
 * Return: nothing is returned
 */
void print_version(unsigned char *e_ident)
{
printf("  Version:                           %d",
		e_ident[EI_VERSION]);

switch (e_ident[EI_VERSION])
{
case EV_CURRENT:
	printf(" (current)\n");
	break;
default:
	printf("\n");
	break;
}
}

/**
 * print_osabi - function prints the OS/ABI of the ELF file
 * @e_ident: a pointer to an array of bytes specifies
 *           how to interpret the file
 *
 * Return: nothing is returned
 */
void print_osabi(unsigned char *e_ident)
{
printf("  OS/ABI:                            ");

switch (e_ident[EI_OSABI])
{
case ELFOSABI_NONE:
	printf("UNIX - System V\n");
	break;
case ELFOSABI_HPUX:
	printf("UNIX - HP-UX\n");
	break;
case ELFOSABI_NETBSD:
	printf("UNIX - NetBSD\n");
	break;
case ELFOSABI_LINUX:
	printf("UNIX - Linux\n");
	break;
case ELFOSABI_SOLARIS:
	printf("UNIX - Solaris\n");
	break;
case ELFOSABI_IRIX:
	printf("UNIX - IRIX\n");
	break;
case ELFOSABI_FREEBSD:
	printf("UNIX - FreeBSD\n");
	break;
case ELFOSABI_TRU64:
	printf("UNIX - TRU64\n");
	break;
case ELFOSABI_ARM:
	printf("ARM\n");
	break;
case ELFOSABI_STANDALONE:
	printf("Standalone App\n");
	break;
default:
	printf("<unknown: %x>\n", e_ident[EI_OSABI]);
}
}

/**
 * print_abi - function prints the ABI version of the ELF file
 * @e_ident: a pointer to an array of bytes specifies
 *           how to interpret the file
 *
 * Return: nothing is returned
 */
void print_abi(unsigned char *e_ident)
{
printf("  ABI Version:                       %d\n",
		e_ident[EI_ABIVERSION]);
}

/**
 * print_type - function prints the type of the ELF file
 * @e_type: a 32-bit quantity that specifies the file's type
 */
void print_type(unsigned int e_type)
{
printf("  Type:                              ");

switch (e_type)
{
case ET_NONE:
	printf("NONE (Unknown type)\n");
	break;
case ET_REL:
	printf("REL (Relocatable file)\n");
	break;
case ET_EXEC:
	printf("EXEC (Executable file)\n");
	break;
case ET_DYN:
	printf("DYN (Shared object file)\n");
	break;
case ET_CORE:
	printf("CORE (Core file)\n");
	break;
default:
	if (e_type >= ET_LOPROC && e_type <= ET_HIPROC)
		printf("Processor-specific\n");
	else if (e_type >= ET_LOOS && e_type <= ET_HIOS)
		printf("OS-specific\n");
	else
		printf("<unknown: %x>\n", e_type);
}
}

/**
 * print_entry - function prints the entry point of the ELF file
 * @e_entry: the memory address to jump to start running the program
 */
void print_entry(unsigned long int e_entry)
{
printf("  Entry point address:               0x%lx\n", e_entry);
}

/**
 * close_elf - function closes the file descriptor
 * @elf: the file descriptor to close
 *
 * Return: nothing is returned
 */
void close_elf(int elf)
{
if (close(elf) == -1)
{
	dprintf(STDERR_FILENO, "Error: Could not close file descriptor\n");
	exit(98);
}
}

/**
 * main - function parses an ELF header
 * @ac: number of arguments passed to the program
 * @av: an array of pointers to the arguments
 *
 * Return: Always returns 0
 */
int main(int ac, char **av)
{
int elf;
ssize_t bytes_read;
Elf32_Ehdr header;

if (ac != 2)
	dprintf(STDERR_FILENO, "Usage: %s elf_filename\n", av[0]);

elf = open(av[1], O_RDONLY);

if (elf == -1)
{
	dprintf(STDERR_FILENO, "Error: Could not open file\n");
	exit(98);
}

bytes_read = read(elf, &header, sizeof(header));

if (bytes_read == -1)
{
	dprintf(STDERR_FILENO, "Error: Could not read file\n");
	close_elf(elf);
	exit(98);
}

check_elf(header.e_ident);
print_magic(header.e_ident);
print_class(header.e_ident);
print_data(header.e_ident);
print_version(header.e_ident);
print_abi(header.e_ident);
print_type(header.e_type);
print_entry(header.e_entry);

close_elf(elf);

return (0);
}

