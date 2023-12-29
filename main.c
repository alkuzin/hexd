/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   main.c                                                                   */
/*                                                                            */
/*   By: alkuzin <->                                                          */
/*                                                                            */
/*   Created: 2023/12/29 12:00:17 by alkuzin                                  */
/*   Updated: 2023/12/29 20:05:04 by alkuzin                                  */
/*                                                                            */
/* ************************************************************************** */

#include "include/hexd.h"

static int set_base(char chr_base);


int main(int argc, char** argv)
{
	FILE *fp;
    int base;
    char filename[FILENAME_SIZE];

	if (argc < 2 || argc > 3)
    {
        puts("hexd: incorrect number of arguments\n"
        "hexd: use '--help' or '-h' to see options list");
        exit(1);
    }

    if ((strncmp(argv[1], "--help", 6) == 0) || (strncmp(argv[1], "-h", 2) == 0))
        show_help();

    if ((strncmp(argv[1], "--version", 9) == 0) || (strncmp(argv[1], "-v", 2) == 0))
        show_version();

    if (!(argv[1][0] == '-') || strlen(argv[1]) <= 1)
    {
        printf("hexd: incorrect option '%s'\n"
        "hexd: use '--help' or '-h' to see options list\n", argv[1]);
        exit(EXIT_FAILURE);
    }
	
	if(argc == 2)
	{
        puts("hexd: empty file name or incorrect option");
        exit(EXIT_FAILURE);
	}

    strncpy(filename, argv[2], FILENAME_SIZE);
    if(!(fp = fopen(filename, "rb")))
    {
        printf("hexd: error to open file '%s'\n"
        "hexd: file doesn't exist or corrupted\n", filename);
        exit(EXIT_FAILURE);
	}	
    
	if ((base = set_base(argv[1][1])) == -1)
	{
        printf("hexd: incorrect option '%s'\n"
        "hexd: use '--help' or '-h' to see options list\n", argv[1]);
        exit(EXIT_FAILURE);
	}

    show_bytes(fp, base);
    
    if (!feof(fp))
    {
        fpos_t pos;
        fgetpos(fp, &pos);
        printf("hexd: can't reach the end of the file on pos: %lld\n", (long long int)pos.__pos);
    }

    fclose(fp);
    return 0;
}

static int set_base(char chr_base)
{
	int base;


    switch (chr_base)
    {
    case 'x':
        base = HEX;
        break;
    
    case 'o':
        base = OCT;
        break;
    
    case 'b':
        base = BIN;
        break;

    default:
		base = -1;
        break;
    }

	return base;
}
