/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   hexd.c                                                                   */
/*                                                                            */
/*   By: alkuzin <->                                                          */
/*                                                                            */
/*   Created: 2023/12/26 13:01:07 by alkuzin                                  */
/*   Updated: 2023/12/29 19:53:03 by alkuzin                                  */
/*                                                                            */
/* ************************************************************************** */

#include "../include/hexd.h"

// set size of field
static int set_size(int base, char *fmt);

// return correct symbol  
static char to_print(unsigned char c);

// hexd title
static const char *title = "\n"     
" ██╗  ██╗███████╗██╗  ██╗██████╗  \n"
" ██║  ██║██╔════╝╚██╗██╔╝██╔══██╗ \n"
" ███████║█████╗   ╚███╔╝ ██║  ██║ \n"
" ██╔══██║██╔══╝   ██╔██╗ ██║  ██║ \n"
" ██║  ██║███████╗██╔╝ ██╗██████╔╝ \n"
" ╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝╚═════╝  \n";


void show_bytes(FILE* fp, int base)
{
	char fmt[FMT_SIZE];
    int line_number;
    int size;

	int c;
    int i;
    int j;

   
	i = 0;
	line_number = 0x0;
    size = set_size(base, fmt);

    char line[size + 1];
    memset(line, ' ', size);

	printf("%08x  ", line_number);
    while ((c = fgetc(fp)) != EOF)
    {
		c = (unsigned int)c;
		printf(fmt, c);

        line[i] = to_print(c);
        i++;

        if (i == size / 2)
		{
			putchar(' ');
			line_number += 0x8;
		}

        if (i == size)
        {
			line_number += 0x8;
            line[size] = '\0';
            printf(" |%s|\n%08x  ", line, line_number);
            i = 0;
            memset(line, ' ', size);
        }
    }
	line[i] = '\0';
    if (i < size)
    {
        j = i;
		i = 0;
        while(i < size - j)
        {
            if (i == size / 2)
                putchar(' ');
            printf("%s", "   ");
            i++;
        }
        printf(" |%s|\n", line);
    }
    printf("%08x\n", line_number);
}

void show_help(void)
{
    puts(title);
    puts(
    "\nUSAGE\n"
    "\thexd [options] <file>\n\n"
    "DESCRIPTION\n"
    "\thexd - display file contents in hexadecimal, octal, binary and ascii formats\n\n"
    "OPTIONS\n"
    "\t-x\t\tone-byte hexidecimal+ASCII display\n"
    "\t-o\t\tone-byte octal display\n"
    "\t-b\t\tone-byte binary display\n\n"
    "\t-h, --help\tdisplay options list\n"
    "\t-v, --version\tdisplay version of hexd\n"
    );
    exit(EXIT_SUCCESS);
}

void show_version(void)
{
    puts(title);
    printf("[*] Current version: %sv %s\n", VERSION, YEAR);
    exit(EXIT_SUCCESS);
}

static char to_print(unsigned char c)
{
    return (c > 31 && c < 127)? c : '.';
}

static int set_size(int base, char *fmt)
{
    int size;


    switch(base)
	{
		case BIN:
            size = 8; 
			memcpy(fmt, "%08b ", FMT_SIZE);
			break;
		
		case OCT:
            size = 16; 
			memcpy(fmt, "%03o ", FMT_SIZE);
			break;
		
		case HEX:
            size = 16; 
			memcpy(fmt, "%02x ", FMT_SIZE);
			break;

		default:
            size = -1;
			break;
	};

	fmt[FMT_SIZE] = '\0';
    return size;
}
