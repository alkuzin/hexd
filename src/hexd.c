/**
 * Tool for displaying file contents in hexadecimal, octal,
 * binary and ascii formats.
 * Copyright (C) 2024 Alexander (@alkuzin).
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <hexd.h>


#define HEXD_VERSION "2.0"
#define HEXD_YEAR    "2024"
#define FMT_SIZE     8
#define HEXD_TITLE  "\n"                    \
    " ██╗  ██╗███████╗██╗  ██╗██████╗  \n"  \
    " ██║  ██║██╔════╝╚██╗██╔╝██╔══██╗ \n"  \
    " ███████║█████╗   ╚███╔╝ ██║  ██║ \n"  \
    " ██╔══██║██╔══╝   ██╔██╗ ██║  ██║ \n"  \
    " ██║  ██║███████╗██╔╝ ██╗██████╔╝ \n"  \
    " ╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝╚═════╝  \n"  \

void hexd_help(void)
{
    puts(HEXD_TITLE);
    puts(
        "\nUSAGE\n"
        "\thexd [options] <file>\n\n"
        "DESCRIPTION\n"
        "\thexd - display file contents in hexadecimal, octal, "
        "binary and ascii formats\n\n"
        "OPTIONS\n"
        "\t-x\t\tone-byte hexidecimal+ASCII display\n"
        "\t-o\t\tone-byte octal display\n"
        "\t-b\t\tone-byte binary display\n\n"
        "\t-h, --help\tdisplay options list\n"
        "\t-v, --version\tdisplay version of hexd\n"
    );
    exit(EXIT_SUCCESS);
}

void hexd_version(void)
{
    printf("%s\nhexd: v%s %s (@alkuzin)", HEXD_TITLE, HEXD_VERSION, HEXD_YEAR);
    exit(EXIT_SUCCESS);
}

/**
 * @brief Convert byte to ASCII.
 *
 * @param [in] ch - given byte to convert.
 * @return character to print.
 */
static inline char to_print(uint8_t ch)
{
    return (ch > 31 && ch < 127) ? (char)ch : '.';
}

/**
 * @brief Handle bytes output mode.
 *
 * @param [in] mode - given bytes output mode.
 * @param [out] bpl - given bytes per line.
 * @param [out] fmt - given format string.
 */
static void handle_mode(enum MODE mode, size_t *bpl, char **fmt)
{
    switch(mode) {
		case BIN:
            *bpl = 8;
            *fmt = "%08b ";
			break;

		case OCT:
            *bpl = 16;
            *fmt = "%03o ";
			break;

		case HEX:
            *bpl = 16;
            *fmt = "%02x ";
			break;

		default:
            *bpl = 16;
            *fmt = "%02x ";
			break;
	};
}

void hexd_dump(enum MODE mode, const char *filename)
{
    FILE *file = fopen(filename, "r");

    if (!file) {
        printf("error to open file \"%s\"", filename);
        exit(EXIT_FAILURE);
    }

    size_t bytes_per_line = 16;
    char *fmt             = nullptr;

    handle_mode(mode, &bytes_per_line, &fmt);

    uint8_t buffer[bytes_per_line];
    size_t  rows = 0, bytes = 0;

    memset(buffer, 0, sizeof(buffer));

    while ((bytes = fread(buffer, sizeof(char), bytes_per_line, file)) > 0) {
        printf("%08lx  ", rows);

        // print first half of 8 bytes in hexadecimal format
        for (size_t i = 0; i < bytes_per_line >> 1; i++)
            printf(fmt, buffer[i]);

        putchar(' ');

        // print second half of 8 bytes in hexadecimal format
        for (size_t i = bytes_per_line >> 1; i < bytes_per_line; i++)
            printf(fmt, buffer[i]);

        // print string representation of bytes
        putchar(' ');
        putchar('|');

        for (size_t i = 0; i < bytes_per_line; i++)
            putchar(to_print(buffer[i]));

        putchar('|');
        putchar('\n');

        memset(buffer, 0, sizeof(buffer));
        rows += 0x10;
    }

    fclose(file);
}